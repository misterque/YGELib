#include "tests.h"

#include "YGEStaticMesh.h"
#include "YGEHeightmap.h"
#include "YGEEntity.h"

#include <iostream>

#include "YGETimer.h"

void addfiveents(YGETimeSpace::YGEEntity* ent, int recursions){
	if(recursions <= 0) {
		return;
	} else {
		for(int i = 0; i<5; i++){
			YGETimeSpace::YGEEntity* child = new YGETimeSpace::YGEEntity();
			ent->addChild(child);
			addfiveents(child, recursions - 1);
		}
	}
}
void speedTests(){

	YGECore::YGETimer timer;
	long long time;	
	YGEMath::Vector3 v;
	YGEMath::Quaternion q;
//
// SPEEDTEST QUATERNIONROTATIONS ************************************************
/*



	timer.startTimer();

	for(int i=0; i<10000; i++){
		v.rotateBy(q);

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 10000.0f <<" ms for rotating a vector by a quaternion"<<std::endl;
*/
//
// SPEEDTEST QUATERNION TO MATRIX ************************************************


	timer.startTimer();

	for(int i=0; i<1000; i++){
		q.getRotationMatrix();

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 1000.0f <<" ms for creating a matrix from a quaternion"<<std::endl;


//
// SPEEDTEST MESHLOADING ************************************************
	timer.startTimer();
	for(int i=0; i<10; i++){
		YGEGraphics::YGEStaticMesh mesh;
		mesh.loadFromOBJ("models/gyro_body.obj");

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000 / 10 <<" ms for loading a mesh (10x the same)"<<std::endl;

//
// SPEEDTEST HEIGHTMAP LOADING ************************************************
	timer.startTimer();
	for(int i=0; i<5; i++){
		YGEGraphics::YGEHeightmap map;
		map.create("images/hmap.bmp", 1000.0f, 1000.0f, 100.0f); 

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000 / 5<<" ms for loading heightmap (5x the same)"<<std::endl;


//
// SPEEDTEST ENTITY TREE CREATION ************************************************
	timer.startTimer();
	for(int i=0; i<10; i++){
		YGETimeSpace::YGEEntity ent;
		addfiveents(&ent, 3);


	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000 / 10 <<" ms for creating and destroying an entity tree with 5^3=125 entities"<<std::endl;



}