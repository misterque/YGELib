#ifndef _YGE_KEY_UP_LISTENER_H
#define _YGE_KEY_UP_LISTENER_H

#include <SDL.h>

class YGEKeyUpListener {
public:
	virtual void keyUp(SDLKey key) = 0;
};


#endif