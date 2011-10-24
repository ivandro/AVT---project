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

#include "Registry.h"

namespace cg {

    Registry* Registry::_instance = 0;

    Registry* Registry::instance() {
        if (_instance == 0) { 
			_instance = new Registry(); 
		}
        return _instance; 
	}
    Registry::Registry() {
	}
    Registry::~Registry() { 
		shutdown();
	}
    void Registry::cleanup() {
		delete _instance;
	}

	void Registry::init() {
		for (tEntityIterator i = _entities.begin(); i != _entities.end(); i++) {
			i->second->init(); 
		}
	}
	unsigned int Registry::size() const{
		return (unsigned int)_entities.size();
    }
	bool Registry::exists(const std::string& id) {
		return (_entities.count(id) != 0);
	}
	Entity* Registry::get(const std::string& id) {
		tEntityIterator i = _entities.find(id);
		if(i != _entities.end()) {
			return i->second;
		}
		return 0;
	}
	#define CONNECT_ENTITY(entity,NOTIFIER,LISTENER)\
		{ LISTENER* l = dynamic_cast<LISTENER*>(entity);\
		  if(l) { NOTIFIER::instance()->addAtEnd(l); }}

	inline
	void Registry::connectEntity(Entity* entity) {
		CONNECT_ENTITY(entity,KeyboardEventNotifier,IKeyboardEventListener)
		CONNECT_ENTITY(entity,MouseEventNotifier,IMouseEventListener)
		CONNECT_ENTITY(entity,ReshapeEventNotifier,IReshapeEventListener)
		CONNECT_ENTITY(entity,UpdateNotifier,IUpdateListener)
		CONNECT_ENTITY(entity,DebugNotifier,IDebugListener)
		CONNECT_ENTITY(entity,ViewNotifier,IViewListener)
	}
	void Registry::add(Entity* entity) {
		std::string id = entity->getId();
		std::pair<tEntityIterator,bool> result = _entities.insert(std::make_pair(id, entity));
		if(result.second == false) {
			throw std::runtime_error("[cg::Registry] entity '" + id + "' already exists.");
		} else {
			connectEntity(entity);
		}
	}

	#define DISCONNECT_ENTITY(entity,NOTIFIER,LISTENER)\
		{ LISTENER* l = dynamic_cast<LISTENER*>(entity);\
		  if(l) { NOTIFIER::instance()->remove(entity->getId()); }}

	inline
	void Registry::disconnectEntity(Entity* entity) {
		DISCONNECT_ENTITY(entity,KeyboardEventNotifier,IKeyboardEventListener)
		DISCONNECT_ENTITY(entity,MouseEventNotifier,IMouseEventListener)
		DISCONNECT_ENTITY(entity,ReshapeEventNotifier,IReshapeEventListener)
		DISCONNECT_ENTITY(entity,UpdateNotifier,IUpdateListener)
		DISCONNECT_ENTITY(entity,DebugNotifier,IDebugListener)
		DISCONNECT_ENTITY(entity,ViewNotifier,IViewListener)
	}
	void Registry::remove(const std::string& id) {
		tEntityIterator i = _entities.find(id);
		if(i != _entities.end()) {
			disconnectEntity(i->second);
			_entities.erase(id);
		}
	}
	void Registry::removeAll() {
		for (tEntityIterator i = _entities.begin(); i != _entities.end(); i++) {
			disconnectEntity(i->second);
		}
		_entities.clear();
	}
	void Registry::destroy(const std::string& id) {
		tEntityIterator i = _entities.find(id);
		if(i != _entities.end()) {
			Entity* entity = i->second;
			disconnectEntity(entity);
			delete entity;
			_entities.erase(id);
		}
	}
	void Registry::destroyAll() {
		for (tEntityIterator i = _entities.begin(); i != _entities.end(); i++) {
			Entity* entity = i->second;
			disconnectEntity(entity);
			delete entity;
		}
		_entities.clear();
	}

	#define DUMP_ENTITY(entity,LISTENER,tab)\
		{ LISTENER* l = dynamic_cast<LISTENER*>(entity);\
		  if(l) { file << tab << #LISTENER << std::endl; }}

	inline
	void Registry::dumpEntity(Entity* entity, std::ofstream& file) {
		entity->dump(file);
		file << std::endl;
		std::string tab = "    ";
		DUMP_ENTITY(entity,IKeyboardEventListener,tab)
		DUMP_ENTITY(entity,IMouseEventListener,tab)
		DUMP_ENTITY(entity,IReshapeEventListener,tab)
		DUMP_ENTITY(entity,IUpdateListener,tab)
		DUMP_ENTITY(entity,IDrawListener,tab)
		DUMP_ENTITY(entity,IDebugListener,tab)
		DUMP_ENTITY(entity,GroupDebug,tab)
		DUMP_ENTITY(entity,GroupDraw,tab)
		DUMP_ENTITY(entity,GroupUpdate,tab)
		DUMP_ENTITY(entity,GroupKeyboardEvent,tab)
		DUMP_ENTITY(entity,GroupMouseEvent,tab)
		DUMP_ENTITY(entity,GroupReshapeEvent,tab)
	}
	void Registry::dump() {
		std::ofstream& file = DebugFile::instance()->getOutputFileStream();
		file << "[Registry] (" << size() << ")" << std::endl;
		for (tEntityIterator i = _entities.begin(); i != _entities.end(); i++) {
			dumpEntity(i->second, file);
		}
	}
	void Registry::shutdown() {
		for (tEntityIterator i = _entities.begin(); i != _entities.end(); i++) {
			Entity* entity = i->second;
			delete entity;
		}
		_entities.clear();
	}
}