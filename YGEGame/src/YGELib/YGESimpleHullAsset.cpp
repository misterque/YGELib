#include "YGESimpleHullAsset.h"
#include "YGESpace.h"
#include "YGEPhysics.h"


namespace YGEPhysics {


	void YGESimpleHullAsset::createGeom(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();

		if(parentSpace != NULL){
			geomId = dCreateSphere(parentSpace->getDSpaceId(), radius);
			dGeomSetData(geomId, this);

			dGeomSetCategoryBits(geomId, YGEPhysics::ENTITIES );
			dGeomSetCollideBits(geomId, YGEPhysics::ENTITIES | YGEPhysics::STATIC_OBJECTS );

			hasGeom = true;
		}
	}

	void YGESimpleHullAsset::setRadius(double r){
		if(hasGeom) {
			dGeomDestroy(geomId);
			hasGeom = false;

		}
		radius = r;

	}



	void YGESimpleHullAsset::setParent(YGETimeSpace::YGEEntity* entity){
		parent = entity;
		if(hasGeom){
			dGeomDestroy(geomId);
			hasGeom = false;
		}
	}

	void YGESimpleHullAsset::update(long delta){
		if(parent->getHasAbsPosition()) {
			if(!hasGeom ){

				createGeom();

			} 

			YGEMath::Vector3 pos = parent->getAbsPosition();
			dGeomSetPosition(geomId, pos.x, pos.y, pos.z);
		}
	}
	void YGESimpleHullAsset::disable(){
		if(hasGeom) {
			dGeomDisable(geomId);
		}

	}
	void YGESimpleHullAsset::enable(){
		if(hasGeom) {
			dGeomEnable(geomId);
		}

	}

}