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
// Copyright 2010 Carlos Martinho

#ifndef SHADER_H
#define SHADER_H

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include "gl.h"
#include "DebugFile.h"

namespace cg {

	class Shader {
	public:
		/** Creates a new shader
		 *  \param name name to identifiy the shader.
		 */
		Shader(const std::string& name);

		/** Destructor
		 */
		virtual ~Shader();

		/** Returns the name given upon creation.
		 *  \return shader name.
		 */
		const std::string& getName();

		/** Returns the OpenGL index given upon creation.
		 *  \return OpenGL index.
		 */
		GLuint getOpenglId();

		/** Loads and compiles the GLSL code. Compilation errors are sent to std::cerr.
		 *  \param file with the GLSL code.
		 *  \return true if no error occured, false otherwise.
		 */		
		bool loadAndCompile(const std::string& filename);

		/** Attaches the shader to the shader program.
		 *  \param programId OpenGL index of the program.
		 */
		virtual void attachToProgram(GLuint programId);

		/** Detaches the shader from the shader program.
		 *  \param programId OpenGL index of the program.
		 */
		virtual void detachFromProgram(GLuint programId);

		/** Dumps shader information to the output stream for debug purposes.
		 *  \param file Output file stream.
		 */
		virtual void dump(std::ofstream& file);

	protected:
		/** Name given to the shader upon creation.
		 */
		std::string _name;

		/** OpenGL index of the shader, automatically created on creation.
		 */
		GLuint _shaderId;

		/** Converts the content of a file to an array of chars.
		 *  \param filename Name of the file with the shader GLSL code.
		 */
		const GLchar* read(const char* filename);
	};

	class VertexShader : public Shader {
	public:
		/** Creates a new vertex shader.
		 *  \param name Unique name of the vertex shader.
		 */
		VertexShader(const std::string& name);

		/** Destructor.
		 */
		virtual ~VertexShader();
	};

	class FragmentShader : public Shader {
	public:
		/** Creates a new fragment shader.
		 *  \param name Unique name of the fragment shader.
		 */
		FragmentShader(const std::string& name);

		/** Destructor.
		 */
		virtual ~FragmentShader();
	};

	class GeometryShader : public Shader {
	public:
		/** Creates a new geometry shader.
		 *  \param name Unique name of the geometry shader.
		 */
		GeometryShader(const std::string& name);

		/** Destructor.
		 */
		virtual ~GeometryShader();

		/** Sets input and output types of the geometry shaders. These will be specified to the shader program
		 *  when the geometry shader is added to the program.
		 *  \param inType Input type to the geometry shader (default is GL_TRIANGLES).
		 *  \param outType Output type of the geometry shader (default is GL_TRIANGLE_STRIP). 
		 */
		void setTypes(GLenum inType, GLenum outType);

		/** Attaches the geometry shader to a sahder program. The input and output types specified using
		 *  setTypes are specified to the shader program. By default the input type is GL_TRIANGLES and
		 *  output type is GL_TRIANGLE_STRIP.
		 */
		void attachToProgram(GLuint programId);

	private:
		GLenum _inType, _outType;
	};

	class ShaderProgram {
	public:
		/** Creates a shader program.
		 *  \param name Unique name of the shader program.
		 */
		ShaderProgram(const std::string& name);

		/** Desctructor. 
		 */
		virtual ~ShaderProgram();

		/** Returns the unique name of the shader program given upon creation.
		 *  \return Unique name of the shader program.
		 */
		const std::string& getName();

		/** Returns the OpenGL index of the shader program.
		 *  \return Unique OpenGL index.
		 */
		GLuint getOpenglId();

		/** Returns the vertex shader currently associated with the shader program.
		 *  \return Pointer to the vertex shader.
		 */
		VertexShader *getVertexShader();

		/** Attaches a vertex shader to the program.
		 *  \param vs Vertex shader to attach.
		 */
		void attachVertexShader(VertexShader *vs);

		/** Detaches the current vertex shader from the program.
		 */
		void detachVertexShader();
		
		/** Returns the fragment shader currently associated with the shader program.
		 *  \return Pointer to the fragment shader.
		 */
		FragmentShader *getFragmentShader();

		/** Attaches a fragment shader to the program.
		 *  \param fs Fragment shader to attach.
		 */
		void attachFragmentShader(FragmentShader *fs);

		/** Detaches the current fragment shader from the program.
		 */
		void detachFragmentShader();
		
		/** Returns the geometry shader currently associated with the shader program.
		 *  \return Pointer to the geometry shader.
		 */
		GeometryShader *getGeometryShader();

		/** Attaches a geometry shader to the program.
		 *  \param gs Geometry shader to attach.
		 */
		void attachGeometryShader(GeometryShader *gs);

		/** Detaches the current geometry shader from the program.
		 */
		void detachGeometryShader();

		/** Links the shader program.
		 */
		void link();

		/** Binds the shader program. Subsequent draw commands will use the shader.
		 */
		void bind();

		/** Unbinds the shader program. Subsequent draw commands will use the fixed pipeline.
		 */
		void unbind();

		/** Dumps shader program information to a file for debug purposes.
		 *  \param file Output file stream.
		 */
		void dump(std::ofstream& file);

	private:
		std::string _name;
		GLuint _programId;
		VertexShader *_vertexShader;
		FragmentShader *_fragmentShader;
		GeometryShader *_geometryShader;
	};
}

#endif