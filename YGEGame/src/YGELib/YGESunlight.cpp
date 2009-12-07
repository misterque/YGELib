#include "YGESunlight.h"
#include <SDL_opengl.h>

namespace YGEGraphics {

	void YGESunlight::draw() {

		GLfloat dir[] = {1,1,1,0};
		glLightfv(GL_LIGHT0, GL_POSITION, dir);	

		GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
	}

}