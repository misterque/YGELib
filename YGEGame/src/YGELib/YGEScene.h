/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_SCENE_H_
#define _YGE_SCENE_H_

#include "YGEEntity.h"
#include "YGESpace.h"
#include "YGEObserver.h"

namespace YGETimeSpace{


	/**
	 * @brief a scene consists of a space and an observer
	 */
	typedef std::pair<YGESpace*, YGEObserver*> YGEScene;

	/**
	 * @brief a list of scenes
	 */
	typedef std::list<YGEScene> YGESceneList;

}

#endif