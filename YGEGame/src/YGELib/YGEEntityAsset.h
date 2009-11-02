/** @file
 * @author Dirk Fortmeier
 */


#ifndef _YGE_ENTITY_ASSET_H_
#define _YGE_ENTITY_ASSET_H_

namespace YGETimeSpace{
enum AssetType { 
		Standard,
		Graphical,
		Sound,
		Physics,
		ETC
	};

class YGEEntityAsset {

public:
	virtual AssetType getAssetType(){
		return Standard;
	}

};


class YGEGraphicsAsset : public YGEEntityAsset {
public:
	virtual void draw() = 0;
	
	virtual AssetType getAssetType(){
		return Graphical;
	}
};

class YGESimpleBox : public YGEGraphicsAsset {
public:
	virtual void draw();


};
}
#endif