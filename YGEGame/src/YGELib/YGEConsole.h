/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_CONSOLE_H_
#define _YGE_CONSOLE_H_

#include <SDL_ttf.h>

#include <string>

namespace YGECore {

// needs current line
// needs history
// needs output
// is a singleton?

	/**
	 * command line console class for interaction with the game engine
	 */
class YGEConsole {

	std::string currentLine;
	//std::string history;

	std::string output;

public:

	YGEConsole(){
		output = "Blablabla \n hohohoho \n hihihihih \n";
	}
	/**
	 * adds a character to the current input line
	 */
	void insertKey(char key);

	/**
	 * draw the console on top of the rendering window
	 */
	void draw();

	/**
	 * evalute a string containing a command
	 */
	void evaluateCommand(char* command);

	void init();

};

}
#endif
