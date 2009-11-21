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
	class YGEMassAsset : public YGEPhysicsAsset {

	private: 
		/**
		* ODE body Id
		*/
		dBodyID bodyId;

		dMass* mass;

		//YGEPhysicsAsset bla;

		bool hasBody;


	public:

		YGEMassAsset() : hasBody(false){
			
		}

		void createBody();

		virtual void setParent(YGETimeSpace::YGEEntity* entity);

		virtual void update();

	};

}

#endif