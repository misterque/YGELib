#include "YGESpace.h"

namespace YGETimeSpace{

	void YGESpace::initTime(){

		worldId = dWorldCreate();
		dWorldSetGravity(worldId, 0,0, -9.81);
	}

	dWorldID  YGESpace::getWorldId(){
		//@todo check for if there is no world at all
		return worldId;
	}

	void YGESpace::timeStep(){
		dWorldStep(worldId, 1.0f);

	}

}