/** @file
* @author Dirk Fortmeier
* @date 4.11.2009
*/

#ifndef _YGE_OBSERVER_H_
#define _YGE_OBSERVER_H_

#include "YGEEntityAsset.h"
#include "YGEEntity.h"
#include <SDL_opengl.h>

#define CAMERA_ORTHOGONAL 1
#define CAMERA_PERSPECTIVE 2

namespace YGETimeSpace {


	/**
	* Observer class.
	* Observers are thrown into a world of entities
	* and are able to.. observe it. Meaning they perceive
	* the enitites through their assets by different senses.
	* These senses are vision (consider the observer as a camera)
	* or hearing (...).
	* An observer itself is an entity.
	*/
	class YGEObserver : public YGEEntity {
	private:
		int cameraMode;

		void setProjectionMatrix();

	public:
		YGEObserver();


		void setCameraMode(int mode);
		void setCameraMatrix(YGEEntity* rootEntity);

		void setCameraMatrixRotation(YGEEntity* rootEntity);


	};

}

#endif