/**
 * @file
 * @author Dirk Fortmeier
 * @date 29.11.2009
 */

#ifndef _YGE_SIMPLE_HULL_
#define _YGE_SIMPLE_HULL_

#include "YGEPhysicsAsset.h"
#include "YGEVector.h"
#include "ode/ode.h"

namespace YGEPhysics {
class YGESimpleHullAsset : public YGEPhysicsAsset {
		dGeomID geomId;

		bool hasGeom;


	public:

		YGESimpleHullAsset() : hasGeom(false){
			
		}

		void createGeom();

		virtual void setParent(YGETimeSpace::YGEEntity* entity);

		virtual void update(long delta);

		virtual void disable();
		virtual void enable();

};

}

#endif