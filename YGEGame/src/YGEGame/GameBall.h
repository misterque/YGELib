/**
 * @file
 * @author Dirk Fortmeier
 * @date 29.11.2009
 */

#ifndef _GAME_BALL_
#define _GAME_BALL_

#include "YGEEntity.h"
#include "YGESimpleHullAsset.h"
#include "YGESimpleSphere.h"

class GameBall : public YGETimeSpace::YGEEntity {

	YGEGraphics::YGESimpleSphere* mesh;

	bool destroyed;
	YGEPhysics::YGESimpleHullAsset* hull;
public:
	GameBall(double radius, double r, double g, double b);
	virtual void processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider);


};

#endif