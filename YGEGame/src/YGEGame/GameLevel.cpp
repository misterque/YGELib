#include "GameLevel.h"

#include <istream>
#include <sstream>

GameLevel::~GameLevel(){
	delete space;
	delete heightmap;
	delete water;
	delete skybox;
}
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

		if(type == "ball:") {
			YGEMath::Vector3 position;

			std::string color;
			istr >> color;

			istr >> position.x;
			istr >> position.y;	
			istr >> position.z;

			ballPositions.push_back(std::pair<YGEMath::Vector3, std::string>(position, color));
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
	space->getSunlight()->setColor((float)suncolor.x, (float)suncolor.y, (float)suncolor.z);
	space->getSunlight()->setDirection(sunposition);

	for(std::list<std::pair<YGEMath::Vector3, std::string>>::iterator iter = ballPositions.begin(); iter != ballPositions.end(); iter++){

		GameBall* ball;

		if(iter->second == "blue") {
			ball = new GameBall(7, 0, 0, 1);
		} else if(iter->second == "red") {
			ball = new GameBall(5, 1, 0, 0);
		} else if(iter->second == "pink") {
			ball = new GameBall(2, 1, 0, 1);
		} else {
			ball = new GameBall(10, 1, 1, 1);
		}


		space->getRootEntity()->addChild(ball);
		ball->setPosition(iter->first);


	}


}

YGEMath::Vector3 GameLevel::getPlayerStartPosition(){
	return startPos;
}

void GameLevel::addEntity(YGETimeSpace::YGEEntity* entity){
	space->getRootEntity()->addChild(entity);

}

int GameLevel::getNumberOfBalls(){
	return ballPositions.size();
}

int GameLevel::getTimeToComplete(){

	return timeToComplete;
}
