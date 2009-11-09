#include <SDL_opengl.h>

#include "YGEGameState.h"
#include "YGELogger.h"
#include "YGEScene.h"
#include "YGEEntity.h"
#include "YGEEntityAsset.h"
#include "YGEHeightmap.h"
#include "YGEGraphicsAsset.h"
#include "YGEParticleSystem.h"

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
		YGEScene s;
		s.first = scene;
		s.second = NULL;
		YGESceneList list;
		list.push_back(s);
		return list;
	}

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Updating Gamestate X");


	}

	virtual void draw(YGECore::YGEEngineCore* core) {

										// Finished Drawing The Triangle
	}

};


class GameStateY : public YGEGame::YGEGameState, public YGEKeyDownListener {
public:
	YGEEntity* scene;
	YGEObserver* camera;

	GameStateY(){

		scene = new YGEEntity();

		YGEMath::Vector3 pos;
		pos.x = 20;
		pos.y = 20;
		pos.z = 140;

		camera = new YGEObserver();

		camera->setPosition(pos);

		YGEHeightmap* heightmap = new YGEHeightmap();
		heightmap->create("heightmaps/simple.bmp");

		scene->addAsset(heightmap);

		scene->addChild(camera);

	}

	virtual YGESceneList getScenesToRender(){
		YGEScene s;
		s.first = scene;
		s.second = camera;
		YGESceneList list;
		list.push_back(s);
		return list;
	}

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Updating Gamestate Y");


	}

	virtual void draw(YGECore::YGEEngineCore* core) {
	}

	virtual void keyDown(SDLKey key){
		switch(key){
			case SDLK_UP:
				YGEMath::Vector3 pos = camera->getPosition();
				pos.z+=1;
				camera->setPosition(pos);
				break;
		}
		
	}

};


class GameStateZ : public YGEGame::YGEGameState, public YGEKeyDownListener {
public:
	YGEEntity* scene;
	YGEObserver* camera;
	YGEParticleSystem* ps;

	GameStateZ(){

		scene = new YGEEntity();

		YGEMath::Vector3 pos;
		pos.x = 0;
		pos.y = 0;
		pos.z = 10;

		camera = new YGEObserver();

		camera->setPosition(pos);

		ps = new YGEParticleSystem();
		scene->addAsset(ps);

		scene->addChild(camera);

	}

	virtual YGESceneList getScenesToRender(){
		YGEScene s;
		s.first = scene;
		s.second = camera;
		YGESceneList list;
		list.push_back(s);
		return list;
	}

	virtual void update() {
		ps->update();
		YGECore::YGELogger::getInstance()->log("Updating Gamestate Z");


	}

	virtual void draw(YGECore::YGEEngineCore* core) {
	}

	virtual void keyDown(SDLKey key){
		switch(key){
			case SDLK_UP:
				YGEMath::Vector3 pos = camera->getPosition();
				pos.z+=1;
				camera->setPosition(pos);
				break;
		}
		
	}

};

