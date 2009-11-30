/**
 * @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 */

#ifndef _GAME_STATE_SPLASHSCREEN_H_
#define _GAME_STATE_SPLASHSCREEN_H_

#include "YGEGameState.h"
#include "GameManager.h"

#include "YGETimer.h"
#include "YGELogger.h"
class GameStateSplashscreen : public YGEGame::YGEGameState {
private:
	YGECore::YGETimer timer;
	bool started;
public:
	GameStateSplashscreen();
	virtual void update(long delta){
		if (started == false) {
			started = true;
			timer.startTimer();
			debugout("show splashscreen");
		} else {

			if(timer.getTimeMilliseconds() > 1000) {

				GameManager::getInstance()->popGameState();
				debugout("hide splashscreen");
			}
		}
		
	}

};



#endif
