#include "tests.h"

#include "YGEStaticMesh.h"
#include "YGEHeightmap.h"
#include "YGEEntity.h"
#include "YGEGraphicsCore.h"
#include "YGELogger.h"

#include <iostream>

#include "YGETimer.h"
// create an entity tree
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

	YGECore::YGELogger::getInstance()->log("Initializing SDL Video");

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw YGEExceptionSubsystemError("SDL Video init");
		return;
	}

	YGEGraphics::YGEGraphicsCore core;

	core.init();
	core.reset();






	//
	// SPEEDTEST RESET GRAPICS CORE ************************************************
	timer.startTimer();

	for(int i=0; i<100; i++){
		core.reset();


	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 100.0f <<" ms for resetting graphics core"<<std::endl;



	//
	// SPEEDTEST QUATERNIONROTATIONS ************************************************




	timer.startTimer();

	for(int i=0; i<100000; i++){
		q.rotateVector(v);

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 100000.0f <<" ms for rotating a vector by a quaternion"<<std::endl;

	//
	// SPEEDTEST QUATERNION TO MATRIX ************************************************


	timer.startTimer();

	for(int i=0; i<10000; i++){
		q.getRotationMatrix();

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 10000.0f <<" ms for creating a matrix from a quaternion"<<std::endl;


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
		map.create("images/hmap.bmp", "textures/mud.tex", 1000.0f, 1000.0f, 100.0f); 

	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 5.0f<<" ms for loading heightmap (5x the same)"<<std::endl;


	//
	// SPEEDTEST HEIGHTMAP DISPLAYING ************************************************


	YGEGraphics::YGEHeightmap* map = new YGEGraphics::YGEHeightmap();
	YGETimeSpace::YGEEntity mapPos;
	map->create("images/hmap.bmp", "textures/mud.tex", 1000.0f, 1000.0f, 100.0f); 
	mapPos.addAsset(map);
	core.reset();
	timer.startTimer();
	for(int i=0; i<50; i++){


		core.renderEntity(&mapPos);
	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 50.0f<<" ms for displaying heightmap (50x the same)"<<std::endl;



	//
	// SPEEDTEST MESH DISPLAYING ************************************************



	YGETimeSpace::YGEEntity meshPos;
	YGEGraphics::YGEStaticMesh* mesh = new YGEGraphics::YGEStaticMesh();
	mesh->loadFromOBJ("models/gyro_body.obj");
	meshPos.addAsset(mesh);
	core.reset();
	timer.startTimer();
	for(int i=0; i<50; i++){


		core.renderEntity(&meshPos);
	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 50.0f<<" ms for displaying mesh (50x the same)"<<std::endl;


	//
	// SPEEDTEST ENTITY TREE CREATION ************************************************
	timer.startTimer();

	for(int i=0; i<10; i++){
		YGETimeSpace::YGEEntity *ent = new YGETimeSpace::YGEEntity();
		addfiveents(ent, 3);
		delete ent;


	}

	time = timer.stopTimer();
	std::cout<<std::endl<<time / 1000.0f / 10.0f <<" ms for creating and destroying an entity tree with 5^3=125 entities"<<std::endl;



}