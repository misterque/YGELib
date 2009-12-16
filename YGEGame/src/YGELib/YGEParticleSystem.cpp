#include <cstdlib>
#include "GLee.h"

#include <SDL_opengl.h>
#include "YGEParticleSystem.h"
#include "YGELogger.h"
#include "YGEEntity.h"
#include <cassert>

namespace YGEGraphics {
	void YGEParticleList::setAlive(YGEGraphics::YGEParticle *p){

		assert(!p->alive);

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
		if(p->nextParticle != NULL) {
			p->nextParticle->previousParticle = p;
		}
		p->previousParticle = NULL;
		this->firstAlive = p;

		p->alive = true;

		//increase alive counter
		numberOfAliveParticles++;
		numberOfDeadParticles--;

	}

	void YGEParticleList::setDead(YGEGraphics::YGEParticle *p){

		assert(p->alive);

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
			if(this->firstAlive != NULL) {
				this->firstAlive->previousParticle = p;
			}
			this->firstAlive = p;
			assert(firstAlive);
			numberOfAliveParticles++;

		}


		return p;
	}

	YGEParticleSystem::YGEParticleSystem(){
		texture = YGECore::YGEResourceManager::getInstance()->getTexture("textures/particle.tex");

		spawnVelocity = YGEMath::Vector3(0,-1,0);
		spawnRandomVelocity = YGEMath::Vector3(0.3f,0.3f,0.3f);
		addVelocity = YGEMath::Vector3(0,-1,0);
		addRandomVelocity = YGEMath::Vector3(0.1f,0.1f,0.1f);
		spawnPerSecond = 50.0f;
		spawnAccum = 0;

	}

	void YGEParticleSystem::tick(long delta){


		double seconds = delta / 1000000.0f;

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
				p->position += p->velocity * seconds;
				p->velocity += YGEMath::Vector3::random( addRandomVelocity ) * seconds;
				p->velocity +=  addVelocity * seconds;



			}
			p = p2;
		}

		// calc the amount of particles to spawn
		// should be dependand on framerate and respawn rate
		spawnAccum += seconds;
		int numberOfParticlesToSpawn = (int)(spawnPerSecond * (spawnAccum));

		spawnAccum -= numberOfParticlesToSpawn / spawnPerSecond ;

		if(enabled == false) {
			numberOfParticlesToSpawn = 0;
		}
		for(int i = 0; i<numberOfParticlesToSpawn; i++){

			YGEParticle* newParticle = particleList.getParticle();
			newParticle->timeToLive = 3.0f;

			newParticle->position = this->getParent()->getAbsPosition();

			newParticle->velocity = spawnVelocity;
			newParticle->velocity += YGEMath::Vector3::random( spawnRandomVelocity );

		}



	}

	void YGEParticleSystem::draw(YGEGraphicsContext *context){

		YGEParticle* p = particleList.getFirstAliveParticle();


		glPushMatrix();
		context->glGetCameraMatrix();

		glEnable(GL_TEXTURE_2D);

		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

		glBindTexture(GL_TEXTURE_2D, texture->textureID);

		glColor3f(1,1,1);

		glEnable( GL_POINT_SPRITE );

		glTexEnvi( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );


		GLfloat fSizes[2];
		glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, fSizes);
		//glGetFloatv
		float quadratic[] =  { 1.0f, 0.0f, 0.01f };

		glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, quadratic );

		glPointParameterf( GL_POINT_FADE_THRESHOLD_SIZE, 60.0f );

		glPointParameterf( GL_POINT_SIZE_MIN, 5.0f );

		glPointParameterf( GL_POINT_SIZE_MAX, 260.0f );

		glPointSize(150.0f);

		glBegin(GL_POINTS);
		while(p != NULL){
			glVertex3f((GLfloat)p->position.x, (GLfloat)p->position.y, (GLfloat)p->position.z); 
			p = p->nextParticle;
		}
		glEnd();

		glPopMatrix();

	}


};