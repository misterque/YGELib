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
	/**
	 * to interact with the engine every frame the user has to create
	 * a YGEGameState. 
	 * The user has to provide the engine with YGETimeSpace::YGESpace so it
	 * knows what to render and what to update.
	 */
class YGEGameState {
protected:
	/**
	 * a list of scenes to be renderd
	 */
	YGETimeSpace::YGESceneList sceneList;
	
	/** 
	 * a list of spaces to be updated
	 */
	YGETimeSpace::YGESpaceList spaceList;

public:
	/**
	 * update the gamestate. overload this method to implement
	 * game logic.
	 *
	 * @todo rename to tick(...)
	 * @param delta time since last tick in microseconds
	 */
	virtual void update(long delta) = 0;

	/**
	 * returns a list of scenes to be rendered.
	 * A scene composes of a YGESpace and a YGEObserver. The YGEObserver
	 * represents the point from where the scene is percived. It is a
	 * YGEEntity and must part of the YGESpace. This method is called
	 * by the YGEEngineCore and invokes the YGEAudioCore and the
	 * YGEGraphicsCore to render it.
	 */
	virtual YGETimeSpace::YGESceneList* getScenesToRender() {
		return &sceneList;
	};

	/**
	 * returns a list of YGETimeSpace::YGESpace to be updated.
	 * This method is called by the YGECore::YGEEngineCore and invokes
	 * the physics engine to compute a timestep for the spaces.
	 * Afterwards, the position of the YGETimeSpace::YGEEntity s in the spaces
	 * are updated and absolute poses of the YGETimeSpace::YGEEntity are calculated.
	 */
	virtual YGETimeSpace::YGESpaceList* getSpacesToUpdate() {
		return &spaceList;
	};

	/**
	 * if a command (for example typed into the console) is send to the YGECore::YGEEngineCore which is unknown to it,
	 * it will be passed to this method. YGEGameState s which want to respond
	 * to commands should overload this method.
	 */
	virtual void processCommand(const char* command) {
	};

};
}


#endif