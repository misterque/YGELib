#include "YGEAudioCore.h"
#include "YGEObserver.h"

#define NULL 0

namespace YGEAudio {
	void YGEAudioCore::renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer){
		if(space->getSoundEnabled()) {
			setListenerPosition(observer->getAbsPosition(), space);
		}

		renderEntity(space->getRootEntity());
	}


	void YGEAudioCore::init(){
		alutInit(NULL, NULL);
//		alutInitWithoutContext (NULL, NULL);


//device = alcOpenDevice(NULL);
		volume = 50;


	}

		
	void YGEAudioCore::renderEntity(YGETimeSpace::YGEEntity* entity){
		// get every graphical asset and render it
		std::list<YGEAudio::YGESoundAsset*>* assets = entity->getSoundAssets();
		for(std::list<YGEAudio::YGESoundAsset*>::iterator iter = assets->begin();
			iter != assets->end();
			iter++){
				(*iter)->render();
		}

		// recursive call on all children
		std::list<YGETimeSpace::YGEEntity*>* children = entity->getChildren();
		for(std::list<YGETimeSpace::YGEEntity*>::iterator iter = children->begin();
			iter != children->end();
			iter++){
				 renderEntity(*iter);

		}
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