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

/**
 * @brief simple mission objective
 *
 * on a collsion it is destroyed and sends a message to the core via YGECore::YGEEngineCore::processCommand()
 *
 */
class GameBall : public YGETimeSpace::YGEEntity {

	YGEGraphics::YGESimpleSphere* mesh;


	/**
	 * needed so a collision will only send a message once
	 */

	bool destroyed;
	YGEPhysics::YGESimpleHullAsset* hull;
public:
	GameBall(double radius, double r, double g, double b);
	virtual void processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider);


};

#endif