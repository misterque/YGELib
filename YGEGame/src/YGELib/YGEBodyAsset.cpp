#include "YGEBodyAsset.h"
#include "YGELogger.h"
#include "YGESpace.h"

#include "YGEPhysics.h"

namespace YGEPhysics {


	void YGEBodyAsset::createBody(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();
		if(parentSpace != NULL){
			bodyId = dBodyCreate(parentSpace->getWorldId());


			mass = new dMass();
			dMassSetBox(mass,1,1,1,1);

			dMassAdjust(mass,1.0f);

			dBodySetMass(bodyId, mass);

			dBodySetAutoDisableFlag(bodyId, 0);

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
			geomId = dCreateBox(parentSpace->getDSpaceId(), 1, 1, 1);
			dGeomSetData(geomId, this);
			
			dGeomSetCategoryBits(geomId, YGEPhysics::ENTITIES );
			dGeomSetCollideBits(geomId, YGEPhysics::ENTITIES | YGEPhysics::STATIC_OBJECTS );
			dGeomSetBody(geomId, bodyId);

			//			dBodySetAuto
			hasBody = true;
		}
	}

	void YGEBodyAsset::addRelativeForce(double x, double y, double z){
		if(hasBody){
			YGEMath::Quaternion q = parent->getOrientation();

			YGEMath::Vector3 z(x,y,z);

			YGEMath::Vector3 d = q.rotateVector(z);
			
			dBodyAddForce(bodyId, d.x, d.y, d.z);
		}

	}

	void YGEBodyAsset::addAbsoluteForce(double x, double y, double z){
		if(hasBody){

			dBodyAddForce(bodyId, x, y, z);
		}

	}
	void YGEBodyAsset::addRelativeTorque(double x, double y, double z){
		if(hasBody){
						YGEMath::Quaternion q = parent->getOrientation();

			YGEMath::Vector3 z(x,y,z);

			YGEMath::Vector3 d = q.rotateVector(z);
			dBodyAddTorque(bodyId, d.x, d.y, d.z);
		}

	}

	YGEMath::Vector3 YGEBodyAsset::getRelativeVelocity(){
if(hasBody) {
			YGEMath::Quaternion q = parent->getOrientation();

			const double* v = dBodyGetLinearVel(bodyId);

			YGEMath::Vector3 z(v[0],v[1],v[2]);

			return q.getConjugate().rotateVector(z);
} else {
	return YGEMath::Vector3();
}

	}

	void YGEBodyAsset::setAngularDamping(double d){
		if(hasBody) {
			dBodySetAngularDamping(bodyId, d);
		}
	}

	void YGEBodyAsset::setLinearDamping(double d){
		if(hasBody) {
			dBodySetLinearDamping(bodyId, d);
		}
	}


/*
	dBodyID YGEBodyAsset::getBodyId(){
		if(hasBody) {
			return bodyId;
		} else {
			// @todo add exception or similar
			return 0;
		}
	}
	*/

	void YGEBodyAsset::setParent(YGETimeSpace::YGEEntity* entity){
		parent = entity;
		if(hasBody){
			dBodyDestroy(bodyId);
			hasBody = false;
		}
	}

	void YGEBodyAsset::update(long delta){
		if(!hasBody){

			createBody();
		}

		
		const dReal* pos = dBodyGetPosition (bodyId);
		const dReal* rot = dBodyGetQuaternion(bodyId);
		parent->setPosition(YGEMath::Vector3(pos[0], pos[1], pos[2]));
		parent->setOrientation(YGEMath::Quaternion(rot[0], rot[1], rot[2], rot[3]));
	}


	void YGEBodyAsset::disable(){
		if(hasBody) {
			dGeomDisable(geomId);
			dBodyDisable(bodyId);
		}

	}
	void YGEBodyAsset::enable(){
		if(hasBody) {
			dGeomEnable(geomId);
			dBodyDisable(bodyId);
		}

	}

}