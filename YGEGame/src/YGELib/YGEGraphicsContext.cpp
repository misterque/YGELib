#include "YGEGraphicsContext.h"
#include <SDL_opengl.h>

void YGEGraphicsContext::glGetCameraMatrix(){
	glLoadMatrixf(cameraMatrix);
}

void YGEGraphicsContext::saveAsGlCameraRotation(){
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraMatrix);
	glLoadMatrixf(cameraMatrix);
}
