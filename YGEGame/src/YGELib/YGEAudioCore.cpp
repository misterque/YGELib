#include "YGEAudioCore.h"
#include "YGEObserver.h"

#define NULL 0

namespace YGEAudio {
	void YGEAudioCore::renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer){
		if(space->getSoundEnabled()) {
			setListenerPosition(observer->getAbsPosition(), observer->getAbsOrientation(), space);

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

	void YGEAudioCore::setListenerPosition(const YGEMath::Vector3 &v, const YGEMath::Quaternion &q, YGETimeSpace::YGESpace* space){
		/*if(contexts.find(space) == contexts.end()) {
			if (device) {
				ALCcontext* context = alcCreateContext(device,NULL);
				contexts[space] = context;
						alcMakeContextCurrent(context);
			}
		}*/

		YGEMath::Vector3 front = q.rotateVector(YGEMath::Vector3(0, 0, -1));
		YGEMath::Vector3 up = q.rotateVector(YGEMath::Vector3(0, 1, 0));

		ALfloat orientation[6];

		orientation[0] = (ALfloat)front.x;
		orientation[1] = (ALfloat)front.y;
		orientation[2] = (ALfloat)front.z;
		orientation[3] = (ALfloat)up.x;
		orientation[4] = (ALfloat)up.y;
		orientation[5] = (ALfloat)up.z;

		alListener3f(AL_POSITION, (ALfloat)v.x, (ALfloat)v.y, (ALfloat)v.z);
		alListenerfv(AL_ORIENTATION, orientation);

		alListenerf(AL_GAIN, pow(2.0f, (volume - 50)/10.0f));
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