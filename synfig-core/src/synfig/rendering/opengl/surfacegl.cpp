/* === S Y N F I G ========================================================= */
/*!	\file synfig/rendering/opengl/surfacegl.cpp
**	\brief SurfaceGL
**
**	\legal
**	......... ... 2015-2018 Ivan Mahonin
**	......... ... 2023 Bharat Sahlot
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

#include "surfacegl.h"
#endif

using namespace synfig;
using namespace rendering;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */


rendering::Surface::Token SurfaceGL::token(
	Desc<SurfaceGL>("SurfaceGL") );

SurfaceGL::SurfaceGL() {}

SurfaceGL::SurfaceGL(const Surface &other)
{
	assign(other);
}

SurfaceGL::~SurfaceGL()
{
	reset();
}

bool
SurfaceGL::create_vfunc(int width, int height)
{
	return false;
}

bool
SurfaceGL::assign_vfunc(const rendering::Surface &surface)
{
	return false;
}

bool
SurfaceGL::clear_vfunc()
{
	return false;
}

bool
SurfaceGL::reset_vfunc()
{
	return false;
}

const Color*
SurfaceGL::get_pixels_pointer_vfunc() const
{
	return nullptr;
}

/* === E N T R Y P O I N T ================================================= */
