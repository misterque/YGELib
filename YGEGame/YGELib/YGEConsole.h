#ifndef _YGE_CONSOLE_H_
#define _YGE_CONSOLE_H_

#include <string>

// needs current line
// needs history
// needs output
// is a singleton?
class YGEConsole {

	std::string currentLine;
	//std::string history;

	std::string output;

public:

	YGEConsole(){
		output = "Blablabla \n hohohoho \n hihihihih \n";
	}
	void insertKey(char key);

	void draw();

	void evaluateCommand(char* command);

};


#endif
