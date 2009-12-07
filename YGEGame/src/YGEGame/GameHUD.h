/**
 * @file
 * @author Dirk Fortmeier
 * @date 26.11.2009
 */

#ifndef _GAME_HUD_H_
#define _GAME_HUD_H_

#include "YGESpace.h"
#include "YGEObserver.h"
#include "YGEText.h"

class GameHUD {
	YGETimeSpace::YGESpace space;
	YGETimeSpace::YGEObserver observer;

	YGETimeSpace::YGEEntity* pauseTextPos;

	YGEGraphics::YGEText* pauseText;
	YGEGraphics::YGEText* velocityText;
	YGEGraphics::YGEText* timeText;
	double velocity;
	int time;

	bool showPauseText;

public:
	GameHUD();
	YGETimeSpace::YGESpace* getSpace();

	YGETimeSpace::YGEObserver* getObserver();

	void setTime(int seconds);
	void setVelocity(double v);

	void setShowPauseText(bool show);
};


#endif