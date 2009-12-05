/**
* @file
* @author Dirk Fortmeier
* @date 1.12.2009
*/


#ifndef _YGE_SOUND_H_
#define _YGE_SOUND_H_

#include <al.h>

namespace YGECore{
	class YGERessourceManager;
}

namespace YGEAudio {

	class YGESound {

	private:
		friend class YGECore::YGERessourceManager;

		/**
		* load a sound from a file
		* @param filename path relative to application
		*        executable
		* @throws YGEExceptionFileNotFound
		* @throws YGEExceptionMethodNotImplementedYet
		*/
		void load(const char* filename);



	unsigned int alSampleSet; 
	public:
		unsigned int getSample();



	};

}

#endif