#ifndef _YGE_INPUT_MANAGER_
#define _YGE_INPUT_MANAGER_


#include "YGEInputManager.h"
#include "YGELogger.h"

class YGESDLInputManager : public YGEInputManager {
public: 
	virtual void init(){

	}

	virtual void update(){

	}

	void notifyEvent(SDL_Event *event){
		switch(event->type){
					case SDL_KEYDOWN:
						for(std::vector<YGEKeyDownListener*>::iterator iter = keydownlisteners.begin();
							iter != keydownlisteners.end();
							iter++){
								YGECore::YGELogger::getInstance()->log("ballalsasd-------------------------------");

								(*iter)->keyDown(event->key.keysym.sym);

						}
						break;
		}
	}

};

#endif