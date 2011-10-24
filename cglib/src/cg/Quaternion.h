// This file is part of CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

namespace cg {

	/** Template class for a Quaternion in which the imaginary part is represented by a 3D vector v
	 *  and the real part is represented by a value w. 
	 *	Q = qx.i + qy.j + qz.k + qw 
	 */
	template<class T>
	class Quaternion {

	public:
		/** Vector representing the quaternion's imaginary part. 
		 */
		Vector3<T> v;
		/** Value representing the quaternion's real part. 
		 */
		T w;

		/** Creates a quaternion where w = 1. 
		 */
		Quaternion() : w(1) {}
		
		/**	Creates a quaternion where v = qv and w = qw.
		 *	\param	qv	A 3D vector for the imaginary part.
		 *	\param	qw	A value for the real part. 
		 */
		Quaternion(const Vector3<T> qv, T qw) : v(qv), w(qw) {}
		
		/**	Creates a quaternion where v(qx) = qx, v(qy) = qy, v(qz) = qz and w = qw.
		 *	\param	qx	X value for the imaginary part.
		 *	\param	qy	Y value for the imaginary part.
		 *	\param	qz	Z value for the imaginary part.
		 *	\param	qw	Value for the real part. 
		 */
		Quaternion(const T qx, const T qy, const T qz, T qw) : v(qx,qy,qz), w(qw) {}
		
		/** Quaternion's destructor. 
		 */
		~Quaternion() {}

		/** Sets v = qv and w = qw.
		 *	\param	qv	A 3D vector for the imaginary part.
		 *	\param	qw	A value for the real part. 
		 */
		void set(const Vector3<T> qv, T qw) {
			v.set(qv);
			w = qw;
		}
		
		/**	Sets v(qx) = qx, v(qy) = qy, v(qz) = qz and w = qw.
		 *	\param	qx	X value for the imaginary part.
		 *	\param	qy	Y value for the imaginary part.
		 *	\param	qz	Z value for the imaginary part.
		 *	\param	qw	Value for the real part. 
		 */
		void set(const T qx, const T qy, const T qz, T qw) {
			v.set(qx,qy,qz);
			w = qw;
		}
		
		/** Gets the quaternion's imaginary and real parts.
		 *	\param[out] qv	A 3D vector to put the imaginary part.
		 *	\param[out] qw	A variable to put the real part. 
		 */
		void get(Vector3<T>& qv, T& qw) {
			qv = v;
			qw = w;
		}
		
		/** Gets the quaternion's imaginary and real parts.
		 *	\param[out]	qx	A variable to put the the x value of the imaginary part.
		 *	\param[out] qy	A variable to put the the y value of the imaginary part.
		 *	\param[out] qz	A variable to put the the z value of the imaginary part.
		 *	\param[out] qw	A variable to put the real part. 
		 */
		void get(T& qx, T& qy, T& qz, T& qw) {
			qx = v[0];
			qy = v[1];
			qz = v[2];
			qw = w;
		}

		//---<angle,axis>---

		/** Rotates the quaternion a number of radians around an axis.
		 *	\param angle	The rotation angle in radians.
		 *	\param axis		A vector representing the axis of the rotation.
		 */
		void setRotationRad(T angle, Vector3<T> axis) {
			angle = angle/2;
			v = normalize(axis);
			v *= sin(angle);
			w  = cos(angle);
		}
		
		/** Rotates the quaternion a number of degrees around an axis.
		 *	\param angle	The rotation angle in degrees.
		 *	\param axis		A vector representing the axis of the rotation.
		 */
		void setRotationDeg(T angle, Vector3<T> axis) {
			setRotationRad((T)DEGREES_TO_RADIANS * angle, axis);
		}
		
		/** Gets the quaternion's rotation as an angle (in radians) and an axis.
		 *	\param[out]	angle	A variable to put the rotation's angle in radians.
		 *	\param[out] axis	A variable to put the rotation's axes.
		 */
		void getRotationRad(T& angle, Vector3<T>& axis, const T threshold=0.001) {
			if(w < -1.0) {
				w = -1.0;
			} else if(w > 1.0) {
				w = 1.0;
			}
			angle = 2 * acos(w);
			if (angle < threshold) {
				axis = Vector3<T>(1,0,0);
			} else  {
				axis = v / sin(angle);
			}
			if (angle > PI) {
				axis = -axis;
			}
			axis = normalize(axis);
		}
		
		/** Gets the quaternion's rotation as an angle (in degrees) and an axis.
		 *	\param[out]	angle	A variable to put the rotation's angle in degrees in.
		 *	\param[out]	axis	A variable to put the rotation's axes in.
		 */
		void getRotationDeg(T& angle, Vector3<T>& axis, const T threshold=0.001) {
			getRotationRad(angle,axis,threshold);
			angle = (T)RADIANS_TO_DEGREES * angle;
		}
		
		/** Gets the quaternion as a 4x4 (rotation) matrix.
		 *	\param[out]	matrix	An array of lenght 16 to put the matrix in.
		 */
		void getGLMatrix(T matrix[16]) {
			T xx = v[0] * v[0];
			T xy = v[0] * v[1];
			T xz = v[0] * v[2];
			T xw = v[0] * w;
			T yy = v[1] * v[1];
			T yz = v[1] * v[2];
			T yw = v[1] * w;
			T zz = v[2] * v[2];
			T zw = v[2] * w;

			matrix[0] = 1.0 - 2.0 * ( yy + zz );
			matrix[1] = 2.0 * ( xy + zw );
			matrix[2] = 2.0 * ( xz - yw );
			matrix[3] = 0.0;

			matrix[4] = 2.0 * ( xy - zw );
			matrix[5] = 1.0 - 2.0f * ( xx + zz );
			matrix[6] = 2.0 * ( yz + xw );
			matrix[7] = 0.0;

			matrix[8] = 2.0 * ( xz + yw );
			matrix[9] = 2.0 * ( yz - xw );
			matrix[10] = 1.0 - 2.0 * ( xx + yy );
			matrix[11] = 0.0;

			matrix[12] = 0.0;
			matrix[13] = 0.0;
			matrix[14] = 0.0;
			matrix[15] = 1.0;
		}

		//---<vector_from,vector_to>---

		/** Sets the quaternion's as two vectors.
		 *	\param[out]	from	A 3D vector to put the vector where the rotation starts.
		 *	\param[out]	to		A 3D vector to put the vector where the rotation ends.
		 */
		void setRotation(const Vector3<T>& from, const Vector3<T>& to, const T threshold = 0.001) {
			Vector3<T> v0 = normalize(from);
			Vector3<T> v1 = normalize(to);
			v = cross(v0, v1);
			double l = length(v);
			if(l < threshold) {
				v = Vector3<T>(1,0,0);
			} else {
				v = normalize(v);
			}
			double a = acos(dot(v0,v1))/2;
			w  = (T)cos(a);
			v *= (T)sin(a);
		}

        //---<comparison>---

        /**	Compares if the quaternion is equal to another quaternion.
		 *	\param	q	The quaternion to compare to.
		 *	\return True if the quaternions are equal, false otherwise.
		 */
		bool operator==(const Quaternion& q) const {
			return (q.w == w && q.v == v);
		}
		
        /**	Compares if the quaternion is different from another quaternion.
		 *	\param	q	The quaternion to compare to.
		 *	\return	True if the quaternions are different, false otherwise.
		 */
		bool operator!=(const Quaternion& q) const {
            return (q.w != w || q.v != v);
        }

		/**	Compares if two quaternions are equal within a threshold.
		 *	\param	q0			A quaternion to compare.
		 *	\param	q1			A quaternion to compare.
		 *	\param	threshold	A threshold value.
		 *	\return	True if the quaternions are equal, false otherwise.
		 */
		friend const bool isEqual(const Quaternion<T>& q0, const Quaternion<T>& q1, T threshold) {
			return (fabs(q0.w - q1.w) < threshold) && (isEqual(q0.v,q1.v,threshold));
        }
		
		//---<unary>---

		/** Calculates the quaternion's conjugate. 
		 *	~Q = - qx.i - qy.j - qz.k + qw
		 *	\return	The quaternion's conjugate.
		 */
		const Quaternion<T> operator~() const {
		    return Quaternion<T>(-v, w);
        }
		
		//---<binary>---

		/**	Adds the quaternion to another quaternion.
		 *	\param	q	The quaternion to add to.
		 *	\return The quaternion resulting from the addition.
		 */
		const Quaternion<T> operator+(const Quaternion<T>& q) const {
			return Quaternion<T>(v + q.v, w + q.w);
		}
		
		/**	Multiplies the quaternion by another quaternion.
		 *	\param	q	The quaternion to multiplie with.
		 *	\return The quaternion resulting from the product.
		 */
		const Quaternion<T> operator*(const Quaternion<T>& q) const {
			T _w = w * q.w    - v[0] * q.v[0] - v[1] * q.v[1] - v[2] * q.v[2];
			T _x = w * q.v[0] + v[0] * q.w    + v[1] * q.v[2] - v[2] * q.v[1];
			T _y = w * q.v[1] + v[1] * q.w    + v[2] * q.v[0] - v[0] * q.v[2];
			T _z = w * q.v[2] + v[2] * q.w    + v[0] * q.v[1] - v[1] * q.v[0];
			return Quaternion<T>(_x,_y,_z,_w);
		}
		
		/**	Multiplies the quaternion by a value.
		 *	\param	q	The value to multiplie with.
		 *	\return		The quaternion resulting from the product.
		 */
		const Quaternion<T> operator*(T s) const {
			return Quaternion<T>(s * v, s * w);
		}

		//---<stream>---

		/** Writes a quaternion to a stream.
		 *	\param	os	A stream where to write the quaternion.
		 *	\param	q	The quaternion to be written.
		 *	\return		The stream with the written quaternion.
		 */
		friend inline std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q) {
			os << "( ";
			for(int i = 0; i < 3; i++) {
				os << q.v[i] << " ";
			}
			os << " ~ " << q.w << " ";
			os << ")";
			return os;
		}
		
		/** Writes the contents of a stream to a quaternion 
		 *	\param	os	The stream to be written.
		 *	\param	q	A quaternion where to write the stream.
		 *	\return		The quaternion with the written stream.
		 */
        friend inline std::istream& operator>>(std::istream& is, Quaternion<T>& q) {
			for(int i = 0; i < 3; i++) {
				is >> q.v[i];
			}
			is >> q.w;
            return is;
        }

		//---<generic.math>---

		/**	Calculates the squared norm of a quaternion.
		 *	\param	q	A quaternion.
		 *	\return		The squared norm of the quaternion.
		 */
		friend const T squaredNorm(const Quaternion<T>& q) {
			return q.v[0]*q.v[0] + q.v[1]*q.v[1] + q.v[2]*q.v[2] + q.w*q.w;
		}
		
		/**	Normalizes a quaternion.
		 *	\param	q	A quaternion.
		 *	\return		The normalized quaternion.
		 */
		friend const Quaternion<T> normalize(const Quaternion<T>& q) {
			return q * (1 / squaredNorm(q));
		}
		
		/**	Calculates the inverse of a quaternion.
		 *	\param	q	A quaternion.
		 *	\return		The inversed quaternion.
		 */
		friend const Quaternion<T> inverse(const Quaternion<T>& q) {
			return ~q * (1 / squaredNorm(q));
		}
		
		/**	Applies a quaternion's rotation to a vector.
		 *	\param	q	A quaternion.
		 *	\param	q	A 3D vector.
		 *	\return		The vector after applying the rotation.
		 */
		friend const Vector3<T> apply(const Quaternion<T>& q, const Vector3<T>& v) {
			Quaternion r = q * Quaternion(v,1) * inverse(q);
			return Vector3<T>(r.v);
		}
		
		/**	Computes a slerp (spherical linear interpolation).
		 *	\param	q0	A quaternion representing one extreme.
		 *	\param	q1	A quaternion representing the other extreme.
		 *	\param	t	The amount of interpolation between the two extremes (0 <= t <= 1).
		 *	\result		The quaternion resulting from the interpolation.
		 */
		friend const Quaternion<T> slerp(const Quaternion<T>& q0, const Quaternion<T>& q1, T t) {
			T angle = acos(q0.v[0]*q1.v[0] + q0.v[1]*q1.v[1] + q0.v[2]*q1.v[2] + q0.w*q1.w);
			return (q0 * sin((1-t)*angle) + q1 * sin(t*angle)) * (1/sin(angle));
		}
	};

	//---<multiply by a factor on the left>---

	/**	Multiplies a value by a quaternion.
	 *	\param	q	The value to multiplie with.
	 *	\return		The quaternion resulting from the product.
	 */
	template<class T>
	inline const Quaternion<T> operator*(T s, const Quaternion<T>& q) {
		return Quaternion<T>(s * q.v, s * q.w);
	}

	//---<predefined types>---
	typedef Quaternion<double> Quaterniond;
	typedef Quaternion<float> Quaternionf;
}

#endif // QUATERNION_H
