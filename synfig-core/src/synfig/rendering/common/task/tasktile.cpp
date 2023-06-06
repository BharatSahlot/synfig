#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "tasktile.h"
#include <algorithm>

#endif

using namespace synfig;
using namespace rendering;

Task::Token TaskTile::token(DescAbstract<TaskTile>("TaskTile"));


Task::List
TaskTile::create_tiles(Task::Handle orig_task, int tile_height)
{
	int my = orig_task->target_rect.maxy;
	int y = orig_task->target_rect.miny;

	if(((float)(my - y) / tile_height) < 1.5f) return Task::List();

	SurfaceResource::Handle orig_surface = orig_task->target_surface;
	assign_target(*orig_task);

	Task::List list;

	int index = 0;
	for(; y < my; y += tile_height)
	{
		Task::Handle task = orig_task->clone();
		task->target_surface = new SurfaceResource();
		task->target_surface->create(task->target_rect.maxx, task->target_rect.maxy);
		task->trunc_target_rect( RectInt(orig_task->target_rect.minx, y, orig_task->target_rect.maxx, std::min(y + tile_height, my)) );

		TaskSurface::Handle surface(new TaskSurface());
		surface->assign_target(*task);

		sub_task(index++) = surface;
		list.push_back(task);
	}

	this->tile_height = tile_height;
	return list;
}
