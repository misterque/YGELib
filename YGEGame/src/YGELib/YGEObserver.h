/** @file
* @author Dirk Fortmeier
* @date 4.11.2009
*/

#ifndef _YGE_OBSERVER_H_
#define _YGE_OBSERVER_H_

#include "YGEEntityAsset.h"
#include "YGEEntity.h"
#include <SDL_opengl.h>

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

	public:
		void setCameraMatrix(YGEEntity* rootEntity);

		void setCameraMatrixRotation(YGEEntity* rootEntity);


	};

}

#endif