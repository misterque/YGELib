#include <SDL_opengl.h>

#include "YGEGameState.h"
#include "YGELogger.h"
#include "YGEScene.h"
#include "YGEEntity.h"
#include "YGEEntityAsset.h"
#include "YGEHeightmap.h"
#include "YGEGraphicsAsset.h"

using namespace YGETimeSpace;
using namespace YGEGraphics;

class GameStateX : public YGEGame::YGEGameState {
public:
	YGEScene* scene;

	GameStateX(){

		scene = new YGEScene();
		YGEEntity* boxPos = new YGEEntity();
		YGESimpleBox* box = new YGESimpleBox();

		YGEEntity* smallBoxPos = new YGEEntity();
		YGESimpleBox* smallBox = new YGESimpleBox();

		YGEMath::Vector3 pos;
		pos.x = 0;
		pos.y = 0;
		pos.z = -10;
		boxPos->setPosition(pos);

		YGEMath::Vector3 pos2;
		pos2.x = 4;
		pos2.y = 0;
		pos2.z = 0;

		YGEMath::Vector3 scale;
		scale.x = 0.5;
		scale.y = 0.5;
		scale.z = 0.5;

		smallBoxPos->setPosition(pos2);
		smallBoxPos->setScale(scale);

		smallBoxPos->addAsset(smallBox);
		boxPos->addChild(smallBoxPos);

		boxPos->addAsset(box);
		scene->getRootNode()->addChild(boxPos);

	}

	virtual std::list<YGEScene*> getScenesToRender(){
		std::list<YGEScene*> list;
		list.push_back(scene);
		return list;
	}

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Updating Gamestate X");


	}

	virtual void draw(YGECore::YGEEngineCore* core) {

										// Finished Drawing The Triangle
	}

};


class GameStateY : public YGEGame::YGEGameState {
public:
	YGEScene* scene;

	GameStateY(){

		scene = new YGEScene();

		YGEHeightmap* heightmap = new YGEHeightmap();
		heightmap->create("heightmaps/simple.bmp");
		scene->getRootNode()->addAsset(heightmap);

	}

	virtual std::list<YGEScene*> getScenesToRender(){
		std::list<YGEScene*> list;
		list.push_back(scene);
		return list;
	}

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Updating Gamestate Y");


	}

	virtual void draw(YGECore::YGEEngineCore* core) {
	}

};

