// EngineTest.cpp : Defines the entry point for the console application.
//

#include "tests.h"

#include "stdafx.h"
#include "time.h"
#include "YGEVector.h"
#include "YGEMatrix.h"
#include "YGEEngineCoreSingleThreaded.h"
#include <iostream>

using namespace std;
using namespace YGEMath;
using namespace YGECore;

void test2(char* test, bool passed){
	cout<<"Test "<<test<<": ";
	if(passed){
		cout<<"passed"<<endl;
	} else {
		cout<<"Not passed!!!"<<endl;
		exit(1);
	}
}

void testMath(){
	Vector3 v1(1.0, 0.0, 1.0);
	Vector3 v2(0.0, 1.0, 0.0);

	v1.echo();


	test2("Vector3 length", v2.length() == 1.0);
	test2("Vector3 lengthSquared", v2.lengthSquared() == 1.0);
	test2("Vector3 Addition1", v1+v2 == Vector3(1.0, 1.0, 1.0) );
	test2("Vector3 Addition2", v1+v2 != Vector3(1.0, 1.0, 2.0) );
	test2("Vector3 Substraction1", v1-v1 == Vector3(0.0, 0.0, 0.0) );
	test2("Vector3 Substraction2", v1-Vector3(0.0, 0.0, 0.0) == v1 );
	test2("Vector3 times Scalar", v1 * 0 == Vector3(0.0, 0.0, 0.0) );
	test2("Vector3 times Scalar", (v1 * 2 - Vector3(2.0, 0.0, 2.0)).length() < 0.01 );
	test2("Vector3 comparison1", Vector3(1.0, 2.0, 4.0) == Vector3(1.0, 2.0, 4.0));
	test2("Vector3 comparison2", Vector3(1.0, 2.0, 4.0) != Vector3(4.0, 2.0, 1.0));

	// assert zeros times zero == zero
	test2("Mat3x3 times Vector3 1", Mat3x3() * Vector3() == Vector3()); 
	// assert ones times vector == vector
	
	// @todo make this working:
	//test("Mat3x3 times Vector3 2", Mat3x3::ones() * v1 == v1);


}

void speedTestMath(){
	Vector3 v1(1.0, 0.0, 1.0);
	Vector3 v2(0.0, 1.0, 0.0);
	Vector3 v3(0.0, 1.0, 0.0);

/*	_SPEEDTEST("Vector Multiplication", 1000000)
		Vector3 r
	_ENDTEST
*/
}

void testCore(){
	YGEEngineCoreSingleThreaded core;

	core.init();
	core.run();
}

int _tmain(int argc, _TCHAR* argv[])
{

	memoryTests();
	cout<<"Testing Engine Features:"<<endl;
	cout<<"01) Math Library"<<endl;
	testMath();
	cout<<"02) Core Functions"<<endl;

	cout<<"03) Particle System"<<endl;
	testParticleSystem();
	
	cout<<"10) Speed Tests"<<endl;
	speedTests();	
	//testCore();
	char a;
	cin>>a;
	return 0;
}

