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

#include "Shader.h"

namespace cg {

	//
	// Shader
	//

	Shader::Shader(const std::string& name) {
		_name = name;
		_shaderId = 0;
	}
	Shader::~Shader() {
		glDeleteShader(_shaderId);
	}
	const std::string& Shader::getName() {
		return _name;
	}
	const char* read(const std::string& filename) {
		return 0;
	}
	GLuint Shader::getOpenglId() {
		return _shaderId;
	}
	// TODO: Change to pure c++
	const GLchar* Shader::read(const char *fileName) {
		char* text;
    
		if (fileName != 0) {
			FILE *file;
			fopen_s(&file, fileName, "rt");
        
			if (file != 0) {
				fseek(file, 0, SEEK_END);
				int count = ftell(file);
				rewind(file);
            
				if (count > 0) {
					text = (char*)malloc(sizeof(char) * (count + 1));
					count = fread(text, sizeof(char), count, file);
					text[count] = '\0';
				}
				fclose(file);
			}
		}
		return text;
	}
	bool Shader::loadAndCompile(const std::string& filename) {
		const GLchar* text = read(filename.c_str());
		assert(text != 0);
		glShaderSource(_shaderId, 1, &text, 0);
		glCompileShader(_shaderId);
		GLint compiled;
		glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compiled);
		GLint length;
		GLchar *log;
		glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &length);
		log = (GLchar*) malloc(length);
		glGetShaderInfoLog(_shaderId, length, &length, log);
		std::cerr << "[" << filename << "] ";
		if(length == 0) {
			std::cerr << "ok." << std::endl;
		} else {
			std::cerr << std::endl << log;
		}
		free(log);
		return (compiled != 0);
	}
	void Shader::attachToProgram(GLuint programId) {
		glAttachShader(programId,_shaderId);
	}
	void Shader::detachFromProgram(GLuint programId) {
		glDetachShader(programId,_shaderId);
	}
	void Shader::dump(std::ofstream& file) {
		// TODO
		file << "    " << _name << std::endl;
	}

	//
	// VertexShader
	//

	VertexShader::VertexShader(const std::string& name) : Shader(name) {
		if(GLEW_ARB_vertex_program) {
			_shaderId = glCreateShader(GL_VERTEX_SHADER);
			assert(_shaderId != 0);
		} else {
			std::cerr << "Vertex program not supported." << std::endl;
		}
	}
	VertexShader::~VertexShader() {
	}

	//
	// FragmentShader
	//

	FragmentShader::FragmentShader(const std::string& name) : Shader(name) {
		if(GLEW_ARB_fragment_program) {
			_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
			assert(_shaderId != 0);
		} else {
			std::cerr << "Fragment program not supported." << std::endl;
		}
	}
	FragmentShader::~FragmentShader() {
	}

	//
	// GeometryShader
	//

	GeometryShader::GeometryShader(const std::string& name) : Shader(name) {
		if(GLEW_ARB_geometry_shader4) {
			_shaderId = glCreateShader(GL_GEOMETRY_SHADER);
			assert(_shaderId != 0);
			_inType = GL_TRIANGLES;			// set a default value
			_outType = GL_TRIANGLE_STRIP;	// set a default value
		} else {
			std::cerr << "Geometry shader not supported." << std::endl;
		}	
	}
	GeometryShader::~GeometryShader() {
	}
	void GeometryShader::setTypes(GLenum inType, GLenum outType) {
		_inType = inType;
		_outType = outType;
	}
	void GeometryShader::attachToProgram(GLuint programId) {
		glAttachShader(programId,_shaderId);
		glProgramParameteriEXT(programId, GL_GEOMETRY_INPUT_TYPE_EXT, _inType);
		if(checkOpenGLError()) { std::cerr << "GL_GEOMETRY_INPUT_TYPE_EXT" << std::endl; }
		glProgramParameteriEXT(programId, GL_GEOMETRY_OUTPUT_TYPE_EXT, _outType);		
		if(checkOpenGLError()) { std::cerr << "GL_GEOMETRY_OUTPUT_TYPE_EXT" << std::endl; }
		GLint max_outv;
		glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT,&max_outv);
		glProgramParameteriEXT(programId,GL_GEOMETRY_VERTICES_OUT_EXT,max_outv);
	}

	//
	// ShaderProgram
	//

	ShaderProgram::ShaderProgram(const std::string& name) {
		_name = name;
		_programId = glCreateProgram();
		assert(_programId != 0);
	}
	ShaderProgram::~ShaderProgram() {
		if(_programId != 0) {
			glDeleteProgram(_programId);
		}
	}
	const std::string& ShaderProgram::getName() {
		return _name;
	}
	GLuint ShaderProgram::getOpenglId() {
		return _programId;
	}

	VertexShader *ShaderProgram::getVertexShader() {
		return _vertexShader;
	}
	void ShaderProgram::attachVertexShader(VertexShader *vs) {
		_vertexShader = vs;
		_vertexShader->attachToProgram(_programId);
	}
	void ShaderProgram::detachVertexShader() {
		_vertexShader->detachFromProgram(_programId);
		_vertexShader = 0;
	}

	FragmentShader *ShaderProgram::getFragmentShader() {
		return _fragmentShader;
	}
	void ShaderProgram::attachFragmentShader(FragmentShader *fs) {
		_fragmentShader = fs;
		_fragmentShader->attachToProgram(_programId);
	}
	void ShaderProgram::detachFragmentShader() {
		_fragmentShader->detachFromProgram(_programId);
		_fragmentShader = 0;
	}
		
	GeometryShader *ShaderProgram::getGeometryShader() {
		return _geometryShader;
	}
	void ShaderProgram::attachGeometryShader(GeometryShader *gs) {
		_geometryShader = gs;
		_geometryShader->attachToProgram(_programId);
	}
	void ShaderProgram::detachGeometryShader() {
		_geometryShader->detachFromProgram(_programId);
		_geometryShader = 0;
	}

	void ShaderProgram::link() {
		glLinkProgram(_programId);
		GLint linked;
		glGetProgramiv(_programId, GL_LINK_STATUS, &linked);
		if(linked == 0) {
			GLint length;
			GLchar *log;
			glGetShaderiv(_programId,GL_INFO_LOG_LENGTH,&length);
			log = (GLchar*) malloc(length);
			glGetProgramInfoLog(_programId,length,&length,log);
			std::cerr << "[LINK] " << std::endl << log << std::endl;
			free(log);
		}
	}
	void ShaderProgram::bind() {
		glUseProgram(_programId);
	}
	void ShaderProgram::unbind() {
		glUseProgram(0);
	}
	void ShaderProgram::dump(std::ofstream& file) {
		// TODO
		file << "    " << _name << std::endl;
	}
}