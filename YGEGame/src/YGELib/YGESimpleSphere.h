/**
 * @file
 * @author Dirk Fortmeier
 * @date 29.11.2009
 */

#ifndef _YGE_SIMPLE_SPHERE_
#define _YGE_SIMPLE_SPHERE_

#include <SDL_opengl.h>
#include "YGEGraphicsAsset.h"

namespace YGEGraphics {


	/**
	 * @brief a simple sphere using GLU quadrics
	 */
	class YGESimpleSphere : public YGEGraphicsAsset {
	private:
		double red;
		double blue;
		double green;

		double radius;


		GLUquadricObj *quadric;
		
	public:
		YGESimpleSphere();
		virtual void draw(YGEGraphicsContext* context);

		void setColor(double r, double b, double g);
		void setRadius(double r);

	};

}

#endif