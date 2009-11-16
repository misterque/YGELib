#ifndef _GAME_GYROCOPTER_H_
#define _GAME_GYROCOPTER_H_

#include "YGEStaticMesh.h"
#include "YGEEntity.h"

class GameGyrocopter : public YGETimeSpace::YGEEntity{
private:

	YGEGraphics::YGEStaticMesh meshBody;
	YGEGraphics::YGEStaticMesh meshRotorTop;
	YGEGraphics::YGEStaticMesh meshRotorBack;
	YGEGraphics::YGEStaticMesh meshTailV;
	YGEGraphics::YGEStaticMesh meshTailH;

	YGETimeSpace::YGEEntity posRotorTop;
	YGETimeSpace::YGEEntity posRotorBack;
	YGETimeSpace::YGEEntity posTailV;
	YGETimeSpace::YGEEntity posTailH;


	float fuel;



public:
	GameGyrocopter();

	void update();



};



#endif