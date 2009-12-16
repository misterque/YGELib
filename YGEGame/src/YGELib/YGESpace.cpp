#include "YGESpace.h"

namespace YGETimeSpace{

	/**
	 * @brief callback function called by ODE in case of a collision
	 */
	void nearCallback(void *data, dGeomID o0, dGeomID o1)
	{
		reinterpret_cast<YGESpace*>(data)->handleCollisionBetween(o0,o1);
	} 


	YGESpace::YGESpace() {

			sunlight = new YGEGraphics::YGESunlight();

			skybox = NULL;


			rootEntity.setSpace(this);

			timeIsRunning = false;

			soundEnabled = false;
		}

	
	YGESpace::~YGESpace() {
		delete sunlight;
		delete skybox;
	}

	void YGESpace::initTime(){

		worldId = dWorldCreate();
		spaceId = dHashSpaceCreate(0);
		
		// maybe using this would be more suitable (because of the heightmap)
		//spaceId = dQuadTreeSpaceCreate (NULL, bla, bla, 8);
		contactGroup = dJointGroupCreate(0); 

		// we need gravity

		dWorldSetGravity(worldId, 0, -9.81, 0);

		timeIsRunning = true;
	}

	void YGESpace::startTime(){
		timeIsRunning = true;
	}

	void YGESpace::stopTime(){
		timeIsRunning = false;
	}

	dWorldID  YGESpace::getWorldId(){
		//@todo check for if there is no world at all
		return worldId;
	}

	dSpaceID YGESpace::getDSpaceId(){
		return spaceId;
	}

	void YGESpace::timeStep(long long delta){
		// do not timestep if no time is running
		if(!timeIsRunning) return;
		
		// and do not timestep on negative times
		if(delta <= 0) return;


		double seconds = delta / 1000000.0f;

		// never do timesteps which are longer than a third of a second
		if(seconds > 0.3) {
			seconds = 0.3;
		}

		//test for collisions
		dSpaceCollide(spaceId, this, &nearCallback);

		//do a timestep
		dWorldStepFast1(worldId, seconds, 5 );

		// empty the group of collsion contacts
		dJointGroupEmpty(contactGroup);


	}

	bool  YGESpace::getTimeIsRunning(){
		return timeIsRunning;
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

			// send a collison to the colliding physicsAssets
			YGEPhysics::YGEPhysicsAsset* a0 = (YGEPhysics::YGEPhysicsAsset*)dGeomGetData(o0);
			YGEPhysics::YGEPhysicsAsset* a1 = (YGEPhysics::YGEPhysicsAsset*)dGeomGetData(o1);

			if(a0 && a1) {

				a0->getParent()->processCollision(a0, a1);
				if(a0->getCollisionListener() != NULL) {
					a0->getCollisionListener()->processCollision(a0, a1);
				}
				a1->getParent()->processCollision(a1, a0);
				if(a1->getCollisionListener() != NULL) {
					a1->getCollisionListener()->processCollision(a1, a0);
				}

			} else if( a0) {
				a0->getParent()->processCollision(a0, NULL);
				if(a0->getCollisionListener() != NULL) {
				a0->getCollisionListener()->processCollision(a0, NULL);
				}

			} else if( a1) {
				a1->getParent()->processCollision(a1, NULL);
				if(a1->getCollisionListener() != NULL) {
					a1->getCollisionListener()->processCollision(a1, a0);
				}

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

	void YGESpace::setSunLightPosition(const YGEMath::Vector3 &pos){
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
		delete skybox;
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