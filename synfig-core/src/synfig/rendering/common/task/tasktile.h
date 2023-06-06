#ifndef  __SYNFIG_RENDERING_TASKTILE_H
#define __SYNFIG_RENDERING_TASKTILE_H

#include "tasktransformation.h"

namespace synfig
{
namespace rendering
{

class TaskTile : public Task
{
public:
	typedef etl::handle<TaskTile> Handle;
	SYNFIG_EXPORT static Token token;
	virtual Token::Handle get_token() const { return token.handle(); }

	Task::List create_tiles(Task::Handle orig_task, int tile_height);

protected:
	int tile_height;
};

}
}

#endif
