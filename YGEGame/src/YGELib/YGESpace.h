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
	 * To be perceptable, the space must contain YGEObservers, and this
	 * together with YGESpace must be send to the renderer as a YGEScene
	 */
	class YGESpace {
	private:
		/**
		 * @brief the spaces root entity
		 *
		 * every entity which is part of the space is either a child of the rootEntity
		 * or a child of a child of it.
		 */
		YGEEntity rootEntity;

		/**
		 * @brief the ODE world id
		 *
		 * See the ODE manual.
		 */
		dWorldID worldId;

		/**
		 * @brief the ODE space id of this space
		 *
		 * In ODE, every world contains several spaces, here
		 * we only use one.
		 * See the ODE manual.
		 */
		dSpaceID spaceId;

		/**
		 * @brief ODE joint group used for managing collisions
		 */
		dJointGroupID contactGroup;


		/**
		 * @brief a pointer to a skybox
		 *
		 * if this points not to null, a skybox will be rendered around the scene
		 */
		YGEGraphics::YGESkybox* skybox;


		/**
		 * @brief a pointer to a sunlight
		 *
		 * the sunlight is used for global illumination
		 */
		YGEGraphics::YGESunlight* sunlight;

		/**
		 * @brief Position of the sunlight.
		 */
		YGEMath::Vector3 sunlightPosition;

		/**
		 * @brief If true, physics will be calculated for this scene.
		 */
		bool timeIsRunning;

		/**
		 * @brief If true, the listener position will be set to the position of
		 * a observer associated to this space.
		 */
		bool soundEnabled;

	public:

		YGESpace();

		~YGESpace();

		/**
		 * @brief Creates a physics environment for this YGESpace.
		 *
		 * Time only affects physical assets as YGEMass.
		 * Physical assets as YGECollisionMesh, or YGECollisionBox
		 * can affect this.
		 */
		void initTime();

		/**
		 * @brief starts the simulation of time
		 * @note initTime() should be called before.
		 *
		 */
		void startTime();

		/**
		 * @brief stops the simualtion of time
		 */
		void stopTime();

		/**
		 * @brief Tell the physics engine to perform a timestep.
		 */
		void timeStep(long long delta);

		/**
		 * @brief true, if time is running
		 */
		bool getTimeIsRunning();

		/**
		 * @brief return a pointer to the root entity 
		 */
		YGEEntity* getRootEntity(){
			return &rootEntity;
		}

		/**
		 * @return the ODE dWorldID of the world
		 * associated to this space
		 */
		dWorldID getWorldId();

		/**
		 * @brief return the space id of the ode space
		 * @deprecated
		 */
		dSpaceID getDSpaceId();


		/**
		 * @brief handle collision between objects
		 * @note is called by a callback function and should in fact be private
		 */
		void handleCollisionBetween(dGeomID o0, dGeomID o1);

		/**
		 * @brief returns true if this space has a skybox that shall be rendered
		 */
		bool hasSkybox();

		/**
		 * @brief returns the skybox
		 */
		YGEGraphics::YGESkybox* getSkybox();


		/**
		 * @brief sets the skybox
		 */
		void setSkybox(YGEGraphics::YGESkybox* sky);

		/**
		 * @brief retuns a pointer to the sunlight of this space
		 */
		YGEGraphics::YGESunlight* getSunlight();

		/**
		 * @brief sets the position of the sunlight
		 */
		void setSunLightPosition(const YGEMath::Vector3 &pos);
		

		/**
		 * @brief true, if sound is enabled for this space
		 */
		bool getSoundEnabled();

		/**
		 * @brief set if sound is enabled for this space
		 */
		void setSoundEnabled(bool enable);
	};

	/**
	 * @brief a list of spaces
	 */
	typedef std::list<YGESpace*> YGESpaceList;
}

#endif