/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_CONSOLE_H_
#define _YGE_CONSOLE_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include <string>



namespace YGECore {

	// forward declaration
	class YGEEngineCore;

	struct consoleLine {
		std::string text;
		GLuint texture;
		int width;
		int height;

		consoleLine(){
			texture = -1;
		}
	};
	/**
	 * command line console class for interaction with the game engine
	 */
class YGEConsole {

	consoleLine output[10];

	consoleLine currentLine;

	YGEEngineCore *core;

public:

	YGEConsole();
	/**
	 * @adds a character to the current input line
	 */
	void insertKey(SDL_keysym key);

	/**
	 * @draw the console on top of the rendering window
	 */
	void draw();

	/**
	 * @brief evalute a string containing a command
	 *
	 * basically sends this command to the engine core
	 */
	void evaluateCommand(const char* command);

	/**
	* @brief print something to the console
	*/
	void println(const char* line);

	/**
	 * @brief initialize this subsystem
	 */
	void init(YGEEngineCore *core);

	/**
	 * @brief update the console
	 *
	 * when this method is called, all lines of the console are rendered to textures
	 */
	void update();

};

}
#endif
