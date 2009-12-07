#ifndef _YGE_GRAPHICS_CONTEXT_H_
#define _YGE_GRAPHICS_CONTEXT_H_

#include <SDL_opengl.h>

class YGEGraphicsContext {
public:
	int width, height;
	int depth;

	GLfloat cameraMatrix[16];

	void glGetCameraMatrix();

	void saveAsGlCameraRotation();

};

#endif