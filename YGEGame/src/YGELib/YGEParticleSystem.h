/** @file
 * @author Dirk Fortmeier
 * @date 9.11.2009
 */

#ifndef _YGE_PARTICLE_SYSTEM_H_
#define _YGE_PARTICLE_SYSTEM_H_

#include "YGEGraphicsAsset.h"
#include "YGEVector.h"
#include "YGEResourceManager.h"

namespace YGEGraphics {

	/** 
	 * @brief particle class representing single particle
	 */
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
	YGEMath::Vector3 velocity;



};

/**
 * @brief double list of particles
 *
 * this class is used for heavy reusing of memory allocated for
 * particles. if a particle dies, it simply is just added to the list
 * of dead particles from where it will be returned if a a new particle
 * is created.
 */
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


/**
 * @brief particle system asset
 * @note, to this time, all properties of the particle system are hardcoded
 */
class YGEParticleSystem : public YGEGraphicsAsset {
private:
	YGEParticleList particleList;
	YGECore::YGETexture* texture;
	YGEMath::Vector3 spawnVelocity;
	YGEMath::Vector3 spawnRandomVelocity;
	YGEMath::Vector3 addVelocity;
	YGEMath::Vector3 addRandomVelocity;

	double spawnPerSecond;
	double spawnAccum;

public:

	YGEParticleSystem();

	virtual void draw(YGEGraphicsContext* context);

	/**
	 * @brief move, kill, spawn particles
	 */
	virtual void tick(long delta);

};

}

#endif