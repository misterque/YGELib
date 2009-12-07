#include "YGESunlight.h"
#include <SDL_opengl.h>

namespace YGEGraphics {

	void YGESunlight::draw() {

		GLfloat dir[] = {1,1,1,0};
		GLfloat diff[] = {red, blue, green, 1.0f };
		GLfloat ambient[] = {red/3.0f, blue/3.0f, green/3.0f, 1.0f };
		
		glLightfv(GL_LIGHT0, GL_POSITION, dir);	
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
	}

}