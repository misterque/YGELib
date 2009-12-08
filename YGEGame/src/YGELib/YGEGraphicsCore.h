#ifndef _YGE_DISPLAY_H_
#define _YGE_DISPLAY_H_

#include <SDL.h> 
#include <SDL_opengl.h> 

#include "YGEGraphicsContext.h"

namespace YGETimeSpace {
	class YGESpace;
	class YGEEntity;
	class YGEObserver;
}

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


#ifdef _DEBUG
#define FULLSCREEN false
#else
#define FULLSCREEN true
#endif

namespace YGECore {

	class YGEGraphicsCore {
	private:
		YGEGraphicsContext context;
		void renderEntity(YGETimeSpace::YGEEntity* entity);

		void createScreen();

		int screenw;
		int screenh;
		int isFullscreen;
		int depth;




		SDL_Surface *screen;

	public:
		int windowClosed;

		void renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer);


		YGEGraphicsCore();

		void setFullscreen(bool fullscreen);

		bool getFullscreen();

		void setResolution(int w, int h) ;

		void setDepth(int depth);

		void init();

		void reset();

		void notifyEvent(SDL_Event *event);

		void update();

		void setTitle(const char* title);
	};



}

#endif
