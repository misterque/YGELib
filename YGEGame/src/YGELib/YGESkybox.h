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
	YGECore::Texture* up;
	YGECore::Texture* down;
	YGECore::Texture* front;
	YGECore::Texture* back;
	YGECore::Texture* left;
	YGECore::Texture* right;
public:

	void loadTextures();
	void draw();


};

}
#endif 