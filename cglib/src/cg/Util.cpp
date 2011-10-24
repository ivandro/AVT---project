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

#include "Util.h"

namespace cg {

    SINGLETON_IMPLEMENTATION(Util)

    void Util::drawBitmapString(std::string s, GLdouble x, GLdouble y) {
        glRasterPos2d(x, y);
		std::string::iterator iend = s.end();
        for (std::string::iterator i = s.begin(); i != iend; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *i);
        }
    }
    void Util::drawBitmapStringVector(std::vector<std::string> s, GLdouble x, GLdouble y, GLdouble delta) {
        std::vector<std::string>::iterator iend = s.end();
        for(std::vector<std::string>::iterator i = s.begin(); i != iend; i++) {
            drawBitmapString((*i),x,y);
            y += delta;
        }
    }
    unsigned long Util::getSystemTime() {
        struct timeb current_time;
        ftime(&current_time);
        return (unsigned long)((current_time.time * 1000) + current_time.millitm);
    }
    void Util::worldToScreenCoordinates(GLdouble wx, GLdouble wy,GLdouble wz, GLdouble *sx, GLdouble *sy, GLdouble *sz) {
		GLint viewport[4];
		GLdouble modelview[16], projection[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluProject(wx, wy, wz, modelview, projection, viewport, sx, sy, sz);
    }
    void Util::screenToWorldCoordinates(GLdouble sx, GLdouble sy, GLdouble sz, GLdouble *wx, GLdouble *wy,GLdouble *wz) {
        GLdouble modelview[16], projection[16];
        GLint viewport[4];
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluUnProject(sx, sy, sz, modelview, projection, viewport, wx, wy, wz);
    }
	bool Util::isPointInPolygon(const Vector2d& point, std::vector<Vector2d>& polygon) {
		bool inside = false;
		double x = point[0];
		double y = point[1];
		std::vector<Vector2d>::iterator i, j;
		i = polygon.begin();
		j = --polygon.end();
		while(i != polygon.end()) {
			Vector2d vi = (*i);
			double xi = vi[0];
			double yi = vi[1];
			Vector2d vj = (*j);
			double xj = vj[0];
			double yj = vj[1];
			if (   ( ((yi <= y) && (y < yj)) || ((yj <= y) && (y < yi)) ) 
				&& (x < ((xj - xi) * (y - yi) / (yj - yi) + xi)) ) {
				inside = !inside;
			}
			j = i;
			i++;
		}
		return inside;
    }
	// Calcula a distância entre as projecções [minA, maxA] e [minB, maxB]
	// A distância será negativa caso os intervalos se intersectem.
	inline
	double Util::projectionDistance(double minA, double maxA, double minB, double maxB) {
		if (minA < minB) {
			return minB - maxA;
		} else {
			return minA - maxB;
		}
	}
	bool Util::isAABBoxCollision(const Vector2d& bottomleft0, const Vector2d& topright0, 
								 const Vector2d& bottomleft1, const Vector2d& topright1) {
		return( projectionDistance(bottomleft0[0],topright0[0],bottomleft1[0],topright1[0]) <= 0
			 && projectionDistance(bottomleft0[1],topright0[1],bottomleft1[1],topright1[1]) <= 0 );
	}
}
