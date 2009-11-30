#include "GameRocket.h"

GameRocket::GameRocket(){
	// add the body
	addAsset(&body);
	// add the mesh
	addAsset(new YGEGraphics::YGESimpleBox());



	//@todo add the particle system

	lifetime = 0;

}

void GameRocket::tick(long delta){
	lifetime += delta / 1000000.0f;
	//unaffect the rocket by gravity
	body.addAbsoluteForce(0, 9.81f, 0);

	//thrust the rocket!
	body.addRelativeForce(0,0,-100.0f);

		dBodySetLinearDamping(body.getBodyId(), 0.01);

		if(lifetime > 20) {
			body.disable();
			//delete this;
			return;
		}
}

void GameRocket::processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider){
	getParent()->removeChild(this);

};