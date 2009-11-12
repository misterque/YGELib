/** @file
 * @author Dirk Fortmeier
 * @date 9.11.2009
 */

#ifndef _YGE_PARTICLE_SYSTEM_H_
#define _YGE_PARTICLE_SYSTEM_H_

#include "YGEGraphicsAsset.h"
#include "YGEVector.h"
#include "YGERessourceManager.h"

namespace YGEGraphics {

class YGEParticle {

private:
	friend class YGEParticleList;
	/**
	 * private constructor = only YGEParticleLists are allowed to create
	 * particles.
	 */
	YGEParticle() {
		nextParticle = 0;
		previousParticle = 0;
	}
public:
	bool alive;
	double timeToLive;
	YGEParticle *nextParticle;
	YGEParticle *previousParticle;
	YGEMath::Vector3 position;

};

class YGEParticleList {
private:
	YGEParticle* firstAlive;
	YGEParticle* firstDead;

	int numberOfDeadParticles;
	int numberOfAliveParticles;

public:
	YGEParticleList() {
		firstAlive = 0;
		firstDead = 0;

		numberOfDeadParticles = 0;
		numberOfAliveParticles = 0;
	}


	/**
	 * moves a particle to the list of dead particles
	 */
	void setDead(YGEParticle* p);

	/**
	 * moves a particle to the list of alive particles
	 */
	void setAlive(YGEParticle* p);


	/**
	 * creates either a new particle, or returns the first from the
	 * list of dead particles. the particle is then put in the list
	 * of alive particles.
	 *
	 * @return a particle to fill with data
	 */
	YGEParticle* getParticle();

	int getNumberOfAliveParticles() {
		return numberOfAliveParticles;
	}
	
	int getNumberOfDeadParticles(){
		return numberOfDeadParticles;
	}

	YGEParticle* getFirstAliveParticle(){
		return firstAlive;
	}

};

class YGEParticleSystem : public YGEGraphicsAsset {
private:
	YGEParticleList particleList;
	YGECore::Texture* texture;
public:

	YGEParticleSystem();

	virtual void draw(YGEGraphicsContext* context);

	void update();

};

}

#endif