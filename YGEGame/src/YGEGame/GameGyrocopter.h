#ifndef _GAME_GYROCOPTER_H_
#define _GAME_GYROCOPTER_H_

#include "YGEStaticMesh.h"
#include "YGEEntity.h"
#include "YGEBodyAsset.h"
#include "YGESoundAsset.h"

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

	YGEAudio::YGESoundAsset idleSound;
	YGEAudio::YGESoundAsset lowSound;
	YGEAudio::YGESoundAsset midSound;
	YGEAudio::YGESoundAsset highSound;

	int soundstate;
	float fuel;

	double throttle;
	double tailH;
	double tailV;
	double tailX;

	double up;

	double backRotorAngularVelocity;

	double tailHRot;
	double tailVRot;

	long long reload;
	int fireFromRight;



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
	
	void setTailX( double x){
		tailX = x;
	}



	void fireRocket();

	virtual void tick(long delta);



};



#endif