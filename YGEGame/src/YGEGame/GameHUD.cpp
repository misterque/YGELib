#include "GameHUD.h"
#include "YGEText.h"

GameHUD::GameHUD(){
	space.getRootEntity()->addChild(&observer);
	observer.setCameraMode(CAMERA_ORTHOGONAL);

	YGETimeSpace::YGEEntity* text = new YGETimeSpace::YGEEntity();
	space.getRootEntity()->addChild(text);

	text->addAsset(new YGEGraphics::YGEText("blaaa"));
	text->setPosition(YGEMath::Vector3(50,50,0));
}

YGETimeSpace::YGESpace* GameHUD::getSpace(){
	return &space;

}

YGETimeSpace::YGEObserver* GameHUD::getObserver(){
	return &observer;

}