#ifndef _YGE_LOGGER_H_
#define _YGE_LOGGER_H_


#include <iostream>
#include <sstream>
#include "YGEConsole.h"

#ifdef _DEBUG
#define debugout(s); YGECore::YGELogger::getInstance()->log(s);
#else
#define debugout(s);
#endif


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

	void logToConsole(int message){
		std::stringstream s;
		s<<message;
		console->println(s.str().c_str());
	}



	void log(long long number){
#ifdef _DEBUG
		std::cout<<number<<std::endl;

#endif
	}


};

}

#endif