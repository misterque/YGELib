#include "YGESpace.h"

namespace YGETimeSpace{


	void nearCallback(void *data, dGeomID o0, dGeomID o1)
	{
		reinterpret_cast<YGESpace*>(data)->handleCollisionBetween(o0,o1);
	} 

	void YGESpace::initTime(){

		worldId = dWorldCreate();
		spaceId = dHashSpaceCreate(0);
		//spaceId = dQuadTreeSpaceCreate (NULL, bla, bla, 8);

		contactGroup = dJointGroupCreate(0); 

		dWorldSetGravity(worldId, 0, -9.81, 0);

		//dGeomID groundPlane = dCreatePlane(spaceId, 0, 1, 0, 0);
		//dGeom

		timeIsRunning = true;
	}

	dWorldID  YGESpace::getWorldId(){
		//@todo check for if there is no world at all
		return worldId;
	}

	dSpaceID YGESpace::getDSpaceId(){
		return spaceId;
	}

	void YGESpace::timeStep(long long delta){
		if(!timeIsRunning) return;
		if(delta <= 0) return;

		double seconds = delta / 1000000.0f;
		if(seconds > 0.3) {
			seconds = 0.3;
		}

		dSpaceCollide(spaceId, this, &nearCallback);
		dWorldStep(worldId, seconds );
		dJointGroupEmpty(contactGroup);

	}

	/** stolen from xavier decoret who stole it as well **/
	void YGESpace::handleCollisionBetween(dGeomID o0, dGeomID o1)
	{


		// Create an array of dContact objects to hold the contact joints
		static const int MAX_CONTACTS = 10;
		dContact contact[MAX_CONTACTS];

		for (int i = 0; i < MAX_CONTACTS; i++)
		{
			contact[i].surface.mode = dContactBounce | dContactSoftCFM;
			contact[i].surface.mu = 0.5;
			//contact[i].surface.mu2 = 0;
			contact[i].surface.bounce = 0.3;
			contact[i].surface.bounce_vel = 0.1;
			contact[i].surface.soft_cfm = 0.01;
		}
		if (int numc = dCollide(o0, o1, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
		{

			YGEPhysics::YGEPhysicsAsset* a0 = (YGEPhysics::YGEPhysicsAsset*)dGeomGetData(o0);
			YGEPhysics::YGEPhysicsAsset* a1 = (YGEPhysics::YGEPhysicsAsset*)dGeomGetData(o1);

			if(a0 && a1) {
				a0->getParent()->processCollision(a0, a1);
				a1->getParent()->processCollision(a1, a0);
			} else if( a0) {
				a0->getParent()->processCollision(a0, NULL);
			} else if( a1) {
				a1->getParent()->processCollision(a1, NULL);
			}
			// Get the dynamics body for each geom
			dBodyID b1 = dGeomGetBody(o0);
			dBodyID b2 = dGeomGetBody(o1);
			// To add each contact point found to our joint group we call dJointCreateContact which is just one of the many
			// different joint types available.  
			for (int i = 0; i < numc; i++)
			{
				// dJointCreateContact needs to know which world and joint group to work with as well as the dContact
				// object itself. It returns a new dJointID which we then use with dJointAttach to finally create the
				// temporary contact joint between the two geom bodies.
				dJointID c = dJointCreateContact(worldId, contactGroup, contact + i);
				dJointAttach(c, b1, b2);
			}
		}	
	}

	void YGESpace::setSunLightPosition(YGEMath::Vector3 pos){
		sunlightPosition = pos;
	}

	bool  YGESpace::hasSkybox(){
		if(skybox == NULL) {
			return false;
		} else {
			return true;
		}
	}
	YGEGraphics::YGESkybox* YGESpace::getSkybox(){
		return skybox;
	}

	void YGESpace::setSkybox(YGEGraphics::YGESkybox* sky){
		skybox = sky;
	}

	YGEGraphics::YGESunlight* YGESpace::getSunlight(){
		return sunlight;
	}


	bool YGESpace::getSoundEnabled() {
		return soundEnabled;
	}
	
	void YGESpace::setSoundEnabled(bool enable){
		soundEnabled = enable;
	}

}