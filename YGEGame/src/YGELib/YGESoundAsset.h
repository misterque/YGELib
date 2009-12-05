/**
* @file
* @author Dirk Fortmeier
* @date 1.12.2009
*/

#ifndef _YGE_SOUND_SOURCE_H_
#define _YGE_SOUND_SOURCE_H_

#include "YGEEntityAsset.h"
#include "YGESound.h"


namespace YGEAudio {
	class YGESoundAsset : public YGETimeSpace::YGEEntityAsset {
	private:
		friend class YGEAudioCore;
		YGESound* sound;

		ALuint source;

		int wantsToBePlayed;

	public:
		//	virtual void draw(YGEGraphicsContext* context) = 0;
		YGESoundAsset();

		// @todo remove this
		virtual void render();

		virtual YGETimeSpace::AssetType getAssetType(){
			return YGETimeSpace::Sound;
		}

		virtual void enable(){};

		virtual void disable(){ 
			stop();
		};

		void playOnce();

		void playLooped();

		void stop();

		void setSound(const char* filename);

	};

}

#endif