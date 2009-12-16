#ifndef _GAME_GYROCOPTER_H_
#define _GAME_GYROCOPTER_H_

#include "YGEStaticMesh.h"
#include "YGEEntity.h"
#include "YGEBodyAsset.h"
#include "YGESimpleHullAsset.h"
#include "YGESoundAsset.h"
#include "YGEParticleSystem.h"

/**
 * @brief the players gyrocopter
 */
class GameGyrocopter : public YGETimeSpace::YGEEntity{
private:

	YGETimeSpace::YGEEntity posBody;

	YGEGraphics::YGEStaticMesh meshBody;
	YGEGraphics::YGEStaticMesh meshRotorTop;
	YGEGraphics::YGEStaticMesh meshRotorBack;
	YGEGraphics::YGEStaticMesh meshTailV;
	YGEGraphics::YGEStaticMesh meshTailH;

	YGEGraphics::YGEParticleSystem engineParticles;

	YGETimeSpace::YGEEntity posRotorTop;
	YGETimeSpace::YGEEntity posRotorBack;
	YGETimeSpace::YGEEntity posTailV;
	YGETimeSpace::YGEEntity posTailH;

	YGEPhysics::YGEBodyAsset mass;



	YGEAudio::YGESoundAsset idleSound;
	YGEAudio::YGESoundAsset lowSound;
	YGEAudio::YGESoundAsset midSound;
	YGEAudio::YGESoundAsset highSound;

	YGEPhysics::YGESimpleHullAsset collider;
	YGEPhysics::YGESimpleHullAsset colliderLeft;
	YGEPhysics::YGESimpleHullAsset colliderRight;

	YGETimeSpace::YGEEntity posColliderLeft;
	YGETimeSpace::YGEEntity posColliderRight;


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

	bool destroyed;



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



	/**
	 * tells the gyrocopter to fire a rocket
	 */
	void fireRocket();

	virtual void tick(long delta);

	/**
	 * on a collsion with the rotor, the game will end
	 */
	virtual void processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider);


};



#endif