#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "YGEEntity.h"
#include "YGEObserver.h"


class Camera :	public YGETimeSpace::YGEEntity {
private:
	YGETimeSpace::YGEEntity* pitcher;
	YGETimeSpace::YGEEntity* distancer;
	YGETimeSpace::YGEObserver* cam;
	float pitch;
	float yaw;
	float distance;
public:

	Camera(){
		pitcher = new YGETimeSpace::YGEEntity();
		distancer = new YGETimeSpace::YGEEntity();
		cam = new YGETimeSpace::YGEObserver();

		this->addChild(pitcher);
		pitcher->addChild(distancer);
		distancer->addChild(cam);
		
		pitch = 0.6f;
		yaw = 0;
		distance = 20;
		distancer->translate3d(0,0, distance);

		 rotate(0,0);
	}

	YGETimeSpace::YGEObserver* getObserver(){
		return cam;
	}

	void rotate(float y, float p){

		yaw += y;
		pitch += p;

	YGEMath::Quaternion q;
	q.w = cos(yaw);
	q.x = 0;
	q.y = sin(yaw);
	q.z = 0;

	//YGEMath::Quaternion p = smallBoxPos->getOrientation();

	this->setOrientation(q);

	q.w = cos(pitch);
	q.x = sin(pitch);
	q.y = 0;
	q.z = 0;

	pitcher->setOrientation(q);


	}


};


#endif

