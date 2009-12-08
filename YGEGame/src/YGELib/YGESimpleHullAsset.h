/**
 * @file
 * @author Dirk Fortmeier
 * @date 29.11.2009
 */

#ifndef _YGE_SIMPLE_HULL_
#define _YGE_SIMPLE_HULL_

#include "YGEPrimitives.h"
#include "YGEPhysicsAsset.h"
#include "YGEVector.h"
#include "ode/ode.h"

namespace YGEPhysics {
class YGESimpleHullAsset : public YGEPhysicsAsset {
		dGeomID geomId;

		bool hasGeom;

		double radius;
	public:

		YGESimpleHullAsset() : hasGeom(false), radius(10){
			
		}


		void fromTriangleMesh(YGEGraphics::Mesh* mesh);

		void createGeom();

		void setRadius(double r);

		virtual void setParent(YGETimeSpace::YGEEntity* entity);

		virtual void update(long delta);

		virtual void disable();
		virtual void enable();

};

}

#endif