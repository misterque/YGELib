/** @file
* @author Dirk Fortmeier
* @date 3.11.2009
*/

#ifndef _YGE_GRAPHICS_ASSET_H_
#define _YGE_GRAPHICS_ASSET_H_


#include "YGEEntityAsset.h"


namespace YGEGraphics {
	/**
	 * @brief a graphical asset which can be rendered
	 */
	class YGEGraphicsAsset : public YGETimeSpace::YGEEntityAsset {
	public:
		virtual void draw(YGEGraphicsContext* context) = 0;

		virtual YGETimeSpace::AssetType getAssetType(){
			return YGETimeSpace::Graphical;
		}


	};

	/**
	 * @brief a simple box
	 */
	class YGESimpleBox : public YGEGraphicsAsset {
	public:
		virtual void draw(YGEGraphicsContext* context);


	};

}

#endif