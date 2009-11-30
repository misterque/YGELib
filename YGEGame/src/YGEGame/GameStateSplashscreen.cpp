#include "GameStateSplashscreen.h"
#include "YGEEntity.h"
#include "YGESpace.h"
#include "YGEObserver.h"
#include "YGEText.h"

GameStateSplashscreen::GameStateSplashscreen(){
	started = false;

	YGETimeSpace::YGESpace* space = new YGETimeSpace::YGESpace();
	YGETimeSpace::YGEObserver* observer = new YGETimeSpace::YGEObserver();
	observer->setCameraMode(CAMERA_ORTHOGONAL);

	space->getRootEntity()->addChild(observer);

	YGETimeSpace::YGEScene s;
	s.first = space;
	s.second = observer;

	sceneList.push_back(s);

	YGETimeSpace::YGEEntity* textPos = new YGETimeSpace::YGEEntity();
	space->getRootEntity()->addChild(textPos);

	YGEGraphics::YGEText::registerFont("VeraMono24", "../media/fonts/VeraMono.ttf", 24);
	YGEGraphics::YGEText* text = new YGEGraphics::YGEText("YGE 2009", "VeraMono24");
	textPos->addAsset(text);
	textPos->setPosition(YGEMath::Vector3(200,75,0));

}
