#include "GameHUD.h"
#include "YGEText.h"

#include <sstream>

GameHUD::GameHUD(){

	YGEGraphics::YGEText::registerFont("VeraMono24", "../media/fonts/VeraMono.ttf", 24);

	space.getRootEntity()->addChild(&observer);
	observer.setCameraMode(CAMERA_ORTHOGONAL);

	YGETimeSpace::YGEEntity* text = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(text);

	text->addAsset(new YGEGraphics::YGEText("blaaa"));
	text->setPosition(YGEMath::Vector3(50,50,0));

	pauseTextPos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(pauseTextPos);
	pauseTextPos->translate(YGEMath::Vector3(200,300,0));
	pauseText = new YGEGraphics::YGEText("press 'p' to continue", "VeraMono24");
	pauseTextPos->addAsset(pauseText);

	YGETimeSpace::YGEEntity* timePos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(timePos);

	timeText = new YGEGraphics::YGEText("bla", "VeraMono24");
	timePos->addAsset(timeText);
	timePos->setPosition(YGEMath::Vector3(500,75,0));

	YGETimeSpace::YGEEntity* velocityPos = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(velocityPos);

	velocityText = new YGEGraphics::YGEText("bla", "VeraMono24");
	velocityPos->addAsset(velocityText);
	velocityPos->setPosition(YGEMath::Vector3(500,100,0));


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
	s<<seconds/60<<":"<<seconds%60;
	timeText->setText(s.str());
	

}

void GameHUD::setVelocity(double v){

	velocity = v;
	//velocityText->
}

void GameHUD::setShowPauseText(bool show){
	showPauseText = show;
	if(show) {
		pauseText->enable();
	} else {
		pauseText->disable();
	}
}