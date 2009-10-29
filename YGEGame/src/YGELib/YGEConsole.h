/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_CONSOLE_H_
#define _YGE_CONSOLE_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include <string>



namespace YGECore {


	class YGEEngineCore;
// needs current line
// needs history
// needs output
// is a singleton?


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
	 * adds a character to the current input line
	 */
	void insertKey(SDL_keysym key);

	/**
	 * draw the console on top of the rendering window
	 */
	void draw();

	/**
	 * evalute a string containing a command
	 */
	void evaluateCommand(const char* command);

	void println(const char* line);

	void init(YGEEngineCore *core);

	void update();

};

}
#endif
