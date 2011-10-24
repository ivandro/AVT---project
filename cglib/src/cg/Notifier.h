/// @cond
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

#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <fstream>
#include <stdexcept>
#include "DebugFile.h"
#include "Entity.h"
#include "LockableOrderedMap.h"
#include "State.h"

#define FOR_EACH_LISTENER(COMMAND)\
	try {\
		lock();\
		if(state.isEnabled()) {\
			for (tListenerIterator i = _listeners.begin(); i != _listeners.end(); i++) {\
				if((*i)->entity->state.isEnabled()) {\
					(*i)->listener->COMMAND;\
				}\
			}\
		}\
		unlock();\
	} catch(std::runtime_error& e) {\
		cg::DebugFile::instance()->writeException(e);\
		throw e;\
	}

#define DUMP_METHOD(CLASS)\
	void dump() {\
		std::ofstream& file = DebugFile::instance()->getOutputFileStream();\
		file << CLASS::instance()->state << " " << #CLASS << " (" << size() << ")" << std::endl;\
		for (tListenerIterator i = _listeners.begin(); i != _listeners.end(); i++) {\
			file << "    " << (*i)->entity->state << " " << (*i)->entity->getId() << std::endl;\
		}\
	}

namespace cg {

	/** cg::ListenerInfo<E> maintains information on a listener implementing interface E.
	 */
	template<class E>
	struct ListenerInfo {
	public:
		E* listener;
		Entity* entity;
		ListenerInfo(E* _listener, Entity* _entity) {
			listener = _listener;
			entity = _entity;
		}
		~ListenerInfo() {
		}
	};

	/** cg::Notifier<E> is an asbtract class maintaining a set of cg::Entity objects
	 *  implementing the callback interface <E>.
	 *  cg::Notifier<E> can be enabled/disabled.
	 *  Note: although cg::Notifier<E> allows for dynamic addition/removal of
	 *  listeners, adding/removing a listener while the callbacks are being
	 *  processed will put this command on a queue, that will only be executed
	 *  at the end of the callback iteration over all listeners.
	 *  It is usually a better design to create a 'manager' class that deals with 
	 *  the dynamic addition/removal of related entities. This manager class can be 
	 *  registered instead of its inner classes, and be an entry point for them.
	 */
	template <class E>
	class Notifier {
	private:
		ListenerInfo<E>* createListenerInfo(E* listener);

	protected:
		LockableOrderedMap<ListenerInfo<E> > _listeners;
		typedef typename LockableOrderedMap<ListenerInfo<E> >::iterator tListenerIterator;

	public:
		Notifier();
		virtual ~Notifier();

		State state;

		unsigned int size() const;
		bool exists(const std::string& id);
		E* get(const std::string& id);
		void addAtBeginning(E* listener);
		void addAtEnd(E* listener);
		void addBefore(E* listener, const std::string& entrypoint);
		void addAfter(E* listener, const std::string& entrypoint);
		void remove(const std::string& id);
		void removeAll();

		void lock();
		void unlock();
	};

    template<class E>
    Notifier<E>::Notifier() {
    }
    template<class E>
    Notifier<E>::~Notifier() {
		_listeners.unlock();
		_listeners.destroyAll();
    }
	template<class E>
    unsigned int Notifier<E>::size() const { 
		return _listeners.size();
	}
	template<class E>
	bool Notifier<E>::exists(const std::string& id) { 
		return _listeners.exists(id); 
	}
	template<class E>
	E* Notifier<E>::get(const std::string& id) { 
		ListenerInfo<E>* info = _listeners.get(id);
		if(info) {
			return info->listener;
		} else {
			return 0;
		}
	}
	template<class E> inline
	ListenerInfo<E>* Notifier<E>::createListenerInfo(E* listener) {
		Entity* entity = dynamic_cast<Entity*>(listener);
		if(entity == 0) {
			throw std::runtime_error("[cg::Notifier] listener is not subclass of cg::Entity.");
		} else {
			std::string id = entity->getId();
			return new ListenerInfo<E>(listener, entity);
		}		
	}
	template<class E>
	void Notifier<E>::addAtBeginning(E* listener) {
		ListenerInfo<E>* info = createListenerInfo(listener);
		_listeners.addAtBeginning(info->entity->getId(),info);
	}
	template<class E>
	void Notifier<E>::addAtEnd(E* listener) {
		ListenerInfo<E>* info = createListenerInfo(listener);
		_listeners.addAtEnd(info->entity->getId(),info);
	}
	template<class E>
	void Notifier<E>::addBefore(E* listener, const std::string& entrypoint) {
		ListenerInfo<E>* info = createListenerInfo(listener);
		_listeners.addBefore(info->entity->getId(),info,entrypoint);
	}
	template<class E>
	void Notifier<E>::addAfter(E* listener, const std::string& entrypoint) {
		ListenerInfo<E>* info = createListenerInfo(listener);
		_listeners.addAfter(info->entity->getId(),info,entrypoint);
	}
	template<class E>
	void Notifier<E>::remove(const std::string& id) {
		_listeners.destroy(id);
	}
	template<class E>
	void Notifier<E>::removeAll() {
		_listeners.destroyAll();
	}
	template<class E>
	void Notifier<E>::lock() {
		_listeners.lock();
	}
	template<class E>
	void Notifier<E>::unlock() {
		_listeners.unlock();
	}
}

#endif // NOTIFIER_H
/// @endcond
