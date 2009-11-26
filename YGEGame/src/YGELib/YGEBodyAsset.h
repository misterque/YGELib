/**
* @file
* @author Dirk Fortmeier
* @date 19.11.2009
*/

#ifndef _YGE_MASS_ASSET_H_
#define _YGE_MASS_ASSET_H_

#include "YGEPhysicsAsset.h"
#include "YGEVector.h"
#include "ode/ode.h"

namespace YGEPhysics {
	class YGEBodyAsset : public YGEPhysicsAsset {

	private: 
		/**
		* ODE body Id
		*/
		dBodyID bodyId;

		dMass* mass;

		//YGEPhysicsAsset bla;

		bool hasBody;


	public:

		YGEBodyAsset() : hasBody(false){
			
		}

		void createBody();

		void addRelativeForce(double x, double y, double z);

		void addRelativeTorque(double x, double y, double z);

		void addAbsoluteForce(double x, double y, double z);

		void addAbsoluteTorque(double x, double y, double z);

		dBodyID getBodyId();

		virtual void setParent(YGETimeSpace::YGEEntity* entity);

		virtual void update(long delta);

	};

}

#endif