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

#ifndef REGISTRY_H
#define REGISTRY_H

#include <fstream>
#include <map>
#include <stdexcept>
#include "DebugFile.h"
#include "DebugNotifier.h"
#include "Entity.h"
#include "GroupDebug.h"
#include "GroupDraw.h"
#include "GroupKeyboardEvent.h"
#include "GroupMouseEvent.h"
#include "GroupReshapeEvent.h"
#include "GroupUpdate.h"
#include "IDebugListener.h"
#include "IDrawListener.h"
#include "IKeyboardEventListener.h"
#include "IMouseEventListener.h"
#include "IReshapeEventListener.h"
#include "IUpdateListener.h"
#include "IViewListener.h" 
#include "KeyboardEventNotifier.h"
#include "MouseEventNotifier.h"
#include "ReshapeEventNotifier.h"
#include "UpdateNotifier.h"
#include "ViewNotifier.h"

namespace cg {

	/** cg::Registry is a singleton that maintains a list of all cg::Entity of 
	 *  the application. When the cg::Registry::init method is invoked, all the
	 *  entities are called through the cg::Entity::init method, independently 
	 *  of being enabled or not.
	 */
	class Registry {

	private:
		static Registry* _instance; 
		Registry();

		std::map<const std::string, Entity*> _entities;
		typedef std::map<const std::string, Entity*>::iterator tEntityIterator;

		void connectEntity(Entity* entity);
		void disconnectEntity(Entity* entity);
		void dumpEntity(Entity* entity, std::ofstream& file);
		void shutdown();

	public:
		virtual ~Registry();
		void cleanup();
		
		/** Singleton instance.
		 *	\return		Pointer to the singleton instance. 
		 */
		static Registry* instance(); 
		
		void init();
		
		/** Returns the size of the registry, i.e., the number of registered entities. 
		 *	\return		The number of registered entities.
		 */
		unsigned int size() const;
		
		/** Checks if an entity is registered.
		 *	\param	id	The entity's identifier.
		 *	\return		True if the entity with identifier id exists in the Registry, false otherwise. 
		 */
		bool exists(const std::string& id);
		
		/** Get's a registered entity.
		 *	\param	id	The entity's identifier.
		 *	\return		The Entity with identifier id. If it does not exist, returns 0. 
		 */
		Entity* get(const std::string& id);
		
		/** Adds an entity to the Registry. 
		 *	\param	entity Entity to be added.
		 */
		void add(Entity* entity);
		
		/** Removes an entity from the Registry. 
		 *	\param	entity Entity to be removed.
		 */
		void remove(const std::string& id);
		
		/** Removes all entities from the Registry. 
		 */
		void removeAll();
		
		/** Removes an entity from the Registry and destroys it. 
		 *	\param	entity Entity to be destroyed.
		 */
		void destroy(const std::string& id);
		
		/** Removes all entities from the Registry and destroys them. 
		 */
		void destroyAll();
		
		/** Writes all entities in the Registry to the "log.txt" file. 
		 */
		void dump();
	};
}

#endif // REGISTRY_H