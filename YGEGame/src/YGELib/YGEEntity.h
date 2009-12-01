/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_ENTITY_H_
#define _YGE_ENTITY_H_

#include "YGEEntityAsset.h"
#include "YGEGraphicsAsset.h"
#include "YGEPhysicsAsset.h"
#include "YGEVector.h"
#include "YGEMatrix.h"
#include "YGEQuaternion.h"

#include <list>

namespace YGETimeSpace{

// forward declaration	
class YGESpace;

/**
 * Entity Class
 * represents an entity. Definiton from wikipedia:
 * 'An entity is something that has a distinct, separate existence,
 *  though it need not be a material existence. ... An entity could
 *  be viewed as a set containing subsets. In philosophy, such sets
 *  are said to be abstract objects'.
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
	 * physical assets of this entity
	 */
	std::list<YGEPhysics::YGEPhysicsAsset*> physicsAssets;


	/**
	 * parent of this entity. every entity can have just one
	 * parent. If this is NULL, this entity is considered to be
	 * a root entity.
	 */
	YGEEntity* parent;

	YGESpace* space;

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
	std::list<YGEEntity*>* getChildren(){
		return &children;
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
	std::list<YGEEntityAsset*>* getAssets(){
		return &assets;
	}

	/**
	 * returns all assets that are graphical assets,
	 * meaning they are derived from YGEGraphicsAsset.
	 * will be called by the scene graphical renderer to
	 * just get the assests which are renderable
	 */
	std::list<YGEGraphics::YGEGraphicsAsset*>* getGraphicsAssets(){
		return &graphicAssets;
	}

	std::list<YGEPhysics::YGEPhysicsAsset*>* getPhysicsAssets(){
		return &physicsAssets;
	}

	/**
	 * @return the YGESpace the entity lies in, NULL if the entity is not
	 * associated to a YGESpace
	 */
	YGESpace* getSpace();

	void setSpace(YGESpace* s);



	/**
	 * get the position of this entity
	 * If this entity has a mass (is affected by the physical world)
	 * this position will be an absolute position in the space the
	 * entity exists in. In all other cases, the position will be
	 * relative to the parent of the entity.
	 */
	YGEMath::Vector3 getPosition(){
		return position;
	}

	/**
	 * returns the scaling factor of an entity
	 * in this version, this only applies to the visual representation
	 */
	YGEMath::Vector3 getScale(){
		return scale;
	}

	/**
	 * get the rotation of this entity
	 * @see getPosition();
	 */
	YGEMath::Quaternion getOrientation(){
		return orientation;
	}

	/**
	 * Sets the position of an object.
	 *
	 * If this entity has a mass (is affected by the physical world)
	 * this position will be an absolute position in the space the
	 * entity exists in. In all other cases, the position will be
	 * relative to the parent of the entity.
	 * @see getPosition();
	 */
	void setPosition(const YGEMath::Vector3 &pos){
		position = pos;
	}

	void setScale(const YGEMath::Vector3 &sca){
		scale = sca;
	}

	void setOrientation(const YGEMath::Quaternion &q){
		orientation = q;
	}

	virtual void render();

	void update(long delta);
	void tickChildren(long delta);

	virtual void tick(long delta) { 
	};

	void translate3d(double x, double y, double z){
		position.x += x;
		position.y += y;
		position.z += z;
	}


	void translate(const YGEMath::Vector3& v){
		position += v;
	}

	void rotateDGR(const YGEMath::Vector3 axis, double degree);

	void rotateRAD(const YGEMath::Vector3 axis, double radiant);

	virtual void processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider){};

};

}

#endif