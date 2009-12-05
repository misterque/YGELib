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
	class YGESoundSource : public YGETimeSpace::YGEEntityAsset {
	private:
		YGESound* sound;

		ALuint source;

		int wantsToBePlayed;

	public:
		//	virtual void draw(YGEGraphicsContext* context) = 0;
		YGESoundSource();

		virtual void update(long delta);

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