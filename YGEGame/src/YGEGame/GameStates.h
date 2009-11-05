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
	YGEEntity* scene;

	GameStateX(){

		scene = new YGEEntity();
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
		scene->addChild(boxPos);

	}

	virtual YGESceneList getScenesToRender(){
		YGESceneList list;
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
	YGEEntity* scene;

	GameStateY(){

		scene = new YGEEntity();

		YGEEntity* hmapPos = new YGEEntity();

		YGEMath::Vector3 pos;
		pos.x = -20;
		pos.y = -20;
		pos.z = -140;
		hmapPos->setPosition(pos);

		YGEHeightmap* heightmap = new YGEHeightmap();
		heightmap->create("heightmaps/simple.bmp");
		scene->addChild(hmapPos);
		hmapPos->addAsset(heightmap);

	}

	virtual YGESceneList getScenesToRender(){
		YGESceneList list;
		list.push_back(scene);
		return list;
	}

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Updating Gamestate Y");


	}

	virtual void draw(YGECore::YGEEngineCore* core) {
	}

};

