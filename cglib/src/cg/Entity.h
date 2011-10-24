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

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <fstream>
#include "State.h"

namespace cg {

	/** cg::Entity is the base class for all elements of the simulation.
	 *
	 *  A cg::Entity is identified by a string and can be turned on or off.
	 *  When turned off, all callbacks are disabled. 
	 *  All initialization should be performed in the cg::Entity::init method (rather
	 *  than in the constructor, as only then are OpenGL commands ready to be used.
	 */
	class Entity {

	protected:
		/** Unique string identifier for each cg::Entity.
		 */
		std::string _id;

	public:
		/** The state of the Entity (enabled/disabled). 
		 */
		State state;

		/** Creates an new Entity.
		 *	\param	id	The Entity's identifier.
		 *	\return		An enabled Entity with identifier id.
		 */
		Entity(const std::string& id) : _id(id) {}
		
		/** Destructor. 
		 */
		virtual ~Entity() {}

		/** Gets the Entity's id.
		 *	\return The Entity's unique identifier. 
		 */
		const std::string& getId() const { return _id; }
		
		/** Initializes the entity. Called when the Entity is created. 
		 */
		virtual void init() = 0;

		/** Writes the cg::Entity to a file.
		 *	\param	file The file output stream to which the entity is dumped.
		 */
		virtual void dump(std::ofstream& file) {
			file << state << " " << _id;
		}
	};
}

#endif // ENTITY_H
