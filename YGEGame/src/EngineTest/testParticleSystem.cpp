#include "tests.h"
#include "YGEParticleSystem.h"
#include <cassert>

using namespace YGEGraphics;

void test(char* test, bool passed){
	cout<<"Test "<<test<<": ";
	if(passed){
		cout<<"passed"<<endl;
	} else {
		cout<<"Not passed!!!"<<endl;
		//assert(false);
		exit(1);
	}
}

void testParticleSystem(){

	YGEParticleList plist;
	YGEParticleList* l = &plist;

	test("ParticleList init 1", plist.getNumberOfAliveParticles() == 0);
	test("ParticleList init 2", plist.getNumberOfDeadParticles() == 0);
	plist.getParticle();
	plist.getParticle();
	YGEParticle* p = plist.getParticle();
	test("ParticleList add 1", plist.getNumberOfAliveParticles() == 3);
	test("ParticleList add 2", plist.getNumberOfDeadParticles() == 0);

	plist.setDead(p);
	test("ParticleList setDead 1", plist.getNumberOfAliveParticles() == 2);
	test("ParticleList setDead 2", plist.getNumberOfDeadParticles() == 1);

	YGEParticle* p2 = plist.getParticle();

	test("ParticleList get 1", plist.getNumberOfAliveParticles() == 3);
	test("ParticleList get 2", plist.getNumberOfDeadParticles() == 0);
	test("ParticleList get 3", p == p2);

	plist.getParticle();
	plist.getParticle();

	p = plist.getFirstAliveParticle();
	int c = 0;
	while(p != NULL){
		c++;
		p = p->nextParticle;
	}
	test("ParticleList getFirstAlive 1", c == 5);

	p = plist.getFirstAliveParticle();
	while(p != NULL){
		p2 = p;
		p = p->nextParticle;
		plist.setDead(p2);
	}

	test("ParticleList getFirstAlive 2", plist.getNumberOfAliveParticles() == 0);
	test("ParticleList getFirstAlive 3", plist.getNumberOfDeadParticles() == 5);


}


