#ifndef _YGE_MATRIX_H_
#define _YGE_MATRIX_H_

#include "YGEVector.h"

namespace YGEMath{

struct Mat2x2 {	
	double values[2][2];

	Mat2x2(){
		values[0][0] = 0.0;
		values[0][1] = 0.0;
		values[1][1] = 0.0;
		values[1][0] = 0.0;
	}

};
	
struct Mat3x3 {
	double values[3][3];

	Mat3x3(){
		values[0][0] = 0.0;
		values[0][1] = 0.0;
		values[0][2] = 0.0;
		values[0][3] = 0.0;

		values[1][0] = 0.0;
		values[1][1] = 0.0;
		values[1][2] = 0.0;
		values[1][3] = 0.0;

		values[2][0] = 0.0;
		values[2][1] = 0.0;
		values[2][2] = 0.0;
		values[2][3] = 0.0;

		values[3][0] = 0.0;
		values[3][1] = 0.0;
		values[3][2] = 0.0;
		values[3][3] = 0.0;


	}

	Vector3 operator*(const Vector3& V){
		Vector3 newVector;

		newVector.x = values[0][0] * V.x + values[1][0] * V.y + values[2][0] * V.z;
		newVector.y = values[0][1] * V.x + values[1][1] * V.y + values[2][1] * V.z;
		newVector.z = values[0][2] * V.x + values[1][2] * V.y + values[2][3] * V.z;

		return newVector;
	}

	static Mat3x3 ones(){
		Mat3x3 newMatrix;

		return newMatrix;

	}

};


struct Mat4x4 {


};
}
#endif