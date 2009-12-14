#include "YGEGraphicsCore.h"
#include <SDL_opengl.h>
#include "YGESpace.h"
#include "YGEObserver.h"
#include "YGELogger.h"





namespace YGECore {
	void YGEGraphicsCore::renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer){

		// draw a skybox
		if(space->hasSkybox()){
			observer->setCameraMatrixRotation(space->getRootEntity());

			space->getSkybox()->draw();
		}

		//draw the scene
		observer->setCameraMatrix(space->getRootEntity());
		context.saveAsGlCameraRotation();
		space->getSunlight()->draw();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);


		renderEntity(space->getRootEntity());

	}


	void YGEGraphicsCore::renderEntity(YGETimeSpace::YGEEntity* entity){


		glEnable(GL_LIGHTING);

		YGEMath::Vector3 pos = entity->getPosition();
		YGEMath::Vector3 scale = entity->getScale();

		glPushMatrix();

		glTranslated(entity->interpolatedPosition.x, entity->interpolatedPosition.y, entity->interpolatedPosition.z);

		YGEMath::Mat3x3 mat = entity->interpolatedOrientation.getRotationMatrix();

		GLfloat m[16] = { (GLfloat)mat[0][0], (GLfloat)mat[1][0], (GLfloat)mat[2][0], 0.0f,
			(GLfloat)mat[0][1], (GLfloat)mat[1][1], (GLfloat)mat[2][1], 0.0f,
			(GLfloat)mat[0][2], (GLfloat)mat[1][2], (GLfloat)mat[2][2], 0.0f,
			0,         0,         0,         1.0f };


		glMultMatrixf(m);

		//glScalef(scale.x, scale.y, scale.z);

		// get every graphical asset and render it
		std::list<YGEGraphics::YGEGraphicsAsset*>* assets = entity->getGraphicsAssets();
		for(std::list<YGEGraphics::YGEGraphicsAsset*>::iterator iter = assets->begin();
			iter != assets->end();
			iter++){



				(*iter)->draw(&context);

		}
		glPopMatrix();

		// recursive call on all children
		std::list<YGETimeSpace::YGEEntity*>* children = entity->getChildren();
		for(std::list<YGETimeSpace::YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				renderEntity(*iter);

		}
	}


	void YGEGraphicsCore::createScreen(){

		Uint32 flags;

		if(isFullscreen) {
			flags = SDL_OPENGL | SDL_FULLSCREEN;
		} else {
			flags = SDL_OPENGL;
		}

		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		screen = SDL_SetVideoMode(screenw, screenh, 16, flags);

		//YGERessourceManager::getInstance()->reloadGraphics();
	}

	YGEGraphicsCore::YGEGraphicsCore(){
		screenw = SCREEN_WIDTH;
		screenh = SCREEN_HEIGHT;
		isFullscreen = FULLSCREEN;
		depth = 0;
		windowClosed = 1;
	}

	void YGEGraphicsCore::setFullscreen(bool fullscreen) {
		if(fullscreen != isFullscreen) {
			SDL_WM_ToggleFullScreen(screen);
		}
		isFullscreen = fullscreen;

	}

	bool YGEGraphicsCore::getFullscreen() {
		return isFullscreen;
	}

	void YGEGraphicsCore::setResolution(int w, int h) {
		screenw = w;
		screenh = h;

	}
	void YGEGraphicsCore::setDepth(int depth) {

	}

	void YGEGraphicsCore::init(){

		YGELogger::getInstance()->log("Initializing Display");



		createScreen();

		if (screen == NULL) {
			YGELogger::getInstance()->log("Setting Video Mode Failed");
			throw YGEExceptionSubsystemError(std::string(SDL_GetError()));
			return;
		}
		windowClosed = 0;

		return;

	}

	void YGEGraphicsCore::reset(){

		SDL_GL_SwapBuffers();

		glEnable( GL_TEXTURE_2D );

		glEnable(GL_DEPTH_TEST);

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

		glViewport( 0, 0, screenw, screenh );

		glClear( GL_COLOR_BUFFER_BIT );
		glClear( GL_DEPTH_BUFFER_BIT );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

	}

	void YGEGraphicsCore::notifyEvent(SDL_Event *event){
		switch(event->type){
			case SDL_QUIT:
				windowClosed = 1;
				break;
		}

	}

	void YGEGraphicsCore::update(){
	}

	void YGEGraphicsCore::setTitle(const char* title){
		SDL_WM_SetCaption(title,title);
	}

}