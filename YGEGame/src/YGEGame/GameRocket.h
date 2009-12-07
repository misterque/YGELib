/**
 * @file
 * @author Dirk Fortmeier
 * @date 26.11.2009
 */

#ifndef _GAME_ROCKET_H_
#define _GAME_ROCKET_H_

#include "YGEStaticMesh.h"
#include "YGEEntity.h"
#include "YGEBodyAsset.h"
#include "YGEParticleSystem.h"

class GameRocket : public YGETimeSpace::YGEEntity {
private:
	YGEGraphics::YGEGraphicsAsset* meshRocket;
	YGEPhysics::YGEBodyAsset body;

	YGEGraphics::YGEParticleSystem explosion;
	YGEGraphics::YGEParticleSystem trail;
	double lifetime;

	YGEAudio::YGESoundAsset* engineSound;

public:
	GameRocket();
	virtual void tick(long delta);
	virtual void processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider);

	void explode();

};

#endif