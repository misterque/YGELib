#ifndef _YGE_VECTOR_H_
#define _YGE_VECTOR_H_

#include <math.h>
#include <iostream>
#include <stdlib.h>

namespace YGEMath{

/**
 * 2d Vector struct
 */
struct Vector2 {
	double x,y;

	Vector2() {
		x = 0;
		y = 0;
	}

	Vector2(double x, double y){
		x = x;
		y = y;
	}

};

/**
 * 3d Vector struct
 */
struct Vector3 {
	/**
	 * x, y, z values of the vector
	 */
	double x,y,z;
	
	Vector3(){
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(double X, double Y, double Z){
		x = X;
		y = Y;
		z = Z;
	}

	// @todo: move this somewhere else
	static double randDouble(){
		int i = rand() % 20000;
		i -= 10000;
		return (double)i / 10000.0f;
	}


	
	static Vector3 random(double v){
		Vector3 r;
		r.x = randDouble() * v;
		r.y = randDouble() * v;
		r.z = randDouble() * v;
		return r;

	}


	double& operator [] (const int index){
		switch(index){
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			case 2:
				return z;
				break;
		}
	}

	/**
	 * add a vector to an other
	 */
	 Vector3 operator+(const Vector3& V){
		Vector3 sum;

		sum.x = this->x + V.x;
		sum.y = this->y + V.y;
		sum.z = this->z + V.z;

		return sum;

	}

	 Vector3& operator+=(const Vector3& V){

		this->x += V.x;
		this->y += V.y;
		this->z += V.z;

		return *this;

	}


 	/**
	 * substract a vector from an other
	 */
	Vector3 operator-(const Vector3& V){
		Vector3 sum;

		sum.x = this->x - V.x;
		sum.y = this->y - V.y;
		sum.z = this->z - V.z;

		return sum;

	}

	 Vector3& operator-=(const Vector3& V){

		this->x -= V.x;
		this->y -= V.y;
		this->z -= V.z;

		return *this;

	}

	/**
	 * multiply Vector with scalar
	 */
	Vector3 operator*(const double s){
		Vector3 newVector;

		newVector.x = x * s;
		newVector.y = y * s;
		newVector.z = z * s;

		return newVector;

	}

	Vector3& operator*=(const double s){

		this->x *= s;
		this->y *= s;
		this->z *= s;

		return *this;

	}

	/**
	 * @todo: comments
	 */
	bool operator==(const Vector3& V){
		if(this->x == V.x &&
			this->y == V.y &&
			this->z == V.z) {
				return true;
		}
		return false;
	}

	/**
	 * @todo: comments
	 */
	bool operator!=(const Vector3& V) {
		return ! (*this == V);
	}


	/**
	 * @todo: comments
	 */
	inline double lengthSquared(){
		return x*x + y*y + z*z;
	}

	
	/**
	 * @todo: comments
	 */
	inline double length(){
		return sqrt(lengthSquared());
	}


	/**
	 * @todo: comments
	 */
	double operator*(const Vector3& V){
		return	this->x * V.x +
				this->y * V.y +
				this->z * V.z;
	}



	/**
	 * calculates the cross product
	 * @todo: comments
	 */
	Vector3 operator^(const Vector3& V){
		Vector3 newVector;

		newVector.x = this->y * V.z - this->z * V.y;
		newVector.y = this->z * V.x - this->x * V.z;
		newVector.z = this->x * V.y - this->y * V.x;

		return newVector;

	}

	Vector3 interpolate(const Vector3& V, double alpha){
		Vector3 newVector = (*this + V) * alpha;

		return newVector;

	}


	/**
	 * function for debugging purposes.
	 * echoes the values of the vector to stdout
	 */
	void echo(){
		std::cout<<x<<" | "<<y<<" | "<<z<<std::endl;
	}
};


}
#endif