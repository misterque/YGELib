#include <cstdlib>
#include <SDL_opengl.h>
#include "YGEParticleSystem.h"
#include "YGELogger.h"

namespace YGEGraphics {
	void YGEParticleList::setAlive(YGEGraphics::YGEParticle *p){

		if(!p->alive){

			// remove from dead list
			if(p->previousParticle != NULL) {
				p->previousParticle->nextParticle = p->nextParticle;
			} else {
				firstDead = p->nextParticle;
			}
			
			if(p->nextParticle != NULL) {
				p->nextParticle->previousParticle = p->previousParticle;
			} 

			// add to head of alive list
			p->nextParticle = this->firstAlive;
			p->previousParticle = NULL;
			this->firstAlive = p;

			p->alive = true;

			//increase alive counter
			numberOfAliveParticles++;
			numberOfDeadParticles--;
		}

	}

	void YGEParticleList::setDead(YGEGraphics::YGEParticle *p){

		if(p->alive){
			// remove from alive list
			if(p->previousParticle != NULL) {
				p->previousParticle->nextParticle = p->nextParticle;
			} else {
				firstAlive = p->nextParticle;
			}
			if(p->nextParticle != NULL) {
				p->nextParticle->previousParticle = p->previousParticle;
			} 

			// add to head of dead list
			p->nextParticle = firstDead;
			p->previousParticle = NULL;
			firstDead = p;

			p->alive = false;

			// increase dead counter
			numberOfDeadParticles++;
			numberOfAliveParticles--;
		}
	}

	YGEParticle* YGEParticleList::getParticle(){
		YGEParticle* p;

		// reuse a dead particle
		if(numberOfDeadParticles > 0){
			p = this->firstDead;
			setAlive(p);


		}
		// or create a new one
		else {
			p = new YGEParticle();
			p->alive = true;
			p->previousParticle = NULL;
			p->nextParticle = this->firstAlive;
			if(p->nextParticle != NULL) {
				p->nextParticle->previousParticle = p;
			}
			this->firstAlive = p;
			numberOfAliveParticles++;

		}
		return p;
	}

	void YGEParticleSystem::update(){
		YGEParticle* p = particleList.getFirstAliveParticle();
		YGEParticle* p2;

		while(p != NULL){
			p->timeToLive -= 0.1;
			p2 = p->nextParticle;
			// check if it is time to die
			if(p->timeToLive < 0.0f) {
				particleList.setDead(p);
			}
			// if not, do other stuff
			else {
				// calc new position
				// for now, just brownian motion
				p->position += YGEMath::Vector3::random(0.1);


			}
			p = p2;
		}

		// calc the amount of particles to spawn
		// should be dependand on framerate and respawn rate
		int spawnnew = 2;
		for(int i = 0; i<spawnnew; i++){
			YGEParticle* newParticle = particleList.getParticle();
			newParticle->timeToLive = 5.0f;
			newParticle->position.x = 0.0f;
			newParticle->position.y = 0.0f;
			newParticle->position.z = 0.0f;
			
		}

	

	}

	void YGEParticleSystem::draw(YGEGraphicsContext *context){
		
		YGEParticle* p = particleList.getFirstAliveParticle();

		while(p != NULL){
			glBegin(GL_POINTS);
			glVertex3f(p->position.x, p->position.y, p->position.z); 
			glEnd();
			p = p->nextParticle;
		}
	}

};