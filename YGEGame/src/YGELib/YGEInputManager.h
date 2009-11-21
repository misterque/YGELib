#ifndef _YGE_SDL_INPUT_MANAGER_
#define _YGE_SDL_INPUT_MANAGER_

#include "YGEKeyDownListener.h"
#include "YGEKeyUpListener.h"
#include "YGEMouseMoveListener.h"

#include <vector>

class YGEInputManager {
protected:
	std::vector<YGEKeyDownListener*> keydownlisteners;
	std::vector<YGEKeyUpListener*> keyuplisteners;
	std::vector<YGEMouseMoveListener*> mousemovelisteners;

public:
	/*+ virtual void update() = 0; +*/
	virtual void init() = 0;

	void addKeyDownListener(YGEKeyDownListener* listener){
		keydownlisteners.push_back(listener);
	}

	void addKeyUpListener(YGEKeyUpListener* listener){
		keyuplisteners.push_back(listener);
	}

	void addMouseMoveListener(YGEMouseMoveListener* listener){
		mousemovelisteners.push_back(listener);
	}
};


#endif