#ifndef _YGE_LOGGER_H_
#define _YGE_LOGGER_H_


#include <iostream>
#include "YGEConsole.h"


namespace YGECore {

class YGELogger {
private:
	YGELogger() {
		activechannel = 0;
		console = NULL;
	}

	YGEConsole* console;
	int activechannel;
	static YGELogger* singleton;

public:
	static YGELogger* getInstance(){
		if(singleton == 0){
			singleton = new YGELogger();
		}
		return singleton;
	}

	void setChannel(int channel){
		activechannel = channel;
	
	}

	void setConsole(YGEConsole *c){
		console = c;
	}

	void log(char* message){
#ifdef _DEBUG
		std::cout<<message<<std::endl;

#endif
	}

	void logToConsole(char* message){
		console->println(message);
	}

	void log(long long number){
#ifdef _DEBUG
		std::cout<<number<<std::endl;

#endif
	}


};

}

#endif