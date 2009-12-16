/**
* @file
* @author Dirk Fortmeier
* @date ?
*/

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

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


#ifdef _DEBUG
#define FULLSCREEN false
#else
#define FULLSCREEN true
#endif

namespace YGECore {

	/**
	* @brief core class for all rendering stuff
	*/
	class YGEGraphicsCore {
	private:
		YGEGraphicsContext context;
		void renderEntity(YGETimeSpace::YGEEntity* entity);

		/**
		* @brief create a rendering surface
		*/
		void createScreen();

		int screenw;
		int screenh;
		bool isFullscreen;
		int depth;

		SDL_Surface *screen;

	public:
		/**
		* @brief will be true if the rendering window has been closed
		*
		* if true, engine will shutdown
		*/
		bool windowClosed;


		/**
		* tells the graphics core to render a space frow the POV of a
		* certain observer
		*/
		void renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer);


		YGEGraphicsCore();

		/**
		* since SDL creates a new opengl context on windows
		* every time the windows is resized or fullscreen is toggled
		* this is only supported before calling init();
		* @note functionality not guaranteed
		*/
		void setFullscreen(bool fullscreen);

		bool getFullscreen();

		/**
		* @see setFullscreen();
		*/
		void setResolution(int w, int h) ;

		void setDepth(int depth);

		/**
		* @brief initialise this subsystem
		*/
		void init();

		/**
		* @brief reset the rendering surface
		*/
		void reset();


		/**
		* if the SDL_QUIT event is passed to this function
		* the variable windowClosed will be set to true
		* and the engine will stop
		* @see windowClosed
		*/
		void notifyEvent(SDL_Event *event);


		/**
		* does actually nothing
		*/
		void update();

		/**
		* sets the window title
		*/
		void setTitle(const char* title);
	};



}

#endif
