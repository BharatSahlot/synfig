#include "synfig/color/color.h"
#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "../../common/task/tasktile.h"
#include "tasksw.h"

#endif

using namespace synfig;
using namespace rendering;

namespace {

class TaskTileSW: public TaskTile, public TaskSW
{
public:
	typedef etl::handle<TaskTileSW> Handle;
	static Token token;
	virtual Token::Handle get_token() const { return token.handle(); }

	virtual bool run(RunParams&) const {
		if(!is_valid()) return false;

		LockWrite ldst(this);
		if(!ldst) return false;

		synfig::Surface& surface = ldst->get_surface();
		synfig::Surface::pen p = surface.get_pen(target_rect.minx, target_rect.miny);

		int my = target_rect.maxy;
		int y = target_rect.miny;

		for(int i = 0; y < my; i++, y += tile_height)
		{
			LockRead lb(sub_task(i));
			if(!lb) return false;

			lb.cast_handle()->get_surface().blit_to(
				p,
				target_rect.minx,
				y,
				target_rect.get_width(),
				tile_height < my - y ? tile_height : my - y
			);
		}

		return true;
	}
};

Task::Token TaskTileSW::token(
	DescReal<TaskTileSW, TaskTile>("TaskTileSW") );

}
