/** @file
 * @author Dirk Fortmeier
 * @todo wrapping in namespace
 */

#ifndef _YGE_SCENE_H_
#define _YGE_SCENE_H_

#include "YGEEntity.h"
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


typedef std::list<YGEScene*> YGESceneList;


#endif