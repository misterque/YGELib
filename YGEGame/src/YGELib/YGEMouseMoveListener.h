#ifndef _YGE_MOUSE_MOVE_LISTENER_H
#define _YGE_MOUSE_MOVE_LISTENER_H

#include <SDL.h>

namespace YGEInput {

	class YGEMouseMoveListener {
	public:
		virtual void mouseMoved(int x, int y) = 0;
	};
}

#endif