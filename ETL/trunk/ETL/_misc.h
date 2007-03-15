/*! ========================================================================
** Extended Template and Library
** Misc
** $Id: _misc.h,v 1.1.1.1 2005/01/04 01:31:47 darco Exp $
**
** Copyright (c) 2002 Robert B. Quattlebaum Jr.
**
** This package is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 2 of
** the License, or (at your option) any later version.
**
** This package is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** === N O T E S ===========================================================
**
** ========================================================================= */

/* === S T A R T =========================================================== */

#ifndef __ETL__MISC_H_
#define __ETL__MISC_H_

/* === H E A D E R S ======================================================= */
#include <cmath>

#include <math.h>

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

_ETL_BEGIN_NAMESPACE

template<typename I, typename T> inline I
binary_find(I begin, I end, const T& value)
{
#if 1
	I iter(begin+(end-begin)/2);

	while(end-begin>1 && !(*iter==value))
	{
		((*iter<value)?begin:end) = iter;

		iter = begin+(end-begin)/2;
	}
	return iter;
#else
	size_t len_(end-begin);
	size_t half_(len_/2);

	I iter(begin);
	iter+=half_;

	while(len_>1 && !(*iter==value))
	{
		((*iter<value)?begin:end) = iter;

		len_=half_;
		half_/=2;

		iter=begin;
		iter+=half_;
	}
	return iter;
#endif
}

inline int round_to_int(const float x) {
	/*!	\fixme Isn't there some x86 FPU instruction for quickly
	**	converting a float to a rounded integer? It's worth
	**	looking into at some point... */
	return static_cast<int>(x+0.5f);
}
inline int round_to_int(const double x) { return static_cast<int>(x+0.5); }

inline int ceil_to_int(const float x) { return static_cast<int>(ceil(x)); }
inline int ceil_to_int(const double x) { return static_cast<int>(ceil(x)); }

inline int floor_to_int(const float x) { return static_cast<int>(x); }
inline int floor_to_int(const double x) { return static_cast<int>(x); }

_ETL_END_NAMESPACE

/* === E X T E R N S ======================================================= */

/* === E N D =============================================================== */

#endif
