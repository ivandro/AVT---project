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

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sys/timeb.h>
#include <vector>
#include "gl.h"
#include "Singleton.h"
#include "Vector.h"

namespace cg {

	/** cg::Util is a singleton providing a set of utility methods.
	 */
    class Util {

	SINGLETON_HEADER(Util)

	private:
		double projectionDistance(double minA, double maxA, double minB, double maxB);

    public:
        /** Draws a given string on screen positioning it at the given OpenGL coordinates. 
		 *	\param	s	The string to be drawn.
		 *	\param	x	The OpenGL x coordinate.
		 *	\param	y	The OpenGL y coordinate.
		 */
		void drawBitmapString(std::string s, GLdouble x, GLdouble y);
        
		/** Draws all strings in the given vector on screen, positioning the first string 
		 *	at the given OpenGL coordinates. Every next string will be delta values 
		 *	vertically distant from the previous one.
		 *	\param	s		The vector containing the strings to be drawn.
		 *	\param	x		The OpenGL x coordinate.
		 *	\param	y		The OpenGL y coordinate.
		 *	\param	delta	The value separating each string (-10 by default).
		 */
		void drawBitmapStringVector(std::vector<std::string> s, GLdouble x, GLdouble y, GLdouble delta = -10);
        
		/** Gets the current system time in milliseconds. 
		 *	\return		The current system time.
		 */
		unsigned long getSystemTime();
        
		/** Transforms world (OpenGL) coordinates into screen (window) coordinates. 
		 *	The computed values will be stored in sx, sy and sz. 
		 *	\param	wx		The OpenGL x coordinate.
		 *	\param	wy		The OpenGL y coordinate.
		 *	\param	wz		The OpenGL z coordinate.
		 *	\param	*sx		A GLDouble to store the window's x coordinate.
		 *	\param	*sy		A GLDouble to store the window's y coordinate.
		 *	\param	*sz		A GLDouble to store the window's z coordinate.
		 */
		void worldToScreenCoordinates(GLdouble wx, GLdouble wy, GLdouble wz, GLdouble *sx, GLdouble *sy, GLdouble *sz);
        
		/** Transforms screen (window) coordinates into world (OpenGL) coordinates. 
		 *	The computed values will be stored in wx, wy and wz. 
		 *	\param	sx		The window's x coordinate.
		 *	\param	sy		The window's y coordinate.
		 *	\param	sz		The window's z coordinate.
		 *	\param	*wx		A GLDouble to store the OpenGL x coordinate.
		 *	\param	*wy		A GLDouble to store the OpenGL y coordinate.
		 *	\param	*wz		A GLDouble to store the OpenGL z coordinate.
		 */
		void screenToWorldCoordinates(GLdouble sx, GLdouble sy, GLdouble sz, GLdouble *wx, GLdouble *wy, GLdouble *wz);
		
		/** Checks if a point is inside a polygon.
		 *	\param	point		A 2D vector representing the point.
		 *	\param	polygon		A vector of 2D vectors representing the polygon.
		 *	\return				True if the point is inside the polygon, false otherwise. 
		 */
		
		bool isPointInPolygon(const Vector2d& point, std::vector<Vector2d>& polygon);
		/** Checks if two boxes are colliding.
		 *	\param	bottomleft0		The bottom left corner of the first box.
		 *	\param	topright0		The top right corner of the first box.
		 *	\param	bottomleft1		The bottom left corner of the second box.
		 *	\param	topright1		The top right corner of the second box.
		 *	\return					True if the boxes are colliding, false otherwise. 
		 */
		bool isAABBoxCollision(const Vector2d& bottomleft0, const Vector2d& topright0, 
							   const Vector2d& bottomleft1, const Vector2d& topright1);
    };

}

#endif // UTIL_H
