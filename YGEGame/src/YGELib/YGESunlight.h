/**
 * @file 
 * @author Dirk Fortmeier
 * @date 25.11.2009
 */

#ifndef _YGE_SUNLIGHT_H_
#define _YGE_SUNLIGHT_H_

#include "YGEVector.h"
namespace YGEGraphics {

class YGESunlight {
private:

	float red;
	float blue;
	float green;

	YGEMath::Vector3 direction;
public:
	void setDirection(YGEMath::Vector3 &dir){
		direction = dir;
	}

	void setColor(float r, float b, float g){
		red = r;
		blue = b;
		green = g;
	}


	void draw();


};

}
#endif 