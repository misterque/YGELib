#include "YGEMassAsset.h"
#include "YGELogger.h"
#include "YGESpace.h"

namespace YGEPhysics {

	void YGEMassAsset::createBody(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();
		if(parentSpace != NULL){
			bodyId = dBodyCreate(parentSpace->getWorldId());

//			mass = new dMass;
//			dMassSetBox(mass,1,1,1,1);

//			dMassAdjust(mass,0.2f);

			//dBodySetMass(bodyId, &mass);
			//dBodyAddForce(bodyId, 0.5, 0, 0);
			hasBody = true;
		}
	}

	void YGEMassAsset::setParent(YGETimeSpace::YGEEntity* entity){
		parent = entity;
		if(hasBody){
			dBodyDestroy(bodyId);
			hasBody = false;
		}
	}

	void YGEMassAsset::update(){
		if(!hasBody){

			createBody();
		}
		const dReal* pos = dBodyGetPosition (bodyId);
		parent->setPosition(YGEMath::Vector3(pos[0], pos[1], pos[2]));
	}


}