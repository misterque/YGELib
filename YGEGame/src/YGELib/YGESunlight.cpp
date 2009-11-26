#include "YGESunlight.h"
#include <SDL_opengl.h>

namespace YGEGraphics {

	void YGESunlight::draw() {

		GLfloat dir[] = {1,1,1,0};
		glLightfv(GL_LIGHT0, GL_POSITION, dir);	
			/*GLfloat ambient = {
GLfloat diffuse = 
GLfloat specular = 
		GLFl

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);*/
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
	}

}