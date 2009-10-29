#ifndef _YGE_GAME_STATE_
#define _YGE_GAME_STATE_

//#include "YGEEngineCore.h"

#include <list>
#include "YGEScene.h"

// forward declarations
namespace YGECore {
	class YGEEngineCore;
}

namespace YGEGame {
class YGEGameState {
public:
	virtual void update() = 0;
	virtual void draw(YGECore::YGEEngineCore* core) = 0;

	virtual std::list<YGEScene*> getScenesToRender() {
		std::list<YGEScene*> list;
		return list;
	};
	
};
}


#endif