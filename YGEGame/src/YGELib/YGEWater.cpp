#include <SDL_opengl.h>

#include "YGEWater.h"

namespace YGEGraphics {

	YGEWater::YGEWater(){

	}


	void YGEWater::draw(YGEGraphicsContext* context){

				glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
			glVertex3d(10000.0f, 10.0f, 10000.0f);
			glVertex3d(-10000.0f, 10.0f, 10000.0f);
			glVertex3d(-10000.0f, 10.0f, -10000.0f);
			glVertex3d(10000.0f, 10.0f, -10000.0f);
			glEnd();

	}

}