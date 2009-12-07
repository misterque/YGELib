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


	std::string skymapName;
	YGEMath::Vector3 sunposition;
	YGEMath::Vector3 suncolor;
	int timeToComplete;

	std::string mapFileName;
	std::string textureFileName;

	YGEMath::Vector3 mapScale;
	YGEMath::Vector3 startPos;
	void parseFile(const char* filename);
public:
	void createFromFile(const char* filename);

	void createRandom();

	void createSample();

	YGEMath::Vector3 getPlayerStartPosition();

	void addEntity(YGETimeSpace::YGEEntity* entity);

	YGETimeSpace::YGESpace* getSpace(){
		return space;
	}

};



#endif