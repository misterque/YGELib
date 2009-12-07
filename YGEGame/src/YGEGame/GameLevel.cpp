#include "GameLevel.h"

#include <istream>
#include <sstream>

void GameLevel::parseFile(const char *filename){
		std::ifstream is;
		is.open(filename);
		if(!is.is_open()) {
			throw YGEExceptionFileNotFound(filename);
		}

		while(!is.eof()){
			std::string line, type;
			getline(is, line);
			std::istringstream istr(line);

			istr >> type;

			if(type == "sky:") {
				istr >> skymapName;
			} 
			if(type == "sunposition:") {
				istr >> sunposition.x;
				istr >> sunposition.y;
				istr >> sunposition.z;
			}
			if(type == "suncolor:") {
				istr >> suncolor.x;
				istr >> suncolor.y;
				istr >> suncolor.z;
			}
			if(type == "timeToComplete:") {
				istr >> timeToComplete;

			}
			if(type == "mapFileName:") {
				istr >> mapFileName;

			}
			if(type == "textureFileName:") {
				istr >> textureFileName;

			}
			if(type == "mapScale:") {
				istr >> mapScale.x;
				istr >> mapScale.y;	
				istr >> mapScale.z;
			}

			if(type == "startPos:") {
				istr >> startPos.x;
				istr >> startPos.y;	
				istr >> startPos.z;
			}







		}


}

void GameLevel::createFromFile(const char* filename){

	mapScale.x = 100;
	mapScale.y = 100;
	mapScale.z = 100;

	parseFile(YGECore::YGERessourceManager::getInstance()->absoluteFilename( filename ).c_str() );

	// create a space
	space = new YGETimeSpace::YGESpace();
	space->initTime();
	space->setSoundEnabled(true);

	// create the heightmap
	heightmap = new YGEGraphics::YGEHeightmap();
	heightmap->create(mapFileName.c_str(), textureFileName.c_str(), mapScale.x, mapScale.z, mapScale.y); 
	space->getRootEntity()->addAsset(heightmap);

	heightmap->makeSolid();

	//water = new YGEGraphics::YGEWater(heightmap, 10);
	//space->getRootEntity()->addAsset(water);

	skybox = new YGEGraphics::YGESkybox();
	skybox->loadTextures(skymapName.c_str());
	space->setSkybox(skybox);
	space->getSunlight()->setColor(suncolor.x, suncolor.y, suncolor.z);
	space->getSunlight()->setDirection(sunposition);
	GameBall* ball1 = new GameBall();
	space->getRootEntity()->addChild(ball1);
	ball1->setPosition(startPos);

	GameBall* ball2 = new GameBall();
	space->getRootEntity()->addChild(ball2);
	ball2->setPosition(YGEMath::Vector3(0, 90, 0));


}

YGEMath::Vector3 GameLevel::getPlayerStartPosition(){
	return startPos;
}

void GameLevel::addEntity(YGETimeSpace::YGEEntity* entity){
	space->getRootEntity()->addChild(entity);

}