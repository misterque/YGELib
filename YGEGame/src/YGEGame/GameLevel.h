/**
 * @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 */

#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

#include "YGEVector.h"
#include "YGEHeightmap.h"
#include "YGEWater.h"
#include "YGESpace.h"

#include "GameBall.h"


class GameLevel {
private:
	YGETimeSpace::YGESpace *space;
	YGEGraphics::YGEHeightmap *heightmap;
	YGEGraphics::YGEWater *water;
	YGEGraphics::YGESkybox *skybox;
public:
	void loadFromFile(const char* filename);

	YGEMath::Vector3 getPlayerStartPosition();

	void addEntity(YGETimeSpace::YGEEntity* entity);

	YGETimeSpace::YGESpace* getSpace(){
		return space;
	}

};



#endif