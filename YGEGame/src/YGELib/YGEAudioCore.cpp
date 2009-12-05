#include "YGEAudioCore.h"

#define NULL 0

namespace YGEAudio {

	void YGEAudioCore::init(){
		alutInit(NULL, NULL);
//		alutInitWithoutContext (NULL, NULL);


//device = alcOpenDevice(NULL);
		volume = 50;


	}

	void YGEAudioCore::playMusic(const char* filename) {


	}

	void YGEAudioCore::setListenerPosition(const YGEMath::Vector3 &v, YGETimeSpace::YGESpace* space){
		/*if(contexts.find(space) == contexts.end()) {
			if (device) {
				ALCcontext* context = alcCreateContext(device,NULL);
				contexts[space] = context;
						alcMakeContextCurrent(context);
			}
		}*/

		alListener3f(AL_POSITION, v.x, v.y, v.z);
	}

	void YGEAudioCore::enableListenerForSpace(YGETimeSpace::YGESpace* space){
		/*if(contexts.find(space) != contexts.end()) {
		ALCcontext* context = contexts.find(space)->second;
		alcMakeContextCurrent(context);
		}
		*/

	}

	void YGEAudioCore::setSoundVolume(int volume){
		if(volume > 100) {
			volume = 100;
		}
		if(volume < 0) {
			volume = 0;
		}

		this->volume = volume;
	}

	int YGEAudioCore::getSoundVolume(){
		return volume;
	}

	YGEAudioCore* YGEAudioCore::singleton = NULL;
}