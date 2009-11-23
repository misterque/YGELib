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
protected:
	YGETimeSpace::YGESceneList sceneList;
	YGETimeSpace::YGESpaceList spaceList;

public:
	virtual void update() = 0;
	//virtual void draw(YGECore::YGEEngineCore* core) = 0;

	virtual YGETimeSpace::YGESceneList* getScenesToRender() {
		return &sceneList;
	};

	virtual YGETimeSpace::YGESpaceList* getSpacesToUpdate() {
		return &spaceList;
	};


};
}


#endif