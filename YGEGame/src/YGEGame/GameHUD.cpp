#include "GameHUD.h"
#include "YGEText.h"

#include <sstream>

GameHUD::GameHUD(){
	// register a font
	YGEGraphics::YGEText::registerFont("VeraMono24", "../media/fonts/VeraMono.ttf", 24);

	// add the camera to the space of the hud and change the way of projection
	space.getRootEntity()->addChild(&observer);
	observer.setCameraMode(CAMERA_ORTHOGONAL);

	// add pause text and hide it
	infoTextPos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(infoTextPos);
	infoTextPos->translate(YGEMath::Vector3(100,300,0));
	infoText = new YGEGraphics::YGEText("press 'p' to continue", "VeraMono24");
	infoTextPos->addAsset(infoText);

	infoText->disable();

	fpsTextPos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(fpsTextPos);
	fpsTextPos->translate(YGEMath::Vector3(20,20,0));
	fpsText = new YGEGraphics::YGEText("FPS:", "VeraMono24");
	fpsTextPos->addAsset(fpsText);

//#ifndef _DEBUG
	//fpsText->disable();
//#endif

	// add entity and text for displaying the time
	YGETimeSpace::YGEEntity* timePos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(timePos);

	timeText = new YGEGraphics::YGEText("bla", "VeraMono24");
	timePos->addAsset(timeText);
	timePos->setPosition(YGEMath::Vector3(500,75,0));
	/*
	YGETimeSpace::YGEEntity* velocityPos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(velocityPos);

	velocityText = new YGEGraphics::YGEText("bla", "VeraMono24");
	velocityPos->addAsset(velocityText);
	velocityPos->setPosition(YGEMath::Vector3(500,100,0));
	*/


	quitMenuPos = new YGETimeSpace::YGEEntity();
	quitMenu = new Menu();

	quitMenuPos->addChild(quitMenu->pos);
	quitMenuPos->translate3d(220, 50, 0);

	quitMenu->addItem("Increase Sound Volume +", "volumeUp");
	quitMenu->addItem("Decrease Sound Volume -", "volumeDown");
	quitMenu->addItem("Exit", "stopgame");


}

YGETimeSpace::YGESpace* GameHUD::getSpace(){
	return &space;

}

YGETimeSpace::YGEObserver* GameHUD::getObserver(){
	return &observer;

}


void GameHUD::setTime(int seconds){
	time = seconds;
	std::stringstream s;
	if(seconds < 0) {
		s<<"-";
	}
	s<<seconds/60<<":"<<abs(seconds%60);
	timeText->setText(s.str());
	
	

}

void GameHUD::setVelocity(double v){

	velocity = v;
	//velocityText->
}


void GameHUD::setInfoText(std::string text){
	if(text == "") {
		infoText->disable();
	} else {
		infoText->enable();
		infoText->setText(text);
	}


}

void GameHUD::setFramesPerSecond(int frames){
	std::stringstream s;
	s<<"FPS: "<<frames;
	fpsText->setText(s.str());
}


void GameHUD::keyDown(SDLKey key){

	switch(key){
			case SDLK_DOWN:
				quitMenu->down();
				break;
			case SDLK_UP:
				quitMenu->up();
				break;
			case SDLK_LEFT:
				quitMenu->left();
				break;
			case SDLK_RIGHT:
				quitMenu->right();
				break;

			case SDLK_SPACE:
			case SDLK_RETURN:
				quitMenu->select();
				break;
	}
}

void GameHUD::showQuitMenu(bool show){
	if(show) {
		space.getRootEntity()->addChild(quitMenuPos);
	} else {
		space.getRootEntity()->removeChild(quitMenuPos);
	}

}