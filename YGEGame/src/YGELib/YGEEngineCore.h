/**
* @file
* @author Dirk Fortmeier
* @date ?
*/


/**
* @mainpage Documentation for the YGE2009 Game Engine by Dirk Fortmeier
*
* \section Introduction
* This documentation generated with doxygen contains information about
* the different parts of my game-engine constructed during the YGE module
* at Teeside University in the year 2009.
* 
* How the engine can be used for creation of a game is shown in the next
* section.
*
*
* \section Usage
*
* The next part of code shows a sample main.cpp program which creates a core and
* passes a game-state to it.
*
* \code

#include <YGEEngineCoreSingleThreaded.h>
#include "MyGameState.h"

void main(){
// for multithreading use YGEEngineCoreMultithreaded, remember to include header file
YGECore::YGEEngineCoreSingleThreaded core;

MyGameState gamestate;

core.setGameState(&gamestate);

core.init();
core.run();
core.shutdown();

}

* \endcode
* A typical Hello-World game-state would like this
* \code

#include "YGEGameState.h"
#include "YGEObserver.h"
#include "YGEEntity.h"
#include "YGEText.h"

class MyGameState : public YGEGame::YGEGameState {
public:

virtual void init(){

// create a space in which entities can live
YGETimeSpace::YGESpace* space = new YGETimeSpace::YGESpace();

// create someone who percieces the space
YGETimeSpace::YGEObserver* observer = new YGETimeSpace::YGEObserver();

observer->setCameraMode(CAMERA_ORTHOGONAL);
space->getRootEntity()->addChild(observer);


YGETimeSpace::YGEScene scene;
scene.first = space;
scene.second = observer;

// add the scene to list of scenes
sceneList.push_back(scene);

// add the space to the list of spaces
spaceList.push_back(space);

// create an entity which will be the position of the text
YGETimeSpace::YGEEntity* textPos = new YGETimeSpace::YGEEntity();
textPos->setPosition(YGEMath::Vector3(100,100,0));

// add the entity to the root entity of the space
space->getRootEntity()->addChild(textPos);


// register a font so it can be used
YGEGraphics::YGEText::registerFont("VeraMono24", "../media/fonts/VeraMono.ttf", 24);

// create an actual text
YGEGraphics::YGEText* text = new YGEGraphics::YGEText("Hello World", "VeraMono24");

// and add the text to the position entity
textPos->addAsset(text);

}

};

* \endcode
* To add keyboard input, the game-state should implement the YGEKeyDownListener interface,
* and it should be added to the list of inputlisteners by calling
* \code
core.getInputManager()->addKeyDownListener(&gamestate);
* \endcode

*/
#ifndef _YGE_ENGINE_CORE_H_
#define _YGE_ENGINE_CORE_H_

#include "YGEGraphicsCore.h"
#include "YGEInputManager.h"

#include "YGEAudioCore.h"

#include "YGETimer.h"

#include "YGEConsole.h"

#include "YGELogger.h"

#include "YGEGameState.h"

#include "YGEEntity.h"

namespace YGECore {

	/**
	* YGE main game engine class
	* this is an abstract class which cannot be instantiated
	* @see YGEEngineCoreMultiThreaded
	* @see YGEEngineCoreSingleThreaded
	*/
	class YGEEngineCore {
	protected:

		/**
		* pointer to a YGEGraphicsCore. Responsible for graphics rendering stuff.
		*/
		YGEGraphicsCore* graphics;

		/**
		* pointer to a YGEAudioCore. Responsigble for audio rendering stuff.
		*/
		YGEAudio::YGEAudioCore* audio;

		/**
		* pointer to a YGEInputManager. Responsible for input
		* as from keyboard, joystick, gamepad or mouse.
		*/
		YGEInputManager* input;

		/**
		* pointer to a YGELogger
		* since the YGELogger is a singleton, this is not
		* really nessesary. The logger can be used for debug output
		* and the destination of the output can be choosen 
		* (stdout, YGEConsole, file, etc...)
		*/
		YGELogger* logger;

		/**
		* pointer to a YGETimer.
		* This timer is used to measure the framerate.
		*/
		YGETimer* timer;

		/**
		* @brief timer for measuring the time the core needs for graphical stuff
		*/
		YGETimer* timerGraphics;

		/**
		* @brief timer for measuring the time the core needs to calculate physics
		*/
		YGETimer* timerPhysics;

		/**
		* @brief timer for measuring the time the core needs to perform updating
		*/
		YGETimer* timerUpdate;

		/**
		* @brief timer for meauring the time the core needs to tick the entities
		*/
		YGETimer* timerTick;

		/**
		* @brief timer which can be used for other things
		*/
		YGETimer* timerOther;

		/**
		* @brief timer that wil be started on intialization of the engine core
		*/
		YGETimer* timeSinceGameStarted;

		/**
		* @brief a pointer to a gamestate
		*
		* the gamestate provides the core with spaces where updating and physics
		* calculation should be done and with scene which shall be rendered
		*/
		YGEGame::YGEGameState* gamestate;


		/**
		* @brief a pointer to a console for direct user-interaction at runtime
		*
		* commands typed into the console are sendend to processCommand()
		*/
		YGEConsole* console;

		/**
		* @brief toggled by the '`' key
		*/
		bool consoleEnabled;

	public:

		YGEEngineCore();

		~YGEEngineCore();

		/**
		* @brief initialises the core
		*
		* components are created and ressources are loaded
		*/
		virtual void init() = 0;

		/**
		* @brief starts a permanent engine loop
		* 
		* returns if core
		* decides to shut down (window closed etc...);
		* init() should be called before starting the render loop
		*/
		virtual void run() = 0;

		/**
		* @brief free resources etc.
		*/
		virtual void shutdown() = 0;


		/**
		* @brief tells the engine which gamestate to use
		*/
		virtual void setGameState(YGEGame::YGEGameState* state);

		/**
		* @brief returns a pointer to the input manager
		*/
		YGEInputManager* getInputManager();

		/**
		* @brief returns the time the core is running in micro seconds
		*/
		long long getTimeSinceGameStarted();

		/**
		* @brief shows or hides the console
		*/
		void toggleConsole();


		/**
		* @brief send a command to the core.
		*
		* the core will try to interpret the command, if it cannot,
		* it sends the command to current gamestate
		*/
		void processCommand(const char* command);

		/**
		* @brief returns the current fps of the game engine
		*/
		virtual int getFramesPerSecond(){return -1;};
	};

}
#endif