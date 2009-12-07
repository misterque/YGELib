#ifndef _YGE_LOGGER_H_
#define _YGE_LOGGER_H_


#include <iostream>
#include <sstream>
#include "YGEConsole.h"

#include "SDL.h"
#include "SDL_thread.h"

#ifdef _DEBUG
#define debugout(s); YGECore::YGELogger::getInstance()->log(s);
#else
#define debugout(s);
#endif


namespace YGECore {

class YGELogger {
private:

	SDL_mutex* mutex;
	YGELogger() {
		mutex = SDL_CreateMutex();
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

	void log(const char* message){
#ifdef _DEBUG
		SDL_mutexP(mutex);
		std::cout<<message<<std::endl;
		SDL_mutexV(mutex);
#endif
	}

	void logToConsole(const char* message){
		SDL_mutexP(mutex);
		console->println(message);
		SDL_mutexV(mutex);
	}

	void logToConsole(int message){
		SDL_mutexP(mutex);
		std::stringstream s;
		s<<message;
		console->println(s.str().c_str());
		SDL_mutexV(mutex);
	}



	void log(long long number){
#ifdef _DEBUG
		SDL_mutexP(mutex);		
		std::cout<<number<<std::endl;
		SDL_mutexV(mutex);
#endif
	}

		void log(double number){
#ifdef _DEBUG
		SDL_mutexP(mutex);
		std::cout<<number<<std::endl;
		SDL_mutexV(mutex);
#endif
	}


};

}

#endif