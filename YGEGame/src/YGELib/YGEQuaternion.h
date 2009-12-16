#ifndef _YGE_QUATERNION_H_
#define _YGE_QUATERNION_H_


#include "YGEMatrix.h"
#include "YGEExceptions.h"

namespace YGEMath{

	/**
	* @brief usable for Rotations and Orientations.
	*/

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


		Quaternion operator ~() const;


		/**
		 * @brief create a 3x3 rotation matrix from the quaternion
		 */
		YGEMath::Mat3x3 getRotationMatrix() const;

		/**
	     * @brief debugout the quaternion
		 */
		void Echo() const;

		/**
		 * @brief normalize the quaternion
		 *
		 * afterwards sqrt(w*w + x*x + y*y + z*z) = 1
		 */
		void normalize();

		/**
		 * @brief create a quaternion from a rotation matrix
		 */
		Quaternion(YGEMath::Mat3x3 a);

		Quaternion();

		Quaternion(double W, double X, double Y, double Z);

		/**
		 * @brief create a quaternion from double[4] array
		 */
		Quaternion(const double* q);

		/**
		 * @brief get the conjugate of a quaternion
		 *
		 * in terms of rotation quaternions, the conjugate is the rotation in the opposite direction
		 */
		Quaternion getConjugate() const;

		/**
		 * rotate a vector by this quaternion
		 */
		Vector3 rotateVector(const Vector3& v) const;



	};

}



#endif // _QUATERNIONS_H_


