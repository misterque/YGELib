/** @file
* @author Dirk Fortmeier
* @date 3.11.2009
*/

#ifndef _YGE_GRAPHICS_ASSET_H_
#define _YGE_GRAPHICS_ASSET_H_


#include "YGEEntityAsset.h"


namespace YGEGraphics {
	class YGEGraphicsAsset : public YGETimeSpace::YGEEntityAsset {
	public:
		virtual void draw(YGEGraphicsContext* context) = 0;

		virtual YGETimeSpace::AssetType getAssetType(){
			return YGETimeSpace::Graphical;
		}
	};

	class YGESimpleBox : public YGEGraphicsAsset {
	public:
		virtual void draw(YGEGraphicsContext* context);


	};

}

#endif