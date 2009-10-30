/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_ENTITY_H_
#define _YGE_ENTITY_H_

#include "YGEEntityAsset.h"
#include <list>


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
	 * parent of this entity. every entity can have just one
	 * parent. If this is NULL, this entity is considered to be
	 * a root entity.
	 */
	YGEEntity* parent;

public:
	/**
	 * add a child to the entity
	 */
	void addChild( YGEEntity* entity );

	/**
	 * remove a child
	 */
	void removeChild( YGEEntity* entity );

	std::list<YGEEntity*> getChildren(){
		return children;
	}
	/**
	 * add an asset to the entity
	 */
	void addAsset( YGEEntityAsset* asset );

	/**
	 * remove an assed
	 */
	void removeAsset( YGEEntityAsset* asset );

	std::list<YGEEntityAsset*> getAssets(){
		return assets;
	}



};

#endif