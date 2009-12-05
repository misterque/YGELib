/**
 * @file 
 * @author Dirk Fortmeier
 * @date 24.11.2009
 */

#ifndef _YGE_SKYBOX_H_
#define _YGE_SKYBOX_H_

#include "YGERessourceManager.h"

namespace YGEGraphics {

class YGESkybox {
private:
	YGECore::YGETexture* up;
	YGECore::YGETexture* down;
	YGECore::YGETexture* front;
	YGECore::YGETexture* back;
	YGECore::YGETexture* left;
	YGECore::YGETexture* right;
public:

	void loadTextures();
	void draw();


};

}
#endif 