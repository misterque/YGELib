/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_ENTITY_H_
#define _YGE_ENTITY_H_

#include "YGEEntityAsset.h"
#include "YGEGraphicsAsset.h"
#include "YGEVector.h"
#include "YGEMatrix.h"
#include "YGEQuaternion.h"


#include <list>

namespace YGETimeSpace{

/**
 * Entity Class
 * represents an entity. Definiton from wikipedia:
 * "An entity is something that has a distinct, separate existence,
 *  though it need not be a material existence. ... An entity could
 *  be viewed as a set containing subsets. In philosophy, such sets
 *  are said to be abstract objects".
 * 
 * YGEEntities are abstract objects composed of other YGEEntities,
 * augmented by YGEEntityAssets which represents a perceptible
 * phenomenon. 
 *
 * Each YGEEntitiy has a pose (position and orientation) in space.
 *
 */



class YGEEntity {
private:
	/**
	 * the children of the entity
	 */
	std::list<YGEEntity*> children;

	/**
	 * the assets of this entity
	 */
	std::list<YGEEntityAsset*> assets;

	/**
	 * renderable graphics assets of this entity
	 */
	std::list<YGEGraphics::YGEGraphicsAsset*> graphicAssets;


	/**
	 * parent of this entity. every entity can have just one
	 * parent. If this is NULL, this entity is considered to be
	 * a root entity.
	 */
	YGEEntity* parent;

	YGEMath::Vector3 position;
	YGEMath::Vector3 scale;
	YGEMath::Quaternion orientation;

public:


	YGEEntity();

	/**
	 * add a child to the entity
	 */
	void addChild( YGEEntity* entity );

	/**
	 * remove a child
	 */
	void removeChild( YGEEntity* entity );

	/**
	 * get all the entities attached to this children
	 */
	std::list<YGEEntity*> getChildren(){
		return children;
	}

	YGEEntity* getParent(){
		return parent;
	}
	/**
	 * add an asset to the entity
	 */
	void addAsset( YGEEntityAsset* asset );

	/**
	 * remove an assed
	 */
	void removeAsset( YGEEntityAsset* asset );

	/**
	 * returns all assets assigned to this entity
	 */
	std::list<YGEEntityAsset*> getAssets(){
		return assets;
	}

	/**
	 * returns all assets that are graphical assets,
	 * meaning they are derived from YGEGraphicsAsset.
	 * will be called by the scene graphical renderer to
	 * just get the assests which are renderable
	 */
	std::list<YGEGraphics::YGEGraphicsAsset*> getGraphicsAssets(){
		return graphicAssets;
	}

	YGEMath::Vector3 getPosition(){
		return position;
	}

	YGEMath::Vector3 getScale(){
		return scale;
	}

	YGEMath::Quaternion getOrientation(){
		return orientation;
	}

	void setPosition(const YGEMath::Vector3 &pos){
		position = pos;
	}

	void setScale(const YGEMath::Vector3 &sca){
		scale = sca;
	}

	void setOrientation(const YGEMath::Quaternion &q){
		orientation = q;
	}
	void render();

};

}

#endif