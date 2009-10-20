#ifndef _YGE_INPUT_MANAGER_
#define _YGE_INPUT_MANAGER_


#include "YGEInputManager.h"

class YGESDLInputManager : public YGEInputManager {
public: 
	virtual void init(){

	}

	virtual void update(){
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			switch(event.type){
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				break;
			}
		}

	}

};

#endif