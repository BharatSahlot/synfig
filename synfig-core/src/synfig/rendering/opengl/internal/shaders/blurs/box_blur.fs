/* === S Y N F I G ========================================================= */
/*!	\file synfig/rendering/opengl/internal/glsl/blurs/box_blur.fs
**	\brief Box Blur Fragment Shader
**
**	\legal
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

#version 330 core

uniform sampler2D tex;

uniform ivec2 size;
// uniform ivec4 rect;
uniform bool horizontal;

layout (location = 0) out vec4 out_color;

void main()
{
	ivec2 coord = ivec2(floor(gl_FragCoord));

    if(horizontal) {
        int minx = coord.x - size.x;
        int maxx = coord.x + size.x;

        int total = 0;
        vec4 sum = vec4(0);
        for(int x = minx; x <= maxx; x++, total++)
        {
            sum += texelFetch(tex, ivec2(x, coord.y), 0);
        }
        sum /= total;
        out_color = sum;
    } else {
        int miny = coord.y - size.y;
        int maxy = coord.y + size.y;

        int total = 0;
        vec4 sum = vec4(0);
        for(int y = miny; y <= maxy; y++, total++)
        {
            sum += texelFetch(tex, ivec2(coord.x, y), 0);
        }
        sum /= total;
        out_color = sum;
    }
}
