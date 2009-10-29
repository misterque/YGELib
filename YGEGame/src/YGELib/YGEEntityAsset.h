/** @file
 * @author Dirk Fortmeier
 */


#ifndef _YGE_ENTITY_ASSET_H_
#define _YGE_ENTITY_ASSET_H_

class YGEEntityAsset {

};


class YGEGraphicsAsset : public YGEEntityAsset {
	virtual void draw() = 0;
};

class YGESimpleBox : public YGEGraphicsAsset {
	virtual void draw();


};

#endif