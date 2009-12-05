#ifndef _YGE_INPUT_MANAGER_
#define _YGE_INPUT_MANAGER_


#include "YGEInputManager.h"
#include "YGELogger.h"

class YGEInputManager : public YGEInputManager {
public: 
	virtual void init(){

	}

/*+	virtual void update(){

	}
+*/
	void notifyEvent(SDL_Event *event){
		switch(event->type){
					case SDL_KEYDOWN:
						for(std::vector<YGEKeyDownListener*>::iterator iter = keydownlisteners.begin();
							iter != keydownlisteners.end();
							iter++){
								(*iter)->keyDown(event->key.keysym.sym);

						}
						break;
					case SDL_KEYUP:
						for(std::vector<YGEKeyUpListener*>::iterator iter = keyuplisteners.begin();
							iter != keyuplisteners.end();
							iter++){
								(*iter)->keyUp(event->key.keysym.sym);

						}
						break;
					case SDL_MOUSEMOTION:
						for(std::vector<YGEMouseMoveListener*>::iterator iter = mousemovelisteners.begin();
							iter != mousemovelisteners.end();
							iter++){
								(*iter)->mouseMoved(event->motion.xrel, event->motion.yrel);
								
						}
						break;
		}
	}

};

#endif