#include "YGESpace.h"

namespace YGETimeSpace{

	void YGESpace::initTime(){

		worldId = dWorldCreate();
		dWorldSetGravity(worldId, 0, 0.81, 0);
	}

	dWorldID  YGESpace::getWorldId(){
		//@todo check for if there is no world at all
		return worldId;
	}

	void YGESpace::timeStep(long long delta){
		dWorldStep(worldId, 0.1 );

	}

}