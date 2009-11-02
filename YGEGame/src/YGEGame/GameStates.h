#include <SDL_opengl.h>

#include "YGEGameState.h"
#include "YGELogger.h"
#include "YGEScene.h"
#include "YGEEntity.h"
#include "YGEEntityAsset.h"

using namespace YGETimeSpace;

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
	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Updating Gamestate Y");
	}

	virtual void draw(YGECore::YGEEngineCore* core) {
		YGECore::YGELogger::getInstance()->log("Draw a box (Y)");


		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);


		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();       
				glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glTranslatef(0.0f,0.0f,-7.0f);						// Move Right 1.5 Units And Into The Screen 7.0
	glRotatef(core->getTimeSinceGameStarted()/100000.0f,1.0f,1.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Bottom Right Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad
										// Finished Drawing The Triangle
	}

};