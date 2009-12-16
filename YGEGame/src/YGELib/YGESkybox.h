/**
* @file 
* @author Dirk Fortmeier
* @date 24.11.2009
*/

#ifndef _YGE_SKYBOX_H_
#define _YGE_SKYBOX_H_

#include "YGEResourceManager.h"

namespace YGEGraphics {
	/**
	 * @brief skybox for adding nice scenery backgrounds
	 */
	class YGESkybox {
	private:
		YGECore::YGETexture* up;
		YGECore::YGETexture* down;
		YGECore::YGETexture* front;
		YGECore::YGETexture* back;
		YGECore::YGETexture* left;
		YGECore::YGETexture* right;
	public:

		/**
		 * @param name name of the skybox textures, for example waterscape will be resolved to "skymaps/waterscape__positive_y.bmp" for the up-texture
		 */
		void loadTextures(const char* name);
		void draw();


	};

}
#endif 