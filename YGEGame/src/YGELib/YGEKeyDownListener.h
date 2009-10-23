#ifndef _YGE_KEY_DOWN_LISTENER_H
#define _YGE_KEY_DOWN_LISTENER_H

#include <SDL.h>

class YGEKeyDownListener {
public:
	virtual void keyDown(SDLKey key) = 0;
};


#endif