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

#include "ShaderManager.h"

namespace cg {

    ShaderManager* ShaderManager::_instance = 0;

    ShaderManager* ShaderManager::instance() {
        if (_instance == 0) { 
			_instance = new ShaderManager(); 
		}
        return _instance; 
	}
    ShaderManager::ShaderManager() {
	}
    ShaderManager::~ShaderManager() { 
		destroyAll();
	}
    void ShaderManager::cleanup() {
		delete _instance;
	}

	static ShaderManager* instance(); 

	VertexShader *ShaderManager::createVertexShader(const std::string& name, const std::string& filename) {
		VertexShader *vs = new VertexShader(name);
		std::pair<tVertexShaderIterator,bool> result = _vertexShaders.insert(std::make_pair(name, vs));
		if(result.second == false) {
			throw std::runtime_error("[cg::ShaderManager] shader '" + name + "' already exists.");
			delete vs;
			return 0;
		} else {
			vs->loadAndCompile(filename);
			return vs;
		}
	}
	FragmentShader *ShaderManager::createFragmentShader(const std::string& name, const std::string& filename) {
		FragmentShader *fs = new FragmentShader(name);
		fs->loadAndCompile(filename);
		return fs;
	}
	GeometryShader *ShaderManager::createGeometryShader(const std::string& name, const std::string& filename) {
		GeometryShader *gs = new GeometryShader(name);
		gs->loadAndCompile(filename);
		return gs;
	}
	ShaderProgram *ShaderManager::createShaderProgram(const std::string& name) {
		ShaderProgram *program = new ShaderProgram(name);
		return program;
	}
	VertexShader *ShaderManager::getVertexShader(const std::string& name) {
		tVertexShaderIterator i = _vertexShaders.find(name);
		if(i != _vertexShaders.end()) {
			return i->second;
		}
		return 0;
	}
	FragmentShader *ShaderManager::getFragmentShader(const std::string& name) {
		tFragmentShaderIterator i = _fragmentShaders.find(name);
		if(i != _fragmentShaders.end()) {
			return i->second;
		}
		return 0;
	}
	GeometryShader *ShaderManager::getGeometryShader(const std::string& name) {
		tGeometryShaderIterator i = _geometryShaders.find(name);
		if(i != _geometryShaders.end()) {
			return i->second;
		}
		return 0;
	}
	ShaderProgram *ShaderManager::getShaderProgram(const std::string& name) {
		tShaderProgramIterator i = _programs.find(name);
		if(i != _programs.end()) {
			return i->second;
		}
		return 0;
	}
	void ShaderManager::destroyVertexShader(const std::string& name) {
		tVertexShaderIterator i = _vertexShaders.find(name);
		if(i != _vertexShaders.end()) {
			VertexShader* shader = i->second;
			delete shader;
			_vertexShaders.erase(name);
		}
	}
	void ShaderManager::destroyFragmentShader(const std::string& name) {
		tFragmentShaderIterator i = _fragmentShaders.find(name);
		if(i != _fragmentShaders.end()) {
			FragmentShader* shader = i->second;
			delete shader;
			_fragmentShaders.erase(name);
		}
	}
	void ShaderManager::destroyGeometryShader(const std::string& name) {
		tGeometryShaderIterator i = _geometryShaders.find(name);
		if(i != _geometryShaders.end()) {
			GeometryShader* shader = i->second;
			delete shader;
			_geometryShaders.erase(name);
		}
	}
	void ShaderManager::destroyShaderProgram(const std::string& name){
		tShaderProgramIterator i = _programs.find(name);
		if(i != _programs.end()) {
			ShaderProgram* program = i->second;
			delete program;
			_programs.erase(name);
		}
	}
	void ShaderManager::destroyAll() {
		for (tVertexShaderIterator i = _vertexShaders.begin(); i != _vertexShaders.end(); i++) {
			VertexShader* shader = i->second;
			delete shader;
		}
		_vertexShaders.clear();
		for (tFragmentShaderIterator i = _fragmentShaders.begin(); i != _fragmentShaders.end(); i++) {
			FragmentShader* shader = i->second;
			delete shader;
		}
		_fragmentShaders.clear();
		for (tGeometryShaderIterator i = _geometryShaders.begin(); i != _geometryShaders.end(); i++) {
			GeometryShader* shader = i->second;
			delete shader;
		}
		_geometryShaders.clear();
		for (tShaderProgramIterator i = _programs.begin(); i != _programs.end(); i++) {
			ShaderProgram* program = i->second;
			delete program;
		}
		_programs.clear();
	}
	void ShaderManager::dump() {
		std::ofstream& file = DebugFile::instance()->getOutputFileStream();
		file << "[ShaderManager]" << std::endl;
		file << "  [Vertex Shaders]" << std::endl;
		for (tVertexShaderIterator i = _vertexShaders.begin(); i != _vertexShaders.end(); i++) {
			i->second->dump(file);
		}
		file << "  [Fragment Shaders]" << std::endl;
		for (tFragmentShaderIterator i = _fragmentShaders.begin(); i != _fragmentShaders.end(); i++) {
			i->second->dump(file);
		}
		file << "  [Geometry Shader]" << std::endl;
		for (tGeometryShaderIterator i = _geometryShaders.begin(); i != _geometryShaders.end(); i++) {
			i->second->dump(file);
		}
		file << "  [Shader Programs]" << std::endl;
		for (tShaderProgramIterator i = _programs.begin(); i != _programs.end(); i++) {
			i->second->dump(file);
		}
	}
}