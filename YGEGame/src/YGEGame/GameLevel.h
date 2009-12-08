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
	/**
	 * all entities which are used in the ingame mode
	 * belong in this space
	 */
	YGETimeSpace::YGESpace *space;
	
	/**
	 * a heightmap
	 */
	YGEGraphics::YGEHeightmap *heightmap;
	
	/**
	 * some water, not used in every level
	 */
	YGEGraphics::YGEWater *water;
	
	
	/**
	 * the skybox
	 */
	YGEGraphics::YGESkybox *skybox;


	/**
	 * the first part of the filenames of the skyboxtextures to be loaded
	 */
	std::string skymapName;

	/**
	 * position of the sun
	 */
	YGEMath::Vector3 sunposition;
	
	/**
	 * color of the sunlight
	 */
	YGEMath::Vector3 suncolor;

	/**
     * time that has to be beaten to reach the next level
	 */
	int timeToComplete;

	/**
	 * filename of the heightmap
	 	 * @param filename relative to media directory
	 */
	std::string mapFileName;
	
	/**
	 * filename of the texture of the heightmap
	 * @param filename relative to media directory
	 */
	std::string textureFileName;

	/**
	 * scale of the heightmap
	 */
	YGEMath::Vector3 mapScale;
	
	/**
	 * player starting position
	 */
	YGEMath::Vector3 startPos;
	
	
	/**
	 * parse a level file
	 * @param filename relative to media directory
     */
	void parseFile(const char* filename);

	/**
	 * positions of the balls
	 */
	std::list<YGEMath::Vector3> ballPositions;
public:
	/**
	 * create his level from a file
	 * @param filename relative to mediadirectory
	 */
	void createFromFile(const char* filename);

	
	/**
	 * @return the starting position of the player
	 */
	YGEMath::Vector3 getPlayerStartPosition();


	/**
	 * add an entity to the space associated to this level
	 */
	void addEntity(YGETimeSpace::YGEEntity* entity);

	/**
	 * get a pointer to the space associated to this level
	 */
	YGETimeSpace::YGESpace* getSpace(){
		return space;
	}

};



#endif