#include "YGEMassAsset.h"
#include "YGELogger.h"
#include "YGESpace.h"

namespace YGEPhysics {

	void YGEMassAsset::createBody(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();
		if(parentSpace != NULL){
			bodyId = dBodyCreate(parentSpace->getWorldId());

			mass = new dMass();
			dMassSetBox(mass,1,1,1,1);

			dMassAdjust(mass,0.2f);

			dBodySetMass(bodyId, mass);

			YGEMath::Vector3 pos = parent->getPosition();
			YGEMath::Quaternion rot = parent->getOrientation();

			dBodySetPosition(bodyId,pos.x,pos.y,pos.z);
			dQuaternion q;
			q[0]=rot.w;
			q[1]=rot.x;
			q[2]=rot.y;
			q[3]=rot.z;
			dBodySetQuaternion(bodyId, q);
			//dBodyAddForce(bodyId, 0.5, 0, 0);

			// a hull, remove this
			dGeomID geom = dCreateBox(parentSpace->getDSpaceId(), 1, 1, 1);
			dGeomSetBody(geom, bodyId);
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
		const dReal* rot = dBodyGetQuaternion(bodyId);
		parent->setPosition(YGEMath::Vector3(pos[0], pos[1], pos[2]));
		parent->setOrientation(YGEMath::Quaternion(rot[0], rot[1], rot[2], rot[3]));
	}


}