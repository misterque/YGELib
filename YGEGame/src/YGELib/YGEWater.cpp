#include <SDL_opengl.h>

#include "YGEWater.h"

namespace YGEGraphics {

	YGEWater::YGEWater(){

		texture = YGECore::YGERessourceManager::getInstance()->getTexture("textures/water.tex");

	}


	void YGEWater::draw(YGEGraphicsContext* context){

				glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		texture->bind();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(2000.0f, 2000.0f);
			glVertex3d(10000.0f, 10.0f, 10000.0f);

			glTexCoord2f(0.0f, 2000.0f);
			glVertex3d(-10000.0f, 10.0f, 10000.0f);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3d(-10000.0f, 10.0f, -10000.0f);

			glTexCoord2f(2000.0f, 0.0f);
			glVertex3d(10000.0f, 10.0f, -10000.0f);
			glEnd();

	}

}