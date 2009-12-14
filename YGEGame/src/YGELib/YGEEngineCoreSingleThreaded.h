/**
 * @file
 * @author Dirk Fortmeier
 * @date ?
 */
#ifndef _YGE_ENGINE_CORE_SINGLE_THREADED_H_
#define _YGE_ENGINE_CORE_SINGLE_THREADED_H_

#include "YGEEngineCore.h"

namespace YGECore {

	/**
	* YGE main game engine class
	*/
	class YGEEngineCoreSingleThreaded : public YGEEngineCore {
	protected:

		/**
		* time elapsed between two frames
		*/
		long long delta;

		/**
		* stores time since last output of FPS rate
		* if > 1 sec debugout frames
		*/
		long long accumDelta;

		/**
		* frame counter for FPS rate
		*/
		int frames;

		/**
		* @brief framerate
		*/
		int framesPerSecond;

		/**
		 * @brief update the positions of the entities which have YGEBodyAsset attached.
		 *
		 * this is done by querying the positions from the simulation and passing 
		 * forces and torques to the simulation.
		 * additionally, the time of the new position is set
		 *
		 * @see YGETimeSpace::YGEEntity::update
		 * @see YGEPhysics::YGEBodyAsset::update
		 */
		void update();


		/**
		 * @brief sets newPosition and oldPosition
		 *
		 * new and oldPos are requiered for interpolation, the absolutePosition is used for rendering
		 * audio and video
		 * @note this function name maybe confusing, since the calculation of the variable absPosition is done
		 * by the function interpolate()
		 */
		void updateAbsolutePositions();

		/**
		 * @brief interpolates between a newPosition and an oldPosition dependend on the current time
		 *
		 * This is only done if the entity has an absolute position (i.e. YGETimeSpace::YGEEntity::hasAbsolutePosition == true).
		 * Afterwards the YGETimeSpace::YGEEntity::absPos will be set correctly
		 */
		void interpolate();

		/**
		 * @brief querys for SDL_Events and handles them
		 */
		void processEvents();

		/**
		 * @brief handles a single event
		 *
		 * called by processEvents();
		 */
		void processSingleEvent(SDL_Event *event);

		/**
		 * @brief tells the graphics and audio core to render the scene
		 */
		void render();

		/**
		 * @brief for each space, do a timestep
		 */
		void calcPhysics(long long delta);

		/**
		 * @brief tick every entity
		 *
		 * custom entities can overwrite the tick() method to implement custom behavior as
		 * user controlls or AI
		 * @see YGETimeSpace::YGEEntity::tick()
		 */
		void tick()	;

		/**
		 * @brief calculate the framerate
		 */
		void calculateFPSRate();

		/**
		 * @brief limit the frames per second
		 * 
		 * this should be done so there are no more frames calculated as necessary so
		 * the computer running the engine has time for other things
		 */
		void limitFPS();

		/**
		 * @brief debugging helper
		 */
		void printTimes();


		/**
		 * @brief et on change of a gamestate
		 *
		 * if current engine cycle is finished the new gamestate will be used
		 */
		YGEGame::YGEGameState* newGameState;

		/**
		 * @brief true if the engine wants to change the gamestate at the start of
		 * the next cycle
		 */
		bool gameStateChanged;

		/**
		* if set to true, the core will shutdown after the next cycle
		*/
		bool shutdownNow;



	public:
		/**
		* initialises the core
		* components are allocated and ressources are loaded
		*/
		virtual void init();

		/**
		* starts a permanent engine loop, returns if core
		* decides to shut down (window closed etc...);
		* init() should be called before starting the render loop
		*/
		virtual void run();

		/**
		* free resources etc.
		*/
		virtual void shutdown();

		
		virtual void setGameState(YGEGame::YGEGameState* state);

		virtual int getFramesPerSecond(){
			return framesPerSecond;
		}

	};

}
#endif