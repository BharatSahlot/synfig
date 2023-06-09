/* === S Y N F I G ========================================================= */
/*!	\file color.cpp
**	\brief Color Class implementation
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
**	Copyright (c) 2012-2013 Carlos López
**	Copyright (c) 2015 Diego Barrios Romero
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

#include "color.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <synfig/general.h>

#include "colorblendingfunctions.h"

#endif

using namespace synfig;

#define COLOR_EPSILON	(0.000001f)

/* === M E T H O D S ======================================================= */

ColorReal
Color::hex2real(String s)
{
	std::istringstream i(s);
	int n;
	i.fill('0');
	if (!(i >> std::hex >> n))
		throw String("bad conversion from hex string \"") + s + String("\"");
	return n / 255.0f;
}

const String
Color::real2hex(ColorReal c)
{
	std::ostringstream o;
	o.width(2);
	o.fill('0');
	if (c<0) c = 0;
	if (c>1) c = 1;
	o << std::hex << int(c*255.0f);
	return o.str();
}

void
Color::set_hex(String& str)
{
	value_type r, g, b;
	String hex;

	// use just the hex characters
	for (String::const_iterator iter = str.begin(); iter != str.end(); ++iter)
		if (isxdigit(*iter))
			hex.push_back(*iter);

	try
	{
		if (hex.size() == 1)
		{
			r = hex2real(hex.substr(0,1)+hex.substr(0,1));
			r_ = g_ = b_ = r;
		}
		else if (hex.size() == 3)
		{
			r = hex2real(hex.substr(0,1)+hex.substr(0,1));
			g = hex2real(hex.substr(1,1)+hex.substr(1,1));
			b = hex2real(hex.substr(2,1)+hex.substr(2,1));
			r_ = r; g_ = g; b_ = b;
		}
		else if (hex.size() == 6)
		{
			r = hex2real(hex.substr(0,2));
			g = hex2real(hex.substr(2,2));
			b = hex2real(hex.substr(4,2));
			r_ = r; g_ = g; b_ = b;
		}
	}
	catch (const std::string& s)
	{
		synfig::warning("caught <%s>\n", s.c_str());
		return;
	}
}

const String
Color::get_string(void)const
{
	std::ostringstream o;
	o << std::fixed << std::setprecision(3) << "#" << get_hex().c_str() << " : " << std::setw(6) << a_;
	return String(o.str());
}

Color
Color::clamped_negative()const
{
	Color ret=*this;

	if(ret.a_==0)
		return alpha();

	if(ret.a_<0)
		ret=-ret;

	if(ret.r_<0)
	{
		ret.g_-=ret.r_;
		ret.b_-=ret.r_;
		ret.r_=0.0f;
	}
	if(ret.g_<0)
	{
		ret.r_-=ret.g_;
		ret.b_-=ret.g_;
		ret.g_=0.0f;
	}
	if(ret.b_<0)
	{
		ret.r_-=ret.b_;
		ret.g_-=ret.b_;
		ret.b_=0.0f;
	}

	if(ret.r_>1) ret.r_=1;
	if(ret.g_>1) ret.g_=1;
	if(ret.b_>1) ret.b_=1;
	if(ret.a_>1) ret.a_=1;

	if(std::isnan(ret.get_r())) ret.r_=0.5;
	if(std::isnan(ret.get_g())) ret.g_=0.5;
	if(std::isnan(ret.get_b())) ret.b_=0.5;
	if(std::isnan(ret.get_a())) ret.a_=1;

/*
	if(ret.r_>1) { ret.g_/=ret.r_; ret.b_/=ret.r_; ret.r_=1; }
	if(ret.g_>1) { ret.r_/=ret.g_; ret.b_/=ret.g_; ret.g_=1; }
	if(ret.b_>1) { ret.g_/=ret.b_; ret.r_/=ret.b_; ret.b_=1; }
	if(ret.a_>1) ret.a_=1;
*/

	return ret;
}

Color
Color::clamped()const
{
	Color ret(*this);
	if(ret.get_r()<0)
		ret.set_r(0);
	if(ret.get_g()<0)
		ret.set_g(0);
	if(ret.get_b()<0)
		ret.set_b(0);
	if(ret.get_a()<0)
		ret.set_a(0);

	if(ret.r_>1) ret.r_=1;
	if(ret.g_>1) ret.g_=1;
	if(ret.b_>1) ret.b_=1;
	if(ret.a_>1) ret.a_=1;

	if(std::isnan(ret.get_r())) ret.r_=0.5;
	if(std::isnan(ret.get_g())) ret.g_=0.5;
	if(std::isnan(ret.get_b())) ret.b_=0.5;
	if(std::isnan(ret.get_a())) ret.a_=1;

	return(ret);
}

Color
Color::blend(Color a, Color b, float amount)
{
	if(fabsf(amount)<=COLOR_EPSILON) return b;
	return blendfunc_COMPOSITE(a, b, amount);
}


Color
Color::blend(Color a, Color b, float amount, Color::BlendMethod type)
{
	// No matter what blend method is being used,
	// if the amount is equal to zero, then only B
	// will shine through
	if(fabsf(amount)<=COLOR_EPSILON) return b;

	assert(type<BLEND_END);

	const static blendfunc vtable[BLEND_END]=
	{
		blendfunc_COMPOSITE<Color>,	// 0
		blendfunc_STRAIGHT<Color>,
		blendfunc_BRIGHTEN<Color>,
		blendfunc_DARKEN<Color>,
		blendfunc_ADD<Color>,
		blendfunc_SUBTRACT<Color>,		// 5
		blendfunc_MULTIPLY<Color>,
		blendfunc_DIVIDE<Color>,
		blendfunc_COLOR<Color>,
		blendfunc_HUE<Color>,
		blendfunc_SATURATION<Color>,	// 10
		blendfunc_LUMINANCE<Color>,
		blendfunc_BEHIND<Color>,
		blendfunc_ONTO<Color>,
		blendfunc_ALPHA_BRIGHTEN<Color>,
		blendfunc_ALPHA_DARKEN<Color>,	// 15
		blendfunc_SCREEN<Color>,
		blendfunc_HARD_LIGHT<Color>,
		blendfunc_DIFFERENCE<Color>,
		blendfunc_ALPHA_OVER<Color>,
		blendfunc_OVERLAY<Color>,		// 20
		blendfunc_STRAIGHT_ONTO<Color>,
		blendfunc_ADD_COMPOSITE<Color>,
		blendfunc_ALPHA<Color>,
	};

	return vtable[type](a,b,amount);
}

template<typename OP>
void blendfunc_buf(const Color* src, Color* dest, float amount, size_t n, OP op)
{
	for(size_t i = 0; i < n; i++)
	{
		dest[i] = op(src[i], dest[i], amount);
	}
}


void
Color::blend_buf(const Color *src, Color *dest, float amount, size_t n, const Color::BlendMethod type)
{
	if(fabsf(amount)<=COLOR_EPSILON) return;

	assert(type<BLEND_END);

	switch(type)
	{
		case BLEND_COMPOSITE:
			blendfunc_buf(src, dest, amount, n, blendfunc_COMPOSITE<Color>);
			break;
		case BLEND_STRAIGHT:
			blendfunc_buf(src, dest, amount, n, blendfunc_STRAIGHT<Color>);
			break;
		case BLEND_ONTO:
			blendfunc_buf(src, dest, amount, n, blendfunc_ONTO<Color>);
			break;
		case BLEND_STRAIGHT_ONTO:
			blendfunc_buf(src, dest, amount, n, blendfunc_STRAIGHT_ONTO<Color>);
			break;
		case BLEND_BEHIND:
			blendfunc_buf(src, dest, amount, n, blendfunc_BEHIND<Color>);
			break;
		case BLEND_SCREEN:
			blendfunc_buf(src, dest, amount, n, blendfunc_SCREEN<Color>);
			break;
		case BLEND_OVERLAY:
			blendfunc_buf(src, dest, amount, n, blendfunc_OVERLAY<Color>);
			break;
		case BLEND_HARD_LIGHT:
			blendfunc_buf(src, dest, amount, n, blendfunc_HARD_LIGHT<Color>);
			break;
		case BLEND_MULTIPLY:
			blendfunc_buf(src, dest, amount, n, blendfunc_MULTIPLY<Color>);
			break;
		case BLEND_DIVIDE:
			blendfunc_buf(src, dest, amount, n, blendfunc_DIVIDE<Color>);
			break;
		case BLEND_ADD:
			blendfunc_buf(src, dest, amount, n, blendfunc_ADD<Color>);
			break;
		case BLEND_ADD_COMPOSITE:
			blendfunc_buf(src, dest, amount, n, blendfunc_ADD_COMPOSITE<Color>);
			break;
		case BLEND_SUBTRACT:
			blendfunc_buf(src, dest, amount, n, blendfunc_SUBTRACT<Color>);
			break;
		case BLEND_DIFFERENCE:
			blendfunc_buf(src, dest, amount, n, blendfunc_DIFFERENCE<Color>);
			break;
		case BLEND_BRIGHTEN:
			blendfunc_buf(src, dest, amount, n, blendfunc_BRIGHTEN<Color>);
			break;
		case BLEND_DARKEN:
			blendfunc_buf(src, dest, amount, n, blendfunc_DARKEN<Color>);
			break;
		case BLEND_COLOR:
			blendfunc_buf(src, dest, amount, n, blendfunc_COLOR<Color>);
			break;
		case BLEND_HUE:
			blendfunc_buf(src, dest, amount, n, blendfunc_HUE<Color>);
			break;
		case BLEND_SATURATION:
			blendfunc_buf(src, dest, amount, n, blendfunc_SATURATION<Color>);
			break;
		case BLEND_LUMINANCE:
			blendfunc_buf(src, dest, amount, n, blendfunc_LUMINANCE<Color>);
			break;
		case BLEND_ALPHA_BRIGHTEN:
			blendfunc_buf(src, dest, amount, n, blendfunc_ALPHA_BRIGHTEN<Color>);
			break;
		case BLEND_ALPHA_DARKEN:
			blendfunc_buf(src, dest, amount, n, blendfunc_ALPHA_DARKEN<Color>);
			break;
		case BLEND_ALPHA_OVER:
			blendfunc_buf(src, dest, amount, n, blendfunc_ALPHA_OVER<Color>);
			break;
		case BLEND_ALPHA:
			blendfunc_buf(src, dest, amount, n, blendfunc_ALPHA<Color>);
			break;
	}
}

void
Color::blend_buf(Color *srcA, Color srcB, Color *dest, float amount, size_t n, const Color::BlendMethod type)
{
	for(size_t i = 0; i < n; i++) dest[i] = srcB;

	blend_buf(srcA, dest, amount, n, type);
}
