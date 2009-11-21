/**
* @file
* @author Dirk Fortmeier
* @date 20.11.2009
*/


#ifndef _YGE_AUDIO_CORE_H_
#define _YGE_AUDIO_CORE_H_


namespace YGEAudio {

	class YGEAudioCore {

	private:
		/**
		 * pointer to singleton instance
		 */
		static YGEAudioCore* singleton;

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
	};

}

#endif