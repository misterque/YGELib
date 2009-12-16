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
#include "YGEKeyDownListener.h"

#include "Menu.h"

/**
 * user head up display
 * used for displaying information like fps and time to complete the level
 */
<<<<<<< HEAD
class GameHUD : public YGEKeyDownListener{
=======
class GameHUD : public  YGEInput::YGEKeyDownListener{
>>>>>>> 26a8
	// space where all the hud elements live in
	YGETimeSpace::YGESpace space;

	// observer to tell the engine that the space will be drawn in parallel projection
	YGETimeSpace::YGEObserver observer;

	// position of the infoText which will tell the user if he has finished the level or has crashed
	YGETimeSpace::YGEEntity* infoTextPos;

	// position of the text which will show the fps count
	YGETimeSpace::YGEEntity* fpsTextPos;

	YGEGraphics::YGEText* infoText;
	YGEGraphics::YGEText* velocityText;
	YGEGraphics::YGEText* fpsText;

	YGEGraphics::YGEText* timeText;


	Menu* quitMenu;
	YGETimeSpace::YGEEntity* quitMenuPos;


	double velocity;
	int time;

public:
	GameHUD();
	YGETimeSpace::YGESpace* getSpace();

	YGETimeSpace::YGEObserver* getObserver();

	void setTime(int seconds);
	void setVelocity(double v);

	//void setShowinfoText(bool show);
	void setInfoText(std::string text);

	void setFramesPerSecond(int frames);

	void showQuitMenu(bool show);

	virtual void keyDown(SDLKey key);
};


#endif