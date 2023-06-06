/* === S Y N F I G ========================================================= */
/*!	\file synfig/rendering/common/optimizer/optimizersplit.cpp
**	\brief OptimizerSplit
**
**	\legal
**	......... ... 2015-2018 Ivan Mahonin
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

#include <synfig/general.h>
#include <synfig/localization.h>

#include "../task/tasktile.h"
#include "../../software/task/tasksw.h"
#include "optimizersplit.h"

#endif

using namespace synfig;
using namespace rendering;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

OptimizerSplit::OptimizerSplit()
{
	category_id = CATEGORY_ID_LIST;
	depends_from = CATEGORY_SPECIALIZED;
	// affects_to = CATEGORY_ID_SPECIALIZED;
	for_list = true;
}


void
OptimizerSplit::run(const RunParams &params) const
{
	if (!params.list) return;
	const int tile_height = 500;
	for(Task::List::iterator i = params.list->begin(); i != params.list->end(); ++i)
	{
		if (TaskInterfaceSplit *split = i->type_pointer<TaskInterfaceSplit>())
		if (split->is_splittable())
		{
			TaskTile::Handle tile(new TaskTile());
			// tile = tile->convert_to(TaskSW::mode_token.handle());

			Task::List list = tile->create_tiles(*i, tile_height);
			if(list.empty()) continue;

			*i = tile->convert_to(TaskSW::mode_token.handle());

			params.list->insert(i, list.begin(), list.end());

			i += list.size();

			apply(params);
		}
	}
}

/* === E N T R Y P O I N T ================================================= */
