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

#ifndef GROUP_H
#define GROUP_H

#include <fstream>
#include <stdexcept>
#include <string>
#include "DebugFile.h"
#include "Entity.h"
#include "LockableOrderedMap.h"

#define FOR_EACH_ENTITY(COMMAND,INTERFACE)\
	try {\
		LockableOrderedMap<Entity>* lomap = getEntities();\
		lomap->lock();\
		LockableOrderedMap<Entity>::iterator iend = end();\
		for (LockableOrderedMap<Entity>::iterator i = begin(); i != iend; i++) {\
			if((*i)->state.isEnabled()) {\
				INTERFACE* obj = dynamic_cast<INTERFACE*>(*i);\
				obj->COMMAND; }}\
		lomap->unlock();\
	} catch(std::runtime_error& e) {\
		DebugFile::instance()->writeException(e);\
		throw e;\
	}

#define IGETENTITIES_IMPLEMENTATION\
	virtual LockableOrderedMap<Entity>* getEntities() {\
		Group* group = (Group*)dynamic_cast<Group*>(this);\
		return group->getEntities(); }\
	virtual LockableOrderedMap<Entity>::iterator begin() {\
		Group* group = (Group*)dynamic_cast<Group*>(this);\
		return group->begin(); }\
	virtual LockableOrderedMap<Entity>::iterator end() {\
		Group* group = (Group*)dynamic_cast<Group*>(this);\
		return group->end(); }

namespace cg {

	class IGetEntities {
    public:
        virtual LockableOrderedMap<Entity>* getEntities() = 0;
		virtual LockableOrderedMap<Entity>::iterator begin() = 0;
		virtual LockableOrderedMap<Entity>::iterator end() = 0;
    };

	/** cg::Group is an entity that contains other entities.
	 *
	 *  cg::Group can implement the same interfaces as any entity plus the
	 *  specific group classes that automatically distribute events
	 *  to the inner entities.
	 *  Note that all methods dealing with the contained entites are
	 *  protected, and can only be called from inside the subclass.
	 */
	class Group : public Entity/*, public IGetEntities*/ {
	protected:
		LockableOrderedMap<Entity> _entities;

	public:
		/** Creates a new Group. 
		 *	\param	id	The Group's unique identifier.
		 */
		Group(const std::string& id);

		/** Destructor. 
		 */
		virtual ~Group();
		
		/** Group inicialization.
		 *  Pre-inicializes the group [cg::Group::preInit], creates the 
		 *	group's entities [cg::Group::createEntities], initializes each 
		 *	entity [cg::Entity::init], and, finally, post-initializes the 
		 *	group [cg::Group::postInit].
		 */
		void init();
		
		/** Writes the Group structure to a file. 
		 *	\param file The output file stream to which the structure will be written.
		 */
		virtual void dump(std::ofstream& file);

		/** Pointer to all entities within the Group.
		 *	\return A pointer to all entities inside the group. 
		 */
		LockableOrderedMap<Entity>* getEntities();
		
		/** Pointer to the beginning of the Group.
		 *	\return An iterator pointing to the beginning of the group. 
		 */
		LockableOrderedMap<Entity>::iterator begin();
		
		/** Pointer to the end of the Group.
		 *	\return An iterator pointing to the end of the group. 
		 */
		LockableOrderedMap<Entity>::iterator end();

		/** Returns the Group's size, i.e. the number of entities in the Group.
		 *	\returns The number of entities in the Group. 
		 */
		unsigned int size();
		
		/** Verifies if an entity belongs to the Group.
		 *	\param	id	The entity's identifier.
		 *	\return		True if the Group has an entity with identifier id, false otherwise. 
		 */
		bool exists(const std::string& id);
		
		/** Get's an entity from the Group.
		 *	\param	id	The entity's identifier.
		 *	\return		The entity with identifier id. 
		 */
		Entity *get(const std::string& id);
		
		/** Adds an entity at the beginning of the group. 
		 *	\param	entity	The entity to be added.
		 */
		void addAtBeginning(Entity* entity);
		
		/** Adds an entity at the end of the group. 
		 *	\param	entity	The entity to be added.
		 */
		void addAtEnd(Entity* entity);
		
		/** Adds an entity before an entry point. 
		 *	\param	entity		The entity to be added.
		 *	\param	entrypoint	The id of the entity representing the entry point.
		 */
		void addBefore(Entity* entity, std::string& entrypoint);
		
		/** Adds an entity after an entry point. 
		 *	\param	entity		The entity to be added.
		 *	\param	entrypoint	The id of the entity representing the entry point.
		 */
		void addAfter(Entity* entity, std::string& entrypoint);
		
		/** Removes an entity from the group. 
		 *	\param	id	The id of the entity to be removed.
		 */
		void remove(const std::string& id);
		
		/** Removes all entities from the group. 
		 */
		void removeAll();
		
		/** Destroys an Entity in the Group. 
		 *	\param	id	The id of the entity to be destroyed.
		 */
		void destroy(const std::string& id);
		
		/** Destroys all Entity of the Group. 
		 */
		void destroyAll();

		/** Creates the Group's entities. 
		*/
		virtual void createEntities() {}
		
		/** Pre-initialization of the group. Executed before cg::Group::createEntities 
		 *	and before each entitie's cg::Entity::init. 
		 */
		virtual void preInit() {}
		
		/** Post-initialization of the group. Executed after cg::Group::createEntities 
		 *	and after each entitie's cg::Entity::init. 
		 */
		virtual void postInit() {}
	};
}

#endif // GROUP_H
