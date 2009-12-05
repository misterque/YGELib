#ifndef _YGE_SDL_DISPLAY_H_
#define _YGE_SDL_DISPLAY_H_

#include <SDL.h> // main SDL header
#include <SDL_opengl.h> 
#include "YGELogger.h"
#include "YGEGraphicsCore.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


#ifdef _DEBUG
#define FULLSCREEN false
#else
#define FULLSCREEN true
#endif

namespace YGECore {


	class YGESDLDisplay : public YGEGraphicsCore {

		int screenw;
		int screenh;
		int fullscreen;
		int depth;




		SDL_Surface *screen;
	public:

		YGESDLDisplay(){
			screenw = SCREEN_WIDTH;
			screenh = SCREEN_HEIGHT;
			fullscreen = FULLSCREEN;
			depth = 0;
			windowClosed = 1;
		}

		virtual void setFullscreen(bool fullscreen) {

		}
		virtual void setResolution(int w, int h) {

		}
		virtual void setDepth(int depth) {

		}

		virtual void init(){

			YGELogger::getInstance()->log("Initializing Display");
			
			Uint32 flags;
			if(fullscreen) {
				flags = SDL_OPENGL | SDL_FULLSCREEN;
			} else {
				flags = SDL_OPENGL;
			}

			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

			screen = SDL_SetVideoMode(screenw, screenh, 16, flags);
			if (screen == NULL) {
				YGELogger::getInstance()->log("Setting Video Mode Failed");
				fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
				return;
			}
			windowClosed = 0;

			return;

		}

		virtual void reset(){

			SDL_GL_SwapBuffers();

			glEnable( GL_TEXTURE_2D );

			glEnable(GL_DEPTH_TEST);

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

			glViewport( 0, 0, 640, 480 );

			glClear( GL_COLOR_BUFFER_BIT );
			glClear( GL_DEPTH_BUFFER_BIT );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();

			glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);

			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();

		}

		void notifyEvent(SDL_Event *event){
			switch(event->type){
			case SDL_QUIT:
				windowClosed = 1;
				break;
			}

		}

		virtual void update(){
		}

		virtual void setTitle(const char* title){
			SDL_WM_SetCaption(title,title);
		}
	};

}

#endif