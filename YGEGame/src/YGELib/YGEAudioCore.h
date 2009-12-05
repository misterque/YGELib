/**
* @file
* @author Dirk Fortmeier
* @date 20.11.2009
*/


#ifndef _YGE_AUDIO_CORE_H_
#define _YGE_AUDIO_CORE_H_

#include <al.h>
#include <alc.h>
#include <AL/alut.h>



#include "YGEVector.h"
#include "YGESpace.h"

#include <map>

namespace YGEAudio {

	class YGEAudioCore {
		void renderEntity(YGETimeSpace::YGEEntity* entity);

	private:
		/**
		 * pointer to singleton instance
		 */
		static YGEAudioCore* singleton;

		ALCdevice* device;

		std::map<YGETimeSpace::YGESpace*, ALCcontext*> contexts;

		
		int volume;
	public:
		/**
		 * @return returns a pointer to the singleton
		 */
		static YGEAudioCore* getInstance(){
			if(singleton == 0){
				singleton = new YGEAudioCore();
			}
			return singleton;
		}


		/**
		 * initialise the sound subsystem
		 */
		void init();

		/**
		 * play a song from a file
		 */
		void playMusic(const char* filename);

		/**
		 * sets the sound fx volume in percent
		 */
		void setSoundVolume(int volume);

		/**
		 * gets the sound fx volume in percent
		 */
		int getSoundVolume();

		/**
		 * sets the music volume in percent
		 */
		void setMusicVolume(int volume);

		/**
		 * gets the music volume in percent
		 */
		int getMusicVolume();


		void setListenerPosition(const YGEMath::Vector3 &v, YGETimeSpace::YGESpace* space);
		
		void enableListenerForSpace(YGETimeSpace::YGESpace* space);


	void renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer);

	};

}

#endif