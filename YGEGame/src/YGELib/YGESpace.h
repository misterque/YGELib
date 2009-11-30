/** @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 */

#ifndef _YGE_SPACE_H_
#define _YGE_SPACE_H_

#include "YGEEntity.h"
#include "YGESkybox.h"
#include "YGESunlight.h"
#include <ode/ode.h>

namespace YGETimeSpace {

	/** 
	 * represents a space in which entities can exist
	 * in space(via position and rotation),
	 * in time (via interpolation between postions and rotations,
	 *    managed by a physics engine)
	 * and can be percepted.
	 * To be perceptable, the space must contain YGEObervers, and this
	 * together with YGESpace must be send to the renderer as a YGEScene
	 */
	class YGESpace {
	private:
		YGEEntity rootEntity;

		dWorldID worldId;

		dSpaceID spaceId;

		dJointGroupID contactGroup;

		YGEGraphics::YGESkybox* skybox;

		YGEGraphics::YGESunlight* sunlight;

		YGEMath::Vector3 sunlightPosition;

		bool timeIsRunning;

	public:

		YGESpace() {

			sunlight = new YGEGraphics::YGESunlight();

			skybox = NULL;


			rootEntity.setSpace(this);

			timeIsRunning = false;
		}
		/**
		 * Creates a physics environment for this YGESpace.
		 * Time only affects physical assets as YGEMass.
		 * Physical assets as YGECollisionMesh, or YGECollisionBox
		 * can affect this.
		 */
		void initTime();

		/**
		 * starts the simulation of time
		 * @todo implement this
		 *
		 */
		void startTime();

		/**
		 * stops the simualtion of time
		 * @todo implement this
		 */
		void stopTime();

		void timeStep(long long delta);

		/**
		 * */
		YGEEntity* getRootEntity(){
			return &rootEntity;
		}

		/**
		 * @return the ODE dWorldID of the world
		 * associated to this space
		 */
		dWorldID getWorldId();

		dSpaceID getDSpaceId();

		void handleCollisionBetween(dGeomID o0, dGeomID o1);

		bool hasSkybox();

		YGEGraphics::YGESkybox* getSkybox();

		void setSkybox(YGEGraphics::YGESkybox* sky);

		YGEGraphics::YGESunlight* getSunlight();

		void setSunLightPosition(YGEMath::Vector3 pos);

	};

	typedef std::list<YGESpace*> YGESpaceList;
}

#endif