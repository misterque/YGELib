#include "YGEEntity.h"
#include "YGESoundSource.h"
#include "YGERessourceManager.h"
#include "YGEVector.h"

namespace YGEAudio {

	YGESoundSource::YGESoundSource() : wantsToBePlayed(2) {

	}

	void YGESoundSource::update(long delta){

		
		YGEMath::Vector3 v = this->getParent()->getAbsPosition();
		alSource3f(source, AL_POSITION, v.x, v.y, v.z);

		if(wantsToBePlayed > 0 && wantsToBePlayed < 2) {
			alSourcePlay(source);
			wantsToBePlayed++;
		} else {
			wantsToBePlayed++;
		}
	}

	void YGESoundSource::setSound(const char *filename){
		sound = YGECore::YGERessourceManager::getInstance()->getSound(filename);
		
		alGenSources(1, &source);

		alSourcei(source, AL_BUFFER, sound->getSample());



	}
	void YGESoundSource::playOnce(){

		alSourcei(source,AL_LOOPING,AL_FALSE);

		wantsToBePlayed = -1;

	}

	void YGESoundSource::playLooped(){

		alSourcei(source,AL_LOOPING,AL_TRUE);

		wantsToBePlayed = -1;

	}
	void YGESoundSource::stop(){

		alSourceStop(source);
	}
}