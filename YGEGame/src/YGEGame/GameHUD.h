/**
 * @file
 * @author Dirk Fortmeier
 * @date 26.11.2009
 */

#ifndef _GAME_HUD_H_
#define _GAME_HUD_H_

#include "YGESpace.h"
#include "YGEObserver.h"

class GameHUD {
	YGETimeSpace::YGESpace space;
	YGETimeSpace::YGEObserver observer;
public:
	GameHUD();
	YGETimeSpace::YGESpace* getSpace();

	YGETimeSpace::YGEObserver* getObserver();

};


#endif