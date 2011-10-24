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

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <fstream>
#include <map>
#include "gl.h"
#include "Shader.h"

namespace cg {

	/** cg::ShaderManager is a factory of vertex, geometry and fragment shaders as well as
	 *  shader programs. Shaders are accessible everywhere through the singleton pattern and
	 *  as such can be shared and reused by different entities. 
	 */
	class ShaderManager {

	private:
		static ShaderManager* _instance; 
		ShaderManager();

		std::map<const std::string, VertexShader*> _vertexShaders;
		typedef std::map<const std::string, VertexShader*>::iterator tVertexShaderIterator;

		std::map<const std::string, FragmentShader*> _fragmentShaders;
		typedef std::map<const std::string, FragmentShader*>::iterator tFragmentShaderIterator;

		std::map<const std::string, GeometryShader*> _geometryShaders;
		typedef std::map<const std::string, GeometryShader*>::iterator tGeometryShaderIterator;

		std::map<const std::string, ShaderProgram*> _programs;
		typedef std::map<const std::string, ShaderProgram*>::iterator tShaderProgramIterator;

		void shutdown();

	public:
		virtual ~ShaderManager();
		void cleanup();
		
		/** Singleton instance.
		 *	\return Pointer to the singleton instance. 
		 */
		static ShaderManager* instance(); 

		/** Creates a new vertex shader.
		 *  \param name Unique name for the vertex shader.
		 *  \param filename GLSL filename with the vertex shader code.
		 *	\return Pointer to the newly created vertex shader or 0 if a vertex shader with the same name already created exists. 
		 */
		VertexShader   *createVertexShader(const std::string& name, const std::string& filename);

		/** Creates a new fragment shader.
		 *  \param name Unique name for the fragment shader.
		 *  \param filename GLSL filename with the fragment shader code.
		 *	\return Pointer to the newly created fragment shader or 0 if a fragment shader with the same name was already exists. 
		 */
		FragmentShader *createFragmentShader(const std::string& name, const std::string& filename);

		/** Creates a new geometry shader.
		 *  \param name Unique name for the geometry shader.
		 *  \param filename GLSL filename with the geometry shader code.
		 *	\return Pointer to the newly created geometry shader or 0 if a geometry shader with the same name was already exists. 
		 */
		GeometryShader *createGeometryShader(const std::string& name, const std::string& filename);

		/** Creates a new shader program.
		 *  \param name Unique name for the shader program.
		 *	\return Pointer to the newly created shader program or 0 if a shader program with the same name was already exists. 
		 */
		ShaderProgram  *createShaderProgram(const std::string& name);

		/** Returns a pointer to a previously created vertex shader.
		 *  \param name Vertex shader name given upon creation.
		 *  \return Pointer to the vertex shader registered with name or 0 if no vertex shader with this name exists.
		 */
		VertexShader   *getVertexShader(const std::string& name);

		/** Returns a pointer to a previously created fragment shader.
		 *  \param name Fragment shader name given upon creation.
		 *  \return Pointer to the fragment shader registered with name or 0 if no fragment shader with this name exists.
		 */
		FragmentShader *getFragmentShader(const std::string& name);

		/** Returns a pointer to a previously created geometry shader.
		 *  \param name Geometry shader name given upon creation.
		 *  \return Pointer to the geometry shader registered with name or 0 if no geometry shader with this name exists.
		 */
		GeometryShader *getGeometryShader(const std::string& name);

		/** Returns a pointer to a previously created shader program.
		 *  \param name Shader program name given upon creation.
		 *  \return Pointer to the shader program registered with name or 0 if no shader program with this name exists.
		 */
		ShaderProgram  *getShaderProgram(const std::string& name);

		/** Destroys a previously created vertex shader. If no vertex shader with this name exists, nothing is changed,
		 *  and no warning is given.
		 *  \param name Vertex shader name given upon creation.
		 */
		void destroyVertexShader(const std::string& name);

		/** Destroys a previously created fragment shader. If no fragment shader with this name exists, nothing is changed,
		 *  and no warning is given.
		 *  \param name Fragment shader name given upon creation.
		 */
		void destroyFragmentShader(const std::string& name);

		/** Destroys a previously created geometry shader. If no geometry shader with this name exists, nothing is changed,
		 *  and no warning is given.
		 *  \param name Geometry shader name given upon creation.
		 */
		void destroyGeometryShader(const std::string& name);

		/** Destroys a previously created shader program. If no shader program with this name exists, nothing is changed,
		 *  and no warning is given.
		 *  \param name Shader program name given upon creation.
		 */
		void destroyShaderProgram(const std::string& name);

		/** Destroys all shaders and shader programs.
		 */
		void destroyAll();

		/** Dumps to the debug file a list of all the shaders and shader programs created.
		 */
		void dump();
	};
}

#endif // SHADERMANAGER_H