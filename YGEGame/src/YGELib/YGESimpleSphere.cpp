#include "YGESimpleSphere.h"
#include <SDL_opengl.h>

namespace YGEGraphics {
	YGESimpleSphere::YGESimpleSphere() : red(1.0f), blue(0.0f), green(0.0f), radius(1.0f){

		quadric = gluNewQuadric();
		gluQuadricNormals(quadric, GLU_OUTSIDE);
	}

	void YGESimpleSphere::setColor(double r, double b, double g){
		red = r;
		blue = b;
		green = g;
	}

	void YGESimpleSphere::setRadius(double r){
		radius = r;
	}

	void YGESimpleSphere::draw(YGEGraphicsContext* context){
		glDisable(GL_TEXTURE_2D);

		glColor3d(red, green, blue);

		gluSphere(quadric, radius, 16, 8);

	}

}