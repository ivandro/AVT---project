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

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Singleton.h"
#include "Vector.h"

namespace cg {

	/** cg::Properties is a singleton that maintains pairs (property,value) imported from 
	 *  a text file. 
	 *  The file format is as follows. Each property is written on a different line.
	 *  The format is [name] = [value], where name does not contain any white character.
	 *  The value field is read from the separator '=' to the end of line, and as such
	 *  can contain white characters.
	 *  Only a set of values are supported for direct type convertion. 
	 *  For other types, use the cg::Properties::getString method to obtain the value as 
	 *  a string and parse it.
	 *  Lines which first non-blank character is a '#' are comments.
	 */
	class Properties {

	SINGLETON_HEADER(Properties)

	private:
		static const char COMMENT;
		std::map<const std::string,const std::string> _properties;
		typedef std::map<const std::string,const std::string>::iterator tPropertyIterator;
		void parseLine(const std::string& line);

	public:
		/** Loads a file containing property values to be used by the application. 
		 *	\param	filename	The properties file.
		 */
		void load(const std::string& filename);
		
		/** Checks if a property exists in the property file.
		 *	\param	name	The property's name.
		 *	\return			True if the property exists, false otherwise. 
		 */
		bool exists(const std::string& name);

		/** Returns a property value with integer precision.
		 *	\param	name	The property's name.
		 *	\return			The value as an int.
		 */
		int getInt(const std::string& name);
		
		/** Returns a property value with single precision.
		 *	\param	name	The property's name.
		 *	\return			The value as a float.
		 */
		float getFloat(const std::string& name);
		
		/** Returns a property value with double precision.
		 *	\param	name	The property's name.
		 *	\return			The value as a double.
		 */
		double getDouble(const std::string& name);
		
		/** Returns a property value as a string.
		 *	\param	name	The property's name.
		 *	\return			The value as a string.
		 */
		std::string getString(const std::string& name);
		
		/** Returns a property value as a 2-dimensional vector of double precision. 
		 *	\param	name	The property's name.
		 *	\return			The value as a 2D vector of double precision.
		 */
		Vector2d getVector2d(const std::string& name);
		
		/** Returns a property value as a 2-dimensional vector of integer precision. 
		 *	\param	name	The property's name.
		 *	\return			The value as a 2D vector of integer precision.
		 */
		Vector2i getVector2i(const std::string& name);
		
		/** Returns a property value as a 3-dimensional vector of double precision. 
		 *	\param	name	The property's name.
		 *	\return			The value as a 3D vector of double precision.
		 */
		Vector3d getVector3d(const std::string& name);
		
		/** Returns a property value as a 3-dimensional vector of integer precision. 
		 *	\param	name	The property's name.
		 *	\return			The value as a 3D vector of integer precision.
		 */
		Vector3i getVector3i(const std::string& name);
	};
}

#endif // PROPERTIES_H