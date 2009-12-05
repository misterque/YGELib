#include "YGESound.h"
#include <AL/alut.h>

#include "YGELogger.h"

namespace YGEAudio{

	void YGESound::load(const char *filename){

		alSampleSet = alutCreateBufferFromFile(filename);

		if(alSampleSet == NULL) {
			ALenum error = alutGetError();

			debugout(alutGetErrorString(error));
			YGECore::YGELogger::getInstance()->logToConsole(alutGetErrorString(error));
		}

		
		


	}

	unsigned int YGESound::getSample(){
		return alSampleSet;
		
	}


}