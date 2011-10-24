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
// Copyright 2009 Carlos Martinho

#ifndef GL_H
#define GL_H

#include <iostream>

#include <GL/glew.h>

//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
#include <GL/glut.h>
//#endif

namespace cg {

	static bool checkOpenGLInfo(const bool check_extensions) {

		// OpenGL
		std::cerr << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << std::endl;
		std::cerr << "OpenGL v" << glGetString(GL_VERSION) << std::endl;
		std::cerr << "GLSL v" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		if(check_extensions) {
			std::cerr << glGetString(GL_EXTENSIONS) << std::endl;
		}

		// GLU
		std::cerr << "GLU v" << gluGetString(GLU_VERSION) << std::endl;
		if(check_extensions) {
			std::cerr << gluGetString(GL_EXTENSIONS) << std::endl;
		}

		// CGlib
		std::cerr << "CGlib 1.5.1" << std::endl;

		std::cerr << std::endl;
		return true;
	}

	static bool checkOpenGLError() {
		bool isError = false;
		GLenum errCode;
		const GLubyte *errString;
		while ((errCode = glGetError()) != GL_NO_ERROR) {
			isError = true;
			errString = gluErrorString(errCode);
			std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
		}
		return isError;
	}
}

#endif // GL_H