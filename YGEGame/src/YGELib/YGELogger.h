#ifndef _YGE_LOGGER_H_
#define _YGE_LOGGER_H_


#include <iostream>
namespace YGECore {

class YGELogger {
private:
	YGELogger() {
		activechannel = 0;
	}

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

	void log(char* message){
#ifdef _DEBUG
		std::cout<<message<<std::endl;

#endif
	}

	void log(long long number){
#ifdef _DEBUG
		std::cout<<number<<std::endl;

#endif
	}


};

}

#endif