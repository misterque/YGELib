#ifndef _GAME_GYROCOPTER_H_
#define _GAME_GYROCOPTER_H_

#include "YGEStaticMesh.h"
#include "YGEEntity.h"
#include "YGEBodyAsset.h"

class GameGyrocopter : public YGETimeSpace::YGEEntity{
private:

	YGEGraphics::YGEStaticMesh meshBody;
	YGEGraphics::YGEStaticMesh meshRotorTop;
	YGEGraphics::YGEStaticMesh meshRotorBack;
	YGEGraphics::YGEStaticMesh meshTailV;
	YGEGraphics::YGEStaticMesh meshTailH;

	YGETimeSpace::YGEEntity posRotorTop;
	YGETimeSpace::YGEEntity posRotorBack;
	YGETimeSpace::YGEEntity posTailV;
	YGETimeSpace::YGEEntity posTailH;

	YGEPhysics::YGEBodyAsset mass;


	float fuel;

	double throttle;
	double tailH;
	double tailV;

	double up;

public:
	GameGyrocopter();

	/**
	 * sets the throttle in percent
	 */
	void setThrottle(double t){
		throttle = t;
}

	void setTailV( double v ){
		tailV = v;
	}

	void setTailH( double h ){
		tailH = h;
	}

	virtual void tick(long delta);



};



#endif