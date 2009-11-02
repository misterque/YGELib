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
	Vector3 columns[3];

	Mat3x3(){



	}

	Mat3x3( double aa, double ab, double ac,
		    double ba, double bb, double bc,
			double ca, double cb, double cc){

		columns[0][0] = aa;
		columns[0][1] = ab;
		columns[0][2] = ac;
		columns[1][0] = ba;
		columns[1][1] = bb;
		columns[1][2] = bc;
		columns[2][0] = ca;
		columns[2][1] = cb;
		columns[2][2] = cc;



	}

		Vector3& operator [] (const int index){
			return columns[index];
		}

	Vector3 operator*(const Vector3& V){
		Vector3 newVector;

		newVector.x = columns[0][0] * V.x + columns[1][0] * V.y + columns[2][0] * V.z;
		newVector.y = columns[0][1] * V.x + columns[1][1] * V.y + columns[2][1] * V.z;
		newVector.z = columns[0][2] * V.x + columns[1][2] * V.y + columns[2][2] * V.z;

		return newVector;
	}

	static Mat3x3 ones(){
		Mat3x3 newMatrix;

		return newMatrix;

	}

	double at(int i, int j){
		return columns[i][j];
	}

};


struct Mat4x4 {


};
}
#endif