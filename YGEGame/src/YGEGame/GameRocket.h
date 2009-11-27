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

class GameRocket : public YGETimeSpace::YGEEntity {
private:
	YGEGraphics::YGEStaticMesh meshRocket;
	YGEPhysics::YGEBodyAsset body;

	double lifetime;

public:
	GameRocket();
	virtual void tick(long delta);


};

#endif