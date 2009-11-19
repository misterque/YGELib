/** @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 */

#ifndef _YGE_SPACE_H_
#define _YGE_SPACE_H_

#include "YGEEntity.h"
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

	public:
		/**
		 * Creates a physics environment for this YGESpace.
		 * Time only affects physical assets as YGEMass.
		 * Physical assets as YGECollisionMesh, or YGECollisionBox
		 * can affect this.
		 */
		void initTime();

		/**
		 * starts the simulation of time
		 *
		 */
		void startTime();

		/**
		 * stops the simualtion of time
		 */
		void stopTime();



		/**
		 * */
		YGEEntity* getRootEntity(){
			return &rootEntity;
		}

	};

}

#endif