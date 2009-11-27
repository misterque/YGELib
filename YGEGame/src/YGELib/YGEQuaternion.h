#ifndef _YGE_QUATERNION_H_
#define _YGE_QUATERNION_H_


/**
* Quaternion class. Usable for Rotations and Orientations.
*/
#include "YGEMatrix.h"
#include "YGEExceptions.h"

namespace YGEMath{

	struct Quaternion {

		double w;
		double x;
		double y;
		double z;

		Quaternion operator + (const Quaternion &q2) const;

		Quaternion& operator += (const Quaternion &q2);

		Quaternion operator - (const Quaternion &q2) const;

		Quaternion& operator -= (const Quaternion &q2);

		Quaternion operator * (const Quaternion &q2) const;


		Quaternion operator * (const Vector3 &q2) const;



		Quaternion& operator *= (const Quaternion &q2);

		Quaternion operator * (double v) const;

		Quaternion& operator *= (double v);

		Quaternion operator / (const double d);

		Quaternion& operator /= (const double d);

		YGEMath::Vector3 operator * (const YGEMath::Vector3 &v);


		Quaternion operator ~();


		YGEMath::Mat3x3 getRotationMatrix() const;

		void Echo();

		void normalize();

		Quaternion(YGEMath::Mat3x3 a);

		Quaternion();

		Quaternion(double W, double X, double Y, double Z);

		Quaternion(const double* q);

		Quaternion getConjugate();

		Vector3 rotateVector(const Vector3& v);



	};

}



#endif // _QUATERNIONS_H_


