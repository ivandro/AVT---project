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

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cassert>
#include <sstream>

namespace cg {

	/** Set of vector classes:
	 *    cg::Vector2i - 2D vector of integer precision.
	 *    cg::Vector2f - 2D vector of single precision.
	 *    cg::Vector2d - 2D vector of double precision.
	 *    cg::Vector3i - 3D vector of integer precision.
	 *    cg::Vector3f - 3D vector of single precision.
	 *    cg::Vector3d - 3D vector of double precision.
	 */

    const double DEGREES_TO_RADIANS =  0.01745329251994329547;
    const double RADIANS_TO_DEGREES = 57.29577951308232185913;
    const double PI                 =  3.14159265358979323846;

#define for_each_i(X)\
    for(int i=0;i<N;i++){X;}

	/** Template class for a N-dimensional vector containing type T values. 
	 */
    template<class V, class T, int N>
    class Vector {

    public:
        /** Structure containing the vector's data. 
		 */
		T data[N];

		/** Creates an empty vector. 
		 *	\return		A Vector with 0 in all of its positions.
		 */
        Vector() { for_each_i( data[i] = 0 ) }
		
		/** Creates a vector containing a given data in all of its positions.
		 *	\param	x	The data to be put in the vector.
		 *	\return		A Vector containing x in all of its positions. 
		 */
        Vector(const T x) { for_each_i( data[i] = x ) }
		
		/** Creates a vector containing the values of a given array. 
		 *	\param	v[N]	An array.
		 *	\return			A Vector containing the values of the given array in the corresponding positions.
		 */
		Vector(const T v[N]){ for_each_i( data[i] = v[i] ) }
		
		/** Copy constructor. 
		 *	\param	v	The Vector to be copied.
		 *	\return		A copy of the given Vector.
		 */
		Vector(const V& v) { for_each_i( data[i] = v.data[i] ) }

		/** Returns the Vector's value at a given position.
		 *	\param	i	An integer representing a position in the Vector.
		 *	\return		A constant representing the Vector's value in the position i. 
		 */
		const T& operator[](int i) const { 
			assert(i<N);
			return data[i]; 
		}
		
		/** Returns the Vector's value at a given position.
		 *	\param	i	An integer representing a position in the Vector.
		 *	\return		The Vector's value in the position i. 
		 */
		T& operator[](int i) { 
			assert(i<N);
			return data[i];
		}
		
		/** Returns the Vector.
		 *	\return		The Vector. 
		 */
		T* get() { return &data[0]; }
		
		/** Returns the Vector.
		 *	\return		A constant representing the Vector. 
		 */
		const T* get() const { return &data[0]; }

        //---<comparison>---

		/** Verifies if all the Vector's values are equal to a given value. 
		 *	\param	k	The value to compare.
		 *	\return		True if all the Vector's values are equal to k, false otherwise.
		 */
        bool operator==(const T k) const {
            for_each_i( if( data[i] != k ) return false; )
            return true;
        }
        
		/** Compares two Vectors. 
		 *	\param	v	A second Vector to compare the Vector with.
		 *	\return		True if the two Vectors are equal, false otherwise.
		 */
        bool operator==(const V& v) const {
            for_each_i( if( data[i] != v.data[i] ) return false; )
            return true;
        }
		
        /** Verifies if all the vector's values are different from k. 
		 */
        bool operator!=(const T k) const {
            for_each_i( if( data[i] != k ) return true; )
            return false;
        }
		
		/** Verifies if all the vector's values are different from the corresponding values in v. 
		 */
        bool operator!=(const V& v) const {
            for_each_i( if( data[i] != v.data[i] ) return true; )
            return false;
        }
		
		/** Verifies if two vectors are equal within a given threshold.
		 */
        friend const bool isEqual(const V& v0, const V& v1, T threshold) {
            for_each_i( if( fabs((double)v0.data[i] - (double)v1.data[i]) > (double)threshold ) return false; )
            return true;
        }

        //---<assignment>---

		/** Multiplies each vector's value by k */
		void operator*=(T k) { for_each_i( data[i] *= k ); }
		
		/** Divides each vector's value by k */
		void operator/=(T k) { for_each_i( data[i] /= k ); }
		
		/** Multiplies each vector's value by the corresponding v value */
		void operator*=(const V& v) { for_each_i( data[i] *= v[i] ); }
		
		/** Divides each vector's value by the corresponding v value */
		void operator/=(const V& v) { for_each_i( data[i] /= v[i] ); }
		
		/** Adds to each vector's value the corresponding v value */
		void operator+=(const V& v) { for_each_i( data[i] += v[i] ); }
		
		/** Subtracts to each vector's value the corresponding v value */
		void operator-=(const V& v) { for_each_i( data[i] -= v[i] ); }

        //---<unary>---

		/** Negates each value in the vector */
		const V operator-() const {
		    V v_new;
		    for_each_i( v_new.data[i] = -data[i]; )
		    return v_new;
        }

        //---<binary>---

		/** Adds two vectors. */
		const V operator+(const V& v) const {
		    V v_new;
		    for_each_i( v_new.data[i] = data[i] + v.data[i]; )
		    return v_new;
        }
		
		/** Subtracts two vectors. */
		const V operator-(const V& v) const {
		    V v_new;
		    for_each_i( v_new.data[i] = data[i] - v.data[i]; )
		    return v_new;
        }
		
		/** Multiplies each element of the vector with the corresponding element of v */
		const V operator*(const V& v) const {
		    V v_new;
		    for_each_i( v_new.data[i] = data[i] * v.data[i]; )
		    return v_new;
        }
		
		/** Multiplies the vector by k */
		const V operator*(const T k) const {
		    V v_new;
		    for_each_i( v_new.data[i] = data[i] * k; )
		    return v_new;
        }
		
		/** Divides each element of the vector with the corresponding element of v */
		const V operator/(const V& v) const {
		    V v_new;
		    for_each_i( v_new.data[i] = data[i] / v.data[i]; )
		    return v_new;
        }
		
		/** Divides the vector by k. */
		const V operator/(const T k) const {
		    V v_new;
		    for_each_i( v_new.data[i] = data[i] / k; )
		    return v_new;
        }

        //---<stream>---

        /** Prints a vector to a stream. */
		friend inline std::ostream& operator<<(std::ostream& os, const V& v) {
            os << "( ";
            for_each_i( os << v[i] << " "; )
            os << ")";
            return os;
        }
		
		/** Inserts a stream contents to a vector. */
        friend inline std::istream& operator>>(std::istream& is, V& v) {
            for_each_i( is >> v[i]; )
            return is;
        }

        //---<generic.math>---

		/** Returns a vector's squared lenght. */
		friend const T squaredLength(const V& v){
		    T result = 0;
		    for_each_i( result += v.data[i] * v.data[i]; )
			return result;
		}
		
		/** Returns a vector's lenght. */
		friend const double length(const V& v){
		    double result = 0;
		    for_each_i( result += v.data[i] * v.data[i]; )
			return sqrt( result );
		}
		
		/** Returns a normalized vector. */
		friend const V normalize(const V& v){
			V v_new;
			double d = length(v);
			if(d != 0.0) {
                v_new = v / (T)d;
			}
            return v_new;
		}
		
		/** Returns the dot product between two vectors. */
		friend const T dot(const V& v1, const V& v2){
            T result = 0;
            for_each_i( result += v1.data[i]*v2.data[i]; )
            return result;
		}
		
		/** Returns the midpoint between two vectors. */
		friend const V midpoint(const V& v1, const V& v2){
			return (v1 + v2) / (T)2;
		}
		
		/** Returns the centroid of three vectors. */
		friend const V centroid(const V& v1, const V& v2,const V& v3){
			return (v1 + v2 + v3) / (T)3;
		}
	};

	/** Template class for a 2-dimensional (2D) vector containing type T values. 
	 */
    template <class T>
	class Vector2 : public Vector<Vector2<T>,T,2> {
	public:
		/** X coordinate of the 2D vector */
		static const Vector2<T> nx;

		/** Y coordinate of the 2D vector */
		static const Vector2<T> ny;

		/** Creates an empty 2D vector */
		Vector2() {}
		
		/** Receives a value k of type T and creates a 2D vector. The vector will contain k in all of its positions. */
		Vector2(const T k) : Vector<Vector2<T>,T,2>(k) {}
		
		/** Receives a 2D array of type T and creates a 2D vector. The values of the given array will be copied to the corresponding vector positions. */
		Vector2(const T v[2]) : Vector<Vector2<T>,T,2>(v) {}
		
		/** Creates a copy of a 2D vector. */
		Vector2(const Vector2<T>& v) : Vector<Vector2<T>,T,2>(v) {}
		
		/** Receives two values of type T and creates a 2D vector. The vector will contain x in the first position and y in the second position. */
        Vector2(const T x, const T y) {
            Vector<Vector2<T>,T,2>::data[0] = x;
            Vector<Vector2<T>,T,2>::data[1] = y;
        }

		/** Destroys a 2D vector. */
		~Vector2() {}

		/** Sets all 2D vector values to k. */
		void set(const T k) {
			Vector<Vector2<T>,T,2>::data[0] = k;
			Vector<Vector2<T>,T,2>::data[1] = k;
		}
		
		/** Copies the values from vector v to the corresponding 2D vector positions. */
		void set(const Vector2<T>& v) {
			Vector<Vector2<T>,T,2>::data[0] = v.data[0];
			Vector<Vector2<T>,T,2>::data[1] = v.data[1];
		}
		
		/** Sets the 2D vector's first position value to x and the second position value to y. */
		void set(const T x, const T y) {
			Vector<Vector2<T>,T,2>::data[0] = x;
			Vector<Vector2<T>,T,2>::data[1] = y;
		}
		
		/*
		friend const T determinant(const Vector2<T>& v1, const Vector2<T>& v2) {
			return ( v1.data[0] * v2.data[1]
                   - v1.data[1] * v2.data[0] );
		}
		*/

        //---<rotation.2d>---

		/** Rotates a 2D vector theta_rad radians. */
		friend const Vector2<T> rotateRad(const Vector2<T>& v0, double theta_rad) {
			double c = cos(theta_rad);
			double s = sin(theta_rad);
			T x = (T)(v0.data[0] * c - v0.data[1] * s);
			T y = (T)(v0.data[1] * c + v0.data[0] * s);
			return Vector2<T>(x,y);
		}
		
		/** Rotates a 2D vector theta_deg degress. */
		friend const Vector2<T> rotateDeg(const Vector2<T>& v0, double theta_deg) {
			return rotateRad(v0, DEGREES_TO_RADIANS * theta_deg);
		}
		
		/** Rotates a 2D vector positioned at center theta_rad radians. */
		friend const Vector2<T> rotateAtRad(const Vector2<T>& v0, double theta_rad, const Vector2<T>& center) {
			Vector2<T> v_new;
			v_new.set(v0);
			v_new -= center;
			v_new = rotateRad(v_new, theta_rad);
			v_new += center;
			return v_new;
		}
		
		/** Rotates a 2D vector positioned at center theta_deg degrees. */
		friend const Vector2<T> rotateAtDeg(const Vector2<T>& v0, double theta_deg, const Vector2<T>& center) {
			return rotateAtRad(v0, theta_deg * DEGREES_TO_RADIANS, center);
		}
	};

	template <class T>
	const Vector2<T> Vector2<T>::nx(1,0);

	template <class T>
	const Vector2<T> Vector2<T>::ny(0,1);


	/** Template class for a 3-dimensional (3D) vector containing type T values. 
	 */
	template <class T>
	class Vector3 : public Vector<Vector3<T>,T,3> {
	public:
		/** X coordinate of the 3D vector */
		static const Vector3<T> nx;
		
		/** Y coordinate of the 3D vector */
		static const Vector3<T> ny;
		
		/** Z coordinate of the 3D vector */
		static const Vector3<T> nz;

		/** Creates an empty 3D vector */
		Vector3() {}
		
		/** Receives a value k of type T and creates a 3D vector. The vector will contain k in all of its positions. */
		Vector3(const T k) : Vector<Vector3<T>,T,3>(k) {}
		
		/** Receives a 3D array of type T and creates a 3D vector. The values of the given array will be copied to the corresponding vector positions. */
		Vector3(const T v[3]) : Vector<Vector3<T>,T,3>(v) {}
		
		/** Creates a copy of a 3D vector. */
		Vector3(const Vector3<T>& v) : Vector<Vector3<T>,T,3>(v) {}
		
        /** Receives two values of type T and creates a 3D vector. The vector will contain x in the first position, y in the second position and z in the third position. */
        Vector3(const T x, const T y, const T z) {
            Vector<Vector3<T>,T,3>::data[0] = x;
            Vector<Vector3<T>,T,3>::data[1] = y;
            Vector<Vector3<T>,T,3>::data[2] = z;
        }

		/** Destroys a 3D vector. */
		~Vector3() {}

        /** Sets all 3D vector values to k. */
		void set(const T k) {
			Vector<Vector3<T>,T,3>::data[0] = k;
			Vector<Vector3<T>,T,3>::data[1] = k;
			Vector<Vector3<T>,T,3>::data[2] = k;
		}
		
		/** Copies the values from vector v to the corresponding 3D vector positions. */
		void set(const Vector3<T>& v) {
			Vector<Vector3<T>,T,3>::data[0] = v.data[0];
			Vector<Vector3<T>,T,3>::data[1] = v.data[1];
			Vector<Vector3<T>,T,3>::data[2] = v.data[2];
		}
		
		/** Sets the 3D vector's first position value to x, the second position value to y and the third position to z. */
		void set(const T x, const T y, const T z) {
			Vector<Vector3<T>,T,3>::data[0] = x;
			Vector<Vector3<T>,T,3>::data[1] = y;
			Vector<Vector3<T>,T,3>::data[2] = z;
		}
		
		/** Returns the cross product between two 3D vectors. */
		friend const Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2){
			return Vector3<T>( v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1],
                               v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2],
                               v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0] );
		}
		
		/*
		friend const T determinant(const Vector3<T>& v1, const Vector3<T>& v2,const Vector3<T>& v3){
			return ( v1.data[0] * v2.data[1] * v3.data[2]
                   + v1.data[1] * v2.data[2] * v3.data[0]
                   + v1.data[2] * v2.data[0] * v3.data[1]
                   - v1.data[2] * v2.data[1] * v3.data[0]
                   - v1.data[0] * v2.data[2] * v3.data[1]
                   - v1.data[1] * v2.data[0] * v3.data[2] );
		}
		*/

        //---<rotation.3d>---

		/** Rotates a 3D vector theta_rad radians in the YoZ plane. */
		friend const Vector3<T> rotateXRad(const Vector3<T>& v0, double theta_rad) {
			double c = cos(theta_rad);
			double s = sin(theta_rad);
			T x = v0.data[0];
			T y = (T)(v0.data[1] * c - v0.data[2] * s);
			T z = (T)(v0.data[2] * c + v0.data[1] * s);
			return Vector3<T>(x,y,z);
		}
		
		/** Rotates a 3D vector theta_deg degrees in the YoZ plane. */
		friend const Vector3<T> rotateXDeg(const Vector3<T>& v0, double theta_deg) {
			return rotateXRad(v0, DEGREES_TO_RADIANS * theta_deg);
		}
		
		/** Rotates a 3D vector theta_rad radians in the XoZ plane. */
		friend const Vector3<T> rotateYRad(const Vector3<T>& v0, double theta_rad) {
			double c = cos(theta_rad);
			double s = sin(theta_rad);
			T x = (T)(v0.data[0] * c + v0.data[2] * s);
			T y = v0.data[1];
			T z = (T)(v0.data[2] * c - v0.data[0] * s);
			return Vector3<T>(x,y,z);
		}
		
		/** Rotates a 3D vector theta_deg degrees in the XoZ plane. */
		friend Vector3<T> rotateYDeg(const Vector3<T>& v0, double theta_deg) {
			return rotateYRad(v0, DEGREES_TO_RADIANS * theta_deg);
		}
		
		/** Rotates a 3D vector theta_rad radians in the XoY plane. */
		friend Vector3<T> rotateZRad(const Vector3<T>& v0, double theta_rad) {
			double c = cos(theta_rad);
			double s = sin(theta_rad);
			T x = (T)(v0.data[0] * c - v0.data[1] * s);
			T y = (T)(v0.data[1] * c + v0.data[0] * s);
			T z = v0.data[2];
			return Vector3<T>(x,y,z);
		}
		
		/** Rotates a 3D vector theta_deg degrees in the XoY plane. */
		friend Vector3<T> rotateZDeg(const Vector3<T>& v0, double theta_deg) {
			return rotateZRad(v0, DEGREES_TO_RADIANS * theta_deg);
		}
		
		/** Rotates a 3D vector theta_rad radians around a given axis. */
		friend Vector3<T> rotateRad(const Vector3<T>& v0, const Vector3<T>& axis, double theta_rad) {
			double c = cos(theta_rad);
			double s = sin(theta_rad);
			T ux = axis.data[0];
			T uy = axis.data[1];
			T uz = axis.data[2];
			T ux2 = ux * ux;
			T uy2 = uy * uy;
			T uz2 = uz * uz;
			T uxy = ux * uy;
			T uxz = ux * uz;
			T uyz = uy * uz;
			T x = (T)((ux2 + c * (1.0 - ux2)) * v0.data[0] + (uxy * (1.0 - c) - uz * s) * v0.data[1] + (uxz * (1.0 - c) + uy * s) * v0.data[2]);
			T y = (T)((uxy * (1.0 - c) + uz * s) * v0.data[0] + (uy2 + c * (1.0 - uy2)) * v0.data[1] + (uyz * (1.0 - c) - ux * s) * v0.data[2]);
			T z = (T)((uxz * (1.0 - c) - uy * s) * v0.data[0] + (uyz * (1.0 - c) + ux * s) * v0.data[1] + (uz2 + c * (1.0 - uz2)) * v0.data[2]);
			return Vector3<T>(x,y,z);
		}
		
		/** Rotates a 3D vector theta_deg degrees around a given axis. */
		friend Vector3<T> rotateDeg(const Vector3<T>& v0, const Vector3<T>& axis, double theta_deg){
			return rotateRad(v0, axis, DEGREES_TO_RADIANS * theta_deg);
		}
		
		/** Rotates a 3D vector positioned at center theta_rad radians around a given axis. */
		friend Vector3<T> rotateAtRad(const Vector3<T>& v0, const Vector3<T>& axis, double theta_rad, const Vector3<T>& center) {
			Vector3<T> v_new;
			v_new.set(v0);
			v_new -= center;
			v_new = rotateRad(v_new, axis, theta_rad);
			v_new += center;
			return v_new;
		}
		
		/** Rotates a 3D vector positioned at center theta_deg degrees around a given axis. */
		friend Vector3<T> rotateAtDeg(const Vector3<T>& v0, const Vector3<T>& axis, double theta_deg, const Vector3<T>& center){
			rotateAtRad(v0, axis, DEGREES_TO_RADIANS * theta_deg, center);
		}
    };

	template <class T>
	const Vector3<T> Vector3<T>::nx(1,0,0);

	template <class T>
	const Vector3<T> Vector3<T>::ny(0,1,0);

	template <class T>
	const Vector3<T> Vector3<T>::nz(0,0,1);

    //---<multiply by a factor on the left>---

    template<class V, class T, int N>
    inline const V operator*(double k, const Vector<V,T,N>& v) {
        V v_new;
        for_each_i( v_new.data[i] = v.data[i] * k; )
        return v_new;
    }
    template<class V, class T, int N>
    inline const V operator*(float k, const Vector<V,T,N>& v) {
        V v_new;
        for_each_i( v_new.data[i] = v.data[i] * k; )
        return v_new;
    }
    template<class V, class T, int N>
    inline const V operator*(int k, const Vector<V,T,N>& v) {
        V v_new;
        for_each_i( v_new.data[i] = v.data[i] * k; )
        return v_new;
    }

    //---<predefined>---

    /** 3D vector of double precision */
	typedef Vector3<double> Vector3d;

    /** 3D vector of single precision */
	typedef Vector3<float> Vector3f;
    
	/** 3D vector of integer precision */
	typedef Vector3<int> Vector3i;

    /** 2D vector of double precision */
	typedef Vector2<double> Vector2d;
    
	/** 2D vector of single precision */
	typedef Vector2<float> Vector2f;
    
	/** 2D vector of integer precision */
	typedef Vector2<int> Vector2i;
}

#endif // VECTOR_H
