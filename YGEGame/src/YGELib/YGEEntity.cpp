#include <SDL_opengl.h>

#include "YGESpace.h"
#include "YGEEntity.h"
#include <cmath>

#define PI 3.1415926

namespace YGETimeSpace{
	
	void YGEEntity::update(long delta){

		protectChildren = true;

		// get every physical asset and ...
		std::list<YGEPhysics::YGEPhysicsAsset*>* assets = this->getPhysicsAssets();
		for(std::list<YGEPhysics::YGEPhysicsAsset*>::iterator iter = assets->begin();
			iter != assets->end();
			iter++){

				(*iter)->update(delta);

		}
		// recursive call on all children
		std::list<YGEEntity*>* children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				(*iter)->update(delta);

		}

		protectChildren = false;

		// remove all children which have been proteced	
		for(std::list<YGEEntity*>::iterator iter = childrenToRemove.begin();
			iter != childrenToRemove.end();
			iter++){
				this->children.remove((*iter));

		}


	};

	void YGEEntity::updateAbsolutePosition(YGEMath::Vector3 posStack, YGEMath::Quaternion rotStack){
		
		oldPosition = newPosition;
		oldOrientation = newOrientation;

		newPosition = rotStack.rotateVector(position) + posStack;
		newOrientation = rotStack * orientation;

		std::list<YGEEntity*>* children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				(*iter)->updateAbsolutePosition(newPosition, newOrientation);

		}

	}

	void YGEEntity::interpolate(long long timeX){
		
		double delta = 0.0001;
		
		if(timeOfNewPosition - timeOfOldPosition > 0)  {
			delta = ((timeX - timeOfOldPosition) / (timeOfNewPosition - timeOfOldPosition));
		}

		absPosition = oldPosition + (newPosition - oldPosition) * delta;
		absOrientation = oldOrientation + (newOrientation - oldOrientation) * delta;

		interpolatedPosition = absPosition;
		interpolatedOrientation = absOrientation;

		std::list<YGEEntity*>* children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				(*iter)->interpolate(timeX);

		}
	}

	void YGEEntity::setTimeOfNewPosition(long long time) {
		timeOfOldPosition = timeOfNewPosition;
		timeOfNewPosition = time;

		std::list<YGEEntity*>* children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				(*iter)->setTimeOfNewPosition(time);

		}
	}

	void YGEEntity::tickChildren(long delta){

		protectChildren = true;

		// recursive call on all children
		std::list<YGEEntity*>* children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				(*iter)->tickChildren(delta);
				(*iter)->tick(delta);

		}

		// recursive call on all assets
		std::list<YGETimeSpace::YGEEntityAsset*>* assets = this->getAssets();
		for(std::list<YGETimeSpace::YGEEntityAsset*>::iterator iter = assets->begin();
			iter != assets->end();
			iter++){

			(*iter)->tick(delta);

		}

		protectChildren = false;

				// remove all children which have been proteced	
		for(std::list<YGEEntity*>::iterator iter = childrenToRemove.begin();
			iter != childrenToRemove.end();
			iter++){
				this->children.remove((*iter));

		}

	};

	void YGEEntity::addChild( YGEEntity* entity ){

		//@todo check for double insertion

		entity->parent = this;
		children.push_back(entity);

	}

	void YGEEntity::removeChild(YGETimeSpace::YGEEntity *entity){
		if(protectChildren) {
			childrenToRemove.push_back(entity);
		} else {
			children.remove(entity);
		}


		//@todo check if children was removed so it really was a child...
		for(std::list<YGEEntityAsset*>::iterator iter = entity->getAssets()->begin();
			iter != entity->getAssets()->end();
			iter++){

				(*iter)->disable();
		

		}

	}

	void YGEEntity::addAsset( YGEEntityAsset* asset ){

		//@todo check for double insertion

		asset->setParent(this);

		assets.push_back(asset);

		// if it is a graphical asset put it in the list of graphicals
		if(asset->getAssetType() == Graphical) {
			graphicAssets.push_back((YGEGraphics::YGEGraphicsAsset*)asset);
		}
		if(asset->getAssetType() == Physics) {
			physicsAssets.push_back((YGEPhysics::YGEPhysicsAsset*)asset);
		}
		if(asset->getAssetType() == Sound) {
			soundAssets.push_back((YGEAudio::YGESoundAsset*)asset);
		}
		

	}


	YGEEntity::YGEEntity(){
		scale.x = 1 ;
		scale.y = 1;
		scale.z = 1;

		assets.clear();
		children.clear();
		parent = NULL;

		space = NULL;

		protectChildren = false;
	}

	YGEEntity::~YGEEntity(){

		for(std::list<YGEEntityAsset*>::iterator iter = getAssets()->begin();
			iter != getAssets()->end();
			iter++){

				delete (*iter);
		

		}

		std::list<YGEEntity*>* children = this->getChildren();
		for(std::list<YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				delete (*iter);

		}

	}

	void YGEEntity::rotateDGR(const YGEMath::Vector3 axis, double degree){

		rotateRAD(axis, degree * PI / 180.0f);
	}

	void YGEEntity::rotateRAD(const YGEMath::Vector3 axis, double radiant){

		YGEMath::Quaternion q;
		q.w = cos(radiant);
		q.x = axis.x * sin(radiant);
		q.y = axis.y * sin(radiant);
		q.z = axis.z * sin(radiant);

		setOrientation(q * getOrientation());


	}

	YGESpace* YGEEntity::getSpace(){
		if(space == NULL) {
			return parent->getSpace();
		}
		return space;

	}

	void YGEEntity::setSpace(YGESpace* s){
		space = s;
	}


}