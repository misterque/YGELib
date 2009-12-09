#include "YGEBodyAsset.h"
#include "YGELogger.h"
#include "YGESpace.h"

#include "YGEPhysics.h"

namespace YGEPhysics {


	void YGEBodyAsset::createBody(){
		YGETimeSpace::YGESpace* parentSpace = parent->getSpace();
		if(parentSpace != NULL && parent->getHasAbsPosition()){

			if(hasBody) {
				dBodyDestroy(bodyId);
				dGeomDestroy(geomId);
			}
			bodyId = dBodyCreate(parentSpace->getWorldId());


			mass = new dMass();
			dMassSetBox(mass,1,1,1,1);

			dMassAdjust(mass,bodyMass);

			dBodySetMass(bodyId, mass);

			dBodySetAutoDisableFlag(bodyId, 0);

			YGEMath::Vector3 pos = parent->getAbsPosition();
			YGEMath::Quaternion rot = parent->getAbsOrientation();

			dBodySetPosition(bodyId,pos.x,pos.y,pos.z);
			dQuaternion q;
			q[0]=rot.w;
			q[1]=rot.x;
			q[2]=rot.y;
			q[3]=rot.z;
			dBodySetQuaternion(bodyId, q);
			//dBodyAddForce(bodyId, 0.5, 0, 0);

			// a hull, remove this
			geomId = dCreateBox(parentSpace->getDSpaceId(), bodySize.x, bodySize.y, bodySize.z);
			dGeomSetData(geomId, this);
			
			dGeomSetCategoryBits(geomId, YGEPhysics::ENTITIES );
			dGeomSetCollideBits(geomId, YGEPhysics::ENTITIES | YGEPhysics::STATIC_OBJECTS );
			dGeomSetBody(geomId, bodyId);

			//			dBodySetAuto
			hasBody = true;
		}
	}

	void YGEBodyAsset::addRelativeForce(double x, double y, double z){
			YGEMath::Quaternion q = parent->getOrientation();

			YGEMath::Vector3 t(x,y,z);

			YGEMath::Vector3 d = q.rotateVector(t);
			
			forceAccum += d;

	}

	void YGEBodyAsset::addAbsoluteForce(double x, double y, double z){

			forceAccum.x += x;
			forceAccum.y += y;
			forceAccum.z += z;

	}
	void YGEBodyAsset::addRelativeTorque(double x, double y, double z){
								YGEMath::Quaternion q = parent->getOrientation();

			YGEMath::Vector3 t(x,y,z);

			YGEMath::Vector3 d = q.rotateVector(t);

			torqueAccum += d;


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

	void YGEBodyAsset::setForce(double x, double y, double z){
		forceAccum.x = x;
		forceAccum.y = y;
		forceAccum.z = z;

	}

	void YGEBodyAsset::setTorque(double x, double y, double z){
		torqueAccum.x = x;
		torqueAccum.y = y;
		torqueAccum.z = z;
	}

	void YGEBodyAsset::setAngularDamping(double d){

			angularDamping = d;

	}

	void YGEBodyAsset::setLinearDamping(double d){

			linearDamping = d;

	}



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
		} else {

		double second = delta / 1000000.0f;
		double m = 1; //second * 1000; 

		dBodySetAngularDamping(bodyId, angularDamping * second);
		dBodySetLinearDamping(bodyId, linearDamping * second);

		dBodyAddTorque(bodyId, torqueAccum.x * m, torqueAccum.y * m, torqueAccum.z * m);
		dBodyAddForce(bodyId, forceAccum.x * m, forceAccum.y * m, forceAccum.z * m);

		
		const dReal* pos = dBodyGetPosition (bodyId);
		const dReal* rot = dBodyGetQuaternion(bodyId);
		parent->setPosition(YGEMath::Vector3(pos[0], pos[1], pos[2]));
		parent->setOrientation(YGEMath::Quaternion(rot[0], rot[1], rot[2], rot[3]));
		}
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

	void YGEBodyAsset::setSize(const YGEMath::Vector3 &size){
		bodySize = size;
		if(hasBody) {
			createBody();
		}
	}
	
	void YGEBodyAsset::setMass(double mass){
		bodyMass = mass;
		if(hasBody) {
			createBody();
		}

	}
}