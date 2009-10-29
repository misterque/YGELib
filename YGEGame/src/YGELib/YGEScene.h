/** @file
 * @author Dirk Fortmeier
 */

#ifndef _YGE_SCENE_H_
#define _YGE_SCENE_H_

#include "YGEEntity.h"

class YGEScene {


private:
	YGEEntity rootNode;
public:
	void render();

	YGEEntity* getRootNode(){
		return &rootNode;
	}
};

#endif