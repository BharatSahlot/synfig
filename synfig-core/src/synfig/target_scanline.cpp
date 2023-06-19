/* === S Y N F I G ========================================================= */
/*!	\file target_scanline.cpp
**	\brief Template File
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2008 Chris Moore
**	Copyright (c) 2012-2013 Carlos López
**
**	This file is part of Synfig.
**
**	Synfig is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 2 of the License, or
**	(at your option) any later version.
**
**	Synfig is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with Synfig.  If not, see <https://www.gnu.org/licenses/>.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "target_scanline.h"

#include "general.h"
#include <synfig/localization.h>

#include "canvas.h"
#include "context.h"
#include "render.h"
#include "string.h"
#include "surface.h"
#include "rendering/renderer.h"
#include "rendering/surface.h"
#include "rendering/software/surfacesw.h"
#include "rendering/common/task/tasktransformation.h"

#endif

/* === U S I N G =========================================================== */

using namespace synfig;
using namespace rendering;

/* === M A C R O S ========================================================= */

#define PIXEL_RENDERING_LIMIT 1500000

#define USE_PIXELRENDERING_LIMIT 1

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

Target_Scanline::Target_Scanline():
	threads_(2)
{
	curr_frame_=0;
	if (const char *s = getenv("SYNFIG_TARGET_DEFAULT_ENGINE"))
		set_engine(s);
}

int
Target_Scanline::next_frame(Time& time)
{
	return Target::next_frame(time);
}

bool
synfig::Target_Scanline::call_renderer(
	const etl::handle<rendering::SurfaceResource> &surface,
	Canvas &canvas,
	const ContextParams &context_params,
	const RendDesc &renddesc )
{
	surface->create(renddesc.get_w(), renddesc.get_h());
	rendering::Task::Handle task = canvas.build_rendering_task(context_params);

	if (task)
	{
		rendering::Renderer::Handle renderer = rendering::Renderer::get_renderer(get_engine());
		if (!renderer)
			throw "Renderer '" + get_engine() + "' not found";

		Vector p0 = renddesc.get_tl();
		Vector p1 = renddesc.get_br();
		if (p0[0] > p1[0] || p0[1] > p1[1]) {
			Matrix m;
			if (p0[0] > p1[0]) { m.m00 = -1.0; m.m20 = p0[0] + p1[0]; std::swap(p0[0], p1[0]); }
			if (p0[1] > p1[1]) { m.m11 = -1.0; m.m21 = p0[1] + p1[1]; std::swap(p0[1], p1[1]); }
			TaskTransformationAffine::Handle t = new TaskTransformationAffine();
			t->transformation->matrix = m;
			t->sub_task() = task;
			task = t;
		}

		task->target_surface = surface;
		task->target_rect = RectInt( VectorInt(), surface->get_size() );
		task->source_rect = Rect(p0, p1);

		rendering::Task::List list;
		list.push_back(task);
		renderer->run(list);
	}
	return true;
}

bool
synfig::Target_Scanline::render(ProgressCallback *cb)
{
	SuperCallback super_cb;
	int
		frames=0,
		total_frames,
		frame_start,
		frame_end;
	Time
		t=0;

	assert(canvas);
	curr_frame_=0;

	if( !init() ){
		if(cb) cb->error(_("Target initialization failure"));
		return false;
	}

	frame_start=desc.get_frame_start();
	frame_end=desc.get_frame_end();

	ContextParams context_params(desc.get_render_excluded_contexts());

	// Calculate the number of frames
	total_frames=frame_end-frame_start+1;
	if(total_frames<=0)total_frames=1;

	try {
		do{
			// Grab the time
			frames=next_frame(t);

			// If we have a callback, and it returns
			// false, go ahead and bail. (it may be a user cancel)
			if(cb && !cb->amount_complete(total_frames-frames,total_frames))
				return false;

			// Set the time that we wish to render
			if(!get_avoid_time_sync() || canvas->get_time()!=t) {
				canvas->set_time(t);
				canvas->load_resources(t);
			}
			canvas->set_outline_grow(desc.get_outline_grow());

			// If quality is set otherwise, then we use the accelerated renderer
			{
				#if USE_PIXELRENDERING_LIMIT
				if(desc.get_w()*desc.get_h() > PIXEL_RENDERING_LIMIT)
				{
					SurfaceResource::Handle surface = new SurfaceResource();

					int rowheight = PIXEL_RENDERING_LIMIT/desc.get_w();
					if (!rowheight) rowheight = 1; // TODO: render partial lines to stay within the limit?
					int rows = desc.get_h()/rowheight;
					int lastrowheight = desc.get_h() - rows*rowheight;

					rows++;

					synfig::info("Render split to %d block%s %d pixels tall, and a final block %d pixels tall",
								 rows-1, rows==2?"":"s", rowheight, lastrowheight);

					// loop through all the full rows
					if(!start_frame())
					{
//						throw(string("render(): target panic on start_frame()"));
						if(cb)
							cb->error(_("render(): target panic on start_frame()"));
						return false;
					}

					for(int i=0; i < rows; ++i)
					{
						surface->reset();
						RendDesc blockrd = desc;

						//render the strip at the normal size unless it's the last one...
						if(i == rows-1)
						{
							if(!lastrowheight) break;
							blockrd.set_subwindow(0,i*rowheight,desc.get_w(),lastrowheight);
						}
						else
						{
							blockrd.set_subwindow(0,i*rowheight,desc.get_w(),rowheight);
						}

						//synfig::info( " -- block %d/%d left, top, width, height: %d, %d, %d, %d",
						//	i+1, rows, 0, i*rowheight, blockrd.get_w(), blockrd.get_h() );

						if (!call_renderer(surface, *canvas, context_params, blockrd))
						{
							if(cb)cb->error(_("Accelerated Renderer Failure"));
							return false;
						} else {
							SurfaceResource::LockRead<SurfaceSW> lock(surface);
							if (!lock) {
								if(cb)cb->error(_("Accelerated Renderer Failure: cannot read surface"));
								return false;
							}

							const synfig::Surface &s = lock->get_surface();

							int yoff = i*rowheight;

							if(!process_block_alpha(s, s.get_w(), blockrd.get_h(), yoff, cb)) return false;
						}
					}
					surface->reset();

					end_frame();

				}else //use normal rendering...
				{
				#endif
					SurfaceResource::Handle surface = new SurfaceResource();

					if (!call_renderer(surface, *canvas, context_params, desc))
					{
						// For some reason, the accelerated renderer failed.
						if(cb)cb->error(_("Accelerated Renderer Failure"));
						return false;
					}

					SurfaceResource::LockRead<SurfaceSW> lock(surface);
					if(!lock)
					{
						if(cb)cb->error(_("Bad surface"));
						return false;
					}

					// Put the surface we renderer
					// onto the target.
					if(!add_frame(&lock->get_surface(), cb))
					{
						if(cb)cb->error(_("Unable to put surface on target"));
						return false;
					}
				#if USE_PIXELRENDERING_LIMIT
				}
				#endif
			}
		} while(frames);
	}
	catch(const String& str)
	{
		if (cb) cb->error(_("Caught string: ")+str);
		return false;
	}
	catch (std::bad_alloc&)
	{
		if (cb) cb->error(_("Ran out of memory (Probably a bug)"));
		return false;
	}
	catch (...)
	{
		if(cb)cb->error(_("Caught unknown error, rethrowing..."));
		throw;
	}
	return true;
}

bool
Target_Scanline::add_frame(const synfig::Surface *surface, ProgressCallback *cb)
{
	assert(surface);

	if(!start_frame(cb))
	{
//		throw(string("add_frame(): target panic on start_frame()"));
		if (cb)
			cb->error(_("add_frame(): target panic on start_frame()"));
		return false;
	}

	if(!process_block_alpha(*surface, surface->get_w(), surface->get_h(), 0, cb)) return false;
	end_frame();
	return true;
}

bool
Target_Scanline::process_block_alpha(const synfig::Surface& surface, int width, int height, int yOffset, ProgressCallback* cb)
{
	int rowspan = sizeof(Color) * width;
	Surface::const_pen pen = surface.begin();

	Color bg = desc.get_bg_color();

	for(int y = 0; y < height; y++, pen.inc_y())
	{
		Color *colordata = start_scanline(y + yOffset);
		if(!colordata)
		{
			if(cb)
				cb->error(_("process_block_alpha(): call to start_scanline(y) returned nullptr"));
			return false;
		}

		switch(get_alpha_mode())
		{
			case TARGET_ALPHA_MODE_FILL:
				for(int i = 0; i < width; i++)
				{
					colordata[i] = Color::blend(surface[y][i], bg, 1.0f);
				}
				break;
			case TARGET_ALPHA_MODE_EXTRACT:
				for(int i = 0; i < width; i++)
				{
					float a = surface[y][i].get_a();
					colordata[i] = Color(a, a, a, a);
				}
				break;
			case TARGET_ALPHA_MODE_REDUCE:
				for(int i = 0; i < width; i++)
				{
					colordata[i] = surface[y][i];
					colordata[i].set_a(1.f);
				}
				break;
			case TARGET_ALPHA_MODE_KEEP:
				memcpy(colordata, surface[y], rowspan);
				break;
		}

		if(!end_scanline())
		{
			if(cb)
				cb->error(_("process_block_alpha(): target panic on end_scanline()"));
			return false;
		}
	}
	return true;
}
