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

		dGeomID geomId;

		dMass* mass;

		//YGEPhysicsAsset bla;

		bool hasBody;

		YGEMath::Vector3 bodySize;
		double bodyMass;

	public:

		YGEBodyAsset() : hasBody(false), bodySize(YGEMath::Vector3(1,1,1)), bodyMass(1){
			
		}

		void createBody();

		void addRelativeForce(double x, double y, double z);

		void addRelativeTorque(double x, double y, double z);

		void addAbsoluteForce(double x, double y, double z);

		void addAbsoluteTorque(double x, double y, double z);

		YGEMath::Vector3 getRelativeVelocity();

		void setLinearDamping(double d);

		void setAngularDamping(double d);

		//dBodyID getBodyId();

		virtual void setParent(YGETimeSpace::YGEEntity* entity);

		virtual void update(long delta);

				virtual void disable();
		virtual void enable();

		void setSize(const YGEMath::Vector3 &size);
		void setMass(double mass);
	};

}

#endif