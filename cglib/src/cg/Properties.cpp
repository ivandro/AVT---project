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

#include "Properties.h"

namespace cg {

	const char Properties::COMMENT = '#';

	SINGLETON_IMPLEMENTATION(Properties)

	void Properties::parseLine(const std::string& line) {
		std::string name, value, separator;
		std::istringstream iss(line);
		if(line.size() > 0) {
			iss >> name >> separator;
			if(name[0] == COMMENT) {
				return;
			}
			value = iss.str().substr((unsigned int)(iss.tellg()));
			if(separator == "=") {
				size_t start = value.find_first_not_of(" ");
				size_t end = value.find_last_not_of(" ");
				std::pair<tPropertyIterator,bool> result = 
					_properties.insert( std::make_pair(name,value.substr(start,end-start+1)) );
				if(result.second == 0) {
					throw std::runtime_error("[cg::Properties] property '" + name + "' already exists.");
				}
			}
		}
	}
	void Properties::load(const std::string& filename) {
		std::string line;
		std::ifstream file;
		file.open(filename.c_str());
		if(file.is_open()) {
			while (!file.eof()) {
				std::getline(file,line);
				parseLine(line);
			}
			file.close();
		} else {
			throw std::runtime_error("[cg::Properties] Cannot open file '" + filename + "'.");
		}
	}
	bool Properties::exists(const std::string& name) {
		tPropertyIterator i = _properties.find(name);
		return (i != _properties.end());
	}
	int Properties::getInt(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		int i;
		if(iss >> i) {
			return i;
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <int> (value '"+ s +"').");
		}
	}
	float Properties::getFloat(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		float f;
		if (iss >> f) {
			return f;
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <double> (value '"+ s +"').");
		}
 	}
	double Properties::getDouble(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		double d;
		if (iss >> d) {
			return d;
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <double> (value '"+ s +"').");
		}
 	}
	std::string Properties::getString(const std::string& name) {
		tPropertyIterator i = _properties.find(name);
		if( i != _properties.end() ) {
			return i->second;
		} else {
			throw std::runtime_error("[cg::Properties] unknown property '" + name + "'.");
		}
	}
	Vector2i Properties::getVector2i(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		int v0, v1;
		if(iss >> v0 >> v1) {
			return Vector2i(v0,v1);
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <Vector2i> (value '"+ s +"').");
		}
	}
	Vector2d Properties::getVector2d(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		double v0, v1;
		if(iss >> v0 >> v1) {
			return Vector2d(v0,v1);
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <Vector2d> (value '"+ s +"').");
		}
	}
	Vector3i Properties::getVector3i(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		int v0, v1, v2;
		if(iss >> v0 >> v1 >> v2) {
			return Vector3i(v0,v1,v2);
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <Vector3i> (value '"+ s +"').");
		}
	}
	Vector3d Properties::getVector3d(const std::string& name) {
		std::string s = getString(name);
		std::istringstream iss(s);
		double v0, v1, v2;
		if(iss >> v0 >> v1 >> v2) {
			return Vector3d(v0,v1,v2);
		} else {
			throw std::runtime_error("[cg::Properties] Cannot convert property '" + name + "' to <Vector3d> (value '"+ s +"').");
		}
	}
}