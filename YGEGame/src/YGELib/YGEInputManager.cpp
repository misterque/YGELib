#include "YGEInputManager.h"

namespace YGEInput {


	void YGEInputManager::init(){

	}

	void YGEInputManager::notifyEvent(SDL_Event *event){
		switch(event->type){
					case SDL_KEYDOWN:
						copyKeydownlisteners = keydownlisteners;
						for(std::list<YGEKeyDownListener*>::iterator iter = copyKeydownlisteners.begin();
							iter != copyKeydownlisteners.end();
							iter++){
								(*iter)->keyDown(event->key.keysym.sym);

						}
						break;
					case SDL_KEYUP:
						copyKeyuplisteners = keyuplisteners;
						for(std::list<YGEKeyUpListener*>::iterator iter = copyKeyuplisteners.begin();
							iter != copyKeyuplisteners.end();
							iter++){
								(*iter)->keyUp(event->key.keysym.sym);

						}
						break;
					case SDL_MOUSEMOTION:
						copyMousemovelisteners = mousemovelisteners;
						for(std::list<YGEMouseMoveListener*>::iterator iter = copyMousemovelisteners.begin();
							iter != copyMousemovelisteners.end();
							iter++){
								(*iter)->mouseMoved(event->motion.xrel, event->motion.yrel);

						}
						break;
		}
	}


	void YGEInputManager::addKeyDownListener(YGEKeyDownListener* listener){
		keydownlisteners.push_back(listener);
	}

	void YGEInputManager::addKeyUpListener(YGEKeyUpListener* listener){
		keyuplisteners.push_back(listener);
	}

	void YGEInputManager::addMouseMoveListener(YGEMouseMoveListener* listener){
		mousemovelisteners.push_back(listener);
	}

	void YGEInputManager::removeKeyDownListener(YGEKeyDownListener* listener){
		keydownlisteners.remove(listener);
	}

	void YGEInputManager::removeKeyUpListener(YGEKeyUpListener* listener){
		keyuplisteners.remove(listener);

	}

	void YGEInputManager::removeMouseMoveListener(YGEMouseMoveListener* listener){
		mousemovelisteners.remove(listener);

	}

}