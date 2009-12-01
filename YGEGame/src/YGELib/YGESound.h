/**
* @file
* @author Dirk Fortmeier
* @date 1.12.2009
*/


#ifndef _YGE_SOUND_H_
#define _YGE_SOUND_H_

#include <al.h>

namespace YGEAudio {

	class YGESound {
	private:
		char *buffer;
		ALenum alFormatBuffer;
		ALsizei alFreqBuffer;
		long alBufferLen;
		ALboolean alLoop;
		unsigned int alSource; 
	public:


	};

}

#endif