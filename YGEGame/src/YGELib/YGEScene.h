/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_SCENE_H_
#define _YGE_SCENE_H_

#include "YGEEntity.h"

namespace YGETimeSpace{


/** this class seems to be dispensable.
 * considering a "root" entity to be a scene
 * is more logical.
 *
 * the root-entity
 * being a set of all sets,
 * mirroring the lord
 *
 * no, the root entity is just the set of all sets which are
 * part of a set.
 * 
 * i am getting stupid here...
 */

/*
class YGEScene {


private:
	YGEEntity rootNode;

	void renderEntity(YGEEntity* entity);

public:
	void render();

	YGEEntity* getRootNode(){
		return &rootNode;
	}

	YGEScene();
};

*/
typedef std::list<YGEEntity*> YGESceneList;

}

#endif