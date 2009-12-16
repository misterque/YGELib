#include "YGEEntity.h"
#include "YGESoundAsset.h"
#include "YGEResourceManager.h"
#include "YGEVector.h"

namespace YGEAudio {

	YGESoundAsset::YGESoundAsset() : wantsToBePlayed(2) {

	}

	void YGESoundAsset::render(){

		
		YGEMath::Vector3 v = this->getParent()->getAbsPosition();
		alSource3f(source, AL_POSITION, (float)v.x, (float)v.y, (float)v.z);

		if(wantsToBePlayed > 0 && wantsToBePlayed < 2) {
			alSourcePlay(source);
			wantsToBePlayed++;
		} else {
			wantsToBePlayed++;
		}
	}

	void YGESoundAsset::setSound(const char *filename){
		sound = YGECore::YGEResourceManager::getInstance()->getSound(filename);
		
		alGenSources(1, &source);

		alSourcei(source, AL_BUFFER, sound->getSample());



	}
	void YGESoundAsset::playOnce(){

		alSourcei(source,AL_LOOPING,AL_FALSE);

		wantsToBePlayed = -1;

	}

	void YGESoundAsset::playLooped(){

		alSourcei(source,AL_LOOPING,AL_TRUE);

		wantsToBePlayed = -1;

	}
	void YGESoundAsset::stop(){

		alSourceStop(source);
	}

}