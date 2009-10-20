#ifndef _YGE_LOGGER_H_
#define _YGE_LOGGER_H_


#include <iostream>

class YGELogger {
private:
	YGELogger() {

	}

	static YGELogger* singleton;

public:
	static YGELogger* getInstance(){
		if(singleton == 0){
			singleton = new YGELogger();
		}
		return singleton;
	}

	void log(char* message){
#ifdef _DEBUG
		std::cout<<message<<std::endl;
#endif
	}


};

#endif