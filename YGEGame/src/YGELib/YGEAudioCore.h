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

	/**
	 * manages playback of audio files.
	 */
	class YGEAudioCore {
		/**
		 * recursivly called function for updating the position of
		 * the sound sources. starts sounds as well.
		 */
		void renderEntity(YGETimeSpace::YGEEntity* entity);

	private:
		/**
		* pointer to singleton instance
		*/
		static YGEAudioCore* singleton;

		/**
		 * openal device
		 */
		ALCdevice* device;

		/**
		 * map of openal contexts
		 * usage of contexts is not implemented yet
		 */
		std::map<YGETimeSpace::YGESpace*, ALCcontext*> contexts;

		/**
		 * sound volume in percent
		 */
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

		/**
		 * sets the position of the openal listner
		 */
		void setListenerPosition(const YGEMath::Vector3 &v, const YGEMath::Quaternion &q, YGETimeSpace::YGESpace* space);

		/**
		 * enables sound for a space. in fact, this is a workaround
		 */
		void enableListenerForSpace(YGETimeSpace::YGESpace* space);

		/**
		 * update all YGESoundAssets in a space, starts playing of
		 * sounds.
		 */
		void renderSpace(YGETimeSpace::YGESpace* space, YGETimeSpace::YGEObserver* observer);

	};

}

#endif