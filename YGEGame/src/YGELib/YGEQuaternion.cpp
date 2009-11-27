#include "YGEQuaternion.h"

namespace YGEMath{


	Quaternion Quaternion::operator + (const Quaternion &q2) const {
			Quaternion result;
			result.w = this->w + q2.w;
			result.x = this->x + q2.x;
			result.y = this->y + q2.y;
			result.z = this->z + q2.z;
			return result;
		}

		Quaternion& Quaternion::operator += (const Quaternion &q2) {
			this->w += q2.w;
			this->x += q2.x;
			this->y += q2.y;
			this->z += q2.z;

			return *this;

		}

		Quaternion Quaternion::operator - (const Quaternion &q2) const {
			Quaternion result;
			result.w = this->w - q2.w;
			result.x = this->x - q2.x;
			result.y = this->y - q2.y;
			result.z = this->z - q2.z;
			return result;
		}

		Quaternion& Quaternion::operator -= (const Quaternion &q2) {
			this->w -= q2.w;
			this->x -= q2.x;
			this->y -= q2.y;
			this->z -= q2.z;

			return *this;

		}

		Quaternion Quaternion::operator * (const Quaternion &q2) const {
			Quaternion result;
			result.w = this->w*q2.w - this->x*q2.x - this->y*q2.y - this->z*q2.z;

			result.x = this->w*q2.x + q2.w*this->x + this->y*q2.z - this->z*q2.y;
			result.y = this->w*q2.y + q2.w*this->y - this->x*q2.z + this->z*q2.x;
			result.z = this->w*q2.z + q2.w*this->z + this->x*q2.y - this->y*q2.x;

			return result;
		}

/*		Quaternion Quaternion::operator * (const Vector3 &q2) const {
			Quaternion result;
			result.w = this->w*q2.w - this->x*q2.x - this->y*q2.y - this->z*q2.z;

			result.x = this->w*q2.x + q2.w*this->x + this->y*q2.z - this->z*q2.y;
			result.y = this->w*q2.y + q2.w*this->y - this->x*q2.z + this->z*q2.x;
			result.z = this->w*q2.z + q2.w*this->z + this->x*q2.y - this->y*q2.x;

			return result;
		}*/








		Quaternion& Quaternion::operator *= (const Quaternion &q2) {
			this->w = this->w*q2.w - this->x*q2.x - this->y*q2.y - this->z*q2.z;
			this->x = this->w*q2.x + q2.w*this->x - this->y*q2.z + this->z*q2.y;
			this->y = this->w*q2.y + q2.w*this->y + this->x*q2.z - this->z*q2.x;
			this->z = this->w*q2.z + q2.w*this->z - this->x*q2.y + this->y*q2.x;

			return *this;
		}
    /*result.w = w*a.w - x*a.x - y*a.y - z*a.z;   
    result.x = w*a.x + x*a.w + z*a.y - y*a.z;   
    result.y = w*a.y + y*a.w + x*a.z - z*a.x;   
    result.z = w*a.z + z*a.w + y*a.x - x*a.y;   
    */

		Quaternion Quaternion::operator * (double v) const {
			Quaternion result;
			result.w = this->w * v;
			result.x = this->x * v;
			result.y = this->y * v;
			result.z = this->z * v;

			return result;

		}

		Quaternion& Quaternion::operator *= (double v) {
			this->w = this->w * v;
			this->x = this->x * v;
			this->y = this->y * v;
			this->z = this->z * v;

			return *this;
		}

		Quaternion Quaternion::operator / (const double d) {
			Quaternion result;
			result = *this;
			result /= d;
			return result;

		}

		Quaternion& Quaternion::operator /= (const double d) {
			w /= d;
			x /= d;
			y /= d;
			z /= d;
			return *this;

		}

		YGEMath::Vector3 Quaternion::operator * (const YGEMath::Vector3 &v) {
			YGEMath::Vector3 result;
			// TODO result = 
			throw YGEExceptionMethodNotImplementedYet();

		}


		Quaternion Quaternion::operator ~(){
			Quaternion result;
			result.w = this->w;
			result.x = - this->x;
			result.y = - this->y;
			result.z = - this->z;
			return result;
		}


		YGEMath::Mat3x3 Quaternion::getRotationMatrix() const{
			YGEMath::Mat3x3 result( 
				1-2*(y*y + z*z),	2*x*y - 2*w*z,		2*w*y + 2*x*z,
				2*w*z+2*x*y,		1-2*(x*x + z*z),	-2*w*x+2*y*z,
				-2*w*y+2*x*z,		2*w*x+2*y*z,		1-2*(x*x + y*y));

			double xx      = x * x;
			double xy      = x * y;
			double xz      = x * z;
			double xw      = x * w;
			double yy      = y * y;
			double yz      = y * z;
			double yw      = y * w;
			double zz      = z * z;
			double zw      = z * w;

			result[0][0]  = 1 - 2 * ( yy + zz );
			result[0][1]  =     2 * ( xy - zw );
			result[0][2]  =     2 * ( xz + yw );
			result[1][0]  =     2 * ( xy + zw );
			result[1][1]  = 1 - 2 * ( xx + zz );
			result[1][2]  =     2 * ( yz - xw );
			result[2][0]  =     2 * ( xz - yw );
			result[2][1]  =     2 * ( yz + xw );
			result[2][2]  = 1 - 2 * ( xx + yy );


			return result;

		}

		void Quaternion::Echo(){
			std::cout<<"w: "<<w<<" x: "<<x<<" y: "<<y<<" z: "<<z<<std::endl;
		}


		void Quaternion::normalize(){
			double length = sqrt(w*w + x*x + y*y + z*z);
			if(length != 0.0f){
				w /= length;
				x /= length;
				y /= length;
				z /= length;
			}
		}

		Quaternion::Quaternion(YGEMath::Mat3x3 a){

			// stolen from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

			double trace = a[0][0] + a[1][1] + a[2][2] + 1.0f;
			if( trace > 0.00001 ) {
				double s = 0.5f / sqrt(trace);
				w = 0.25f / s;
				x = ( a[2][1] - a[1][2] ) * s;
				y = ( a[0][2] - a[2][0] ) * s;
				z = ( a[1][0] - a[0][1] ) * s;
			} else {
				//std::cout<<"adfdgdf"<<std::endl;
				if ( a[0][0] > a[1][1] && a[0][0] > a[2][2] ) {
					double s = 2.0 * (double)sqrt( 1.0 + a[0][0] - a[1][1] - a[2][2]);
					w = (a[2][1] - a[1][2] ) / s;
					x = 0.25f * s;
					y = (a[0][1] + a[1][0] ) / s;
					z = (a[0][2] + a[2][0] ) / s;
				} else if (a[1][1] > a[2][2]) {
					double s = 2.0 * (double)sqrt( 1.0f + a[1][1] - a[0][0] - a[2][2]);
					w = (a[0][2] - a[2][0] ) / s;
					x = (a[0][1] + a[1][0] ) / s;
					y = 0.25f * s;
					z = (a[1][2] + a[2][1] ) / s;
				} else {
					double s = 2.0f * (double)sqrt( 1.0f + a[2][2] - a[0][0] - a[1][1] );
					w = (a[1][0] - a[0][1] ) / s;
					x = (a[0][2] + a[2][0] ) / s;
					y = (a[1][2] + a[2][1] ) / s;
					z = 0.25f * s;
				}
			}

		}

		Quaternion::Quaternion(){
			w = 1;
			x = 0;
			y = 0;
			z = 0;
		}

		Quaternion::Quaternion(double W, double X, double Y, double Z) : w(W), x(X), y(Y), z(Z) {
		}

		Quaternion::Quaternion(const double* q) : w(q[0]), x(q[1]), y(q[2]), z(q[3]) {
		}

		

		Quaternion Quaternion::getConjugate(){
			Quaternion q;
			q.w = w;
			q.x = -x;
			q.y = -y;
			q.z = -z;

			return q;
		}

		Vector3 Quaternion::rotateVector(const Vector3& v){
			Quaternion q(0, v.x, v.y, v.z);
			Quaternion r = ((*this)) * (q * ~(*this));
			return Vector3(r.x, r.y, r.z);
		}


}

