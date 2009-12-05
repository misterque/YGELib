#ifndef _YGE_SDL_INPUT_MANAGER_
#define _YGE_SDL_INPUT_MANAGER_

#include "YGEKeyDownListener.h"
#include "YGEKeyUpListener.h"
#include "YGEMouseMoveListener.h"

#include <list>

class YGEInputManager {
protected:
	std::list<YGEKeyDownListener*> keydownlisteners;
	std::list<YGEKeyUpListener*> keyuplisteners;
	std::list<YGEMouseMoveListener*> mousemovelisteners;

	std::list<YGEKeyDownListener*> copyKeydownlisteners;
	std::list<YGEKeyUpListener*> copyKeyuplisteners;
	std::list<YGEMouseMoveListener*> copyMousemovelisteners;

public:
	/*+ virtual void update() = 0; +*/

	/** @todo remove SDLInputManager **/
	virtual void init();

	void notifyEvent(SDL_Event *event);

	void addKeyDownListener(YGEKeyDownListener* listener);

	void addKeyUpListener(YGEKeyUpListener* listener);

	void addMouseMoveListener(YGEMouseMoveListener* listener);

	void removeKeyDownListener(YGEKeyDownListener* listener);

	void removeKeyUpListener(YGEKeyUpListener* listener);

	void removeMouseMoveListener(YGEMouseMoveListener* listener);

};


#endif