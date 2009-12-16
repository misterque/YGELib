#ifndef _YGE_GRAPHICS_CONTEXT_H_
#define _YGE_GRAPHICS_CONTEXT_H_

#include <SDL_opengl.h>

/**
 * @brief graphics context which holds information about
 * the render surface and the current camera transformations
 */
class YGEGraphicsContext {
public:
	int width, height;
	int depth;

	GLfloat cameraMatrix[16];

	/**
	 * @brief grabs the current open gl
	 */
	void glGetCameraMatrix();

	void saveAsGlCameraRotation();

};

#endif