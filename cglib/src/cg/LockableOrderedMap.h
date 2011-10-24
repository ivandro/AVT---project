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

#ifndef LOCKABLE_ORDERED_MAP_H
#define LOCKABLE_ORDERED_MAP_H

#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>
#include <list>
#include "CommandQueue.h"

namespace cg {

	template <class T>
	class LockableOrderedMap {

	private:
		std::map<const std::string,T*> _names;
		typedef typename std::map<const std::string,T*>::iterator tNameIterator;
		
		std::list<T*> _elements;
		typedef typename std::list<T*>::iterator tElementIterator;

		bool _isLocked;
		CommandQueue<T> _commandQueue;
		void addPair(const std::string& id, T* element);

	public:
		LockableOrderedMap();
		~LockableOrderedMap();

		typedef tElementIterator iterator;
		tElementIterator begin();
		tElementIterator end();

		unsigned int size() const;
		bool exists(const std::string& id);
		T* get(const std::string& id);
		void addAtBeginning(const std::string& id, T* element);
		void addAtEnd(const std::string& id, T* element);
		void addBefore(const std::string& id, T* element, const std::string& entrypoint);
		void addAfter(const std::string& id, T* element, const std::string& entrypoint);
		void remove(const std::string& id);
		void removeAll();
		void destroy(const std::string& id);
		void destroyAll();

		void lock();
		void unlock();
	};

    template<class T>
    LockableOrderedMap<T>::LockableOrderedMap() {
		_isLocked = false;
    }
    template<class T>
    LockableOrderedMap<T>::~LockableOrderedMap() {
		_isLocked = false; 
		removeAll(); 
    }
    template<class T>
    typename LockableOrderedMap<T>::iterator LockableOrderedMap<T>::begin() {
		return _elements.begin();
	}
    template<class T>
    typename LockableOrderedMap<T>::iterator LockableOrderedMap<T>::end() {
		return _elements.end();
	}
	template<class T>
    unsigned int LockableOrderedMap<T>::size() const{
		return (unsigned int)_names.size();
    }
    template<class T>
    bool LockableOrderedMap<T>::exists(const std::string& id) {
		if(_names.count(id) == 0) {
			return _commandQueue.existsElement(id);
		} else {
			return true;
		}
    }
	template <class T>
	T* LockableOrderedMap<T>::get(const std::string& id) {
		tNameIterator i = _names.find(id);
		if(i == _names.end()) {
			return _commandQueue.getElement(id);
		} else {
			return i->second;
		}
	}
	template <class T> inline
	void LockableOrderedMap<T>::addPair(const std::string& id, T* element) {
		std::pair<tNameIterator,bool> result = _names.insert(std::make_pair(id,element));
		if(result.second == false) {
			throw std::runtime_error("[cg::LocakableOrderedMap] element '" + id + "' already exists.");
		}
	}
	template <class T>
	void LockableOrderedMap<T>::addAtBeginning(const std::string& id, T* element) {
		if(_isLocked) {
			_commandQueue.add(new AddCommandAtBeginning<T>(id,element));
			_commandQueue.addElement(id,element);
		} else {
			addPair(id,element);
			_elements.push_front(element);
		}
	}
	template <class T>
	void LockableOrderedMap<T>::addAtEnd(const std::string& id, T* element) {
		if(_isLocked) {
			_commandQueue.add(new AddCommandAtEnd<T>(id,element));
			_commandQueue.addElement(id,element);
		} else {
			addPair(id,element);
			_elements.push_back(element);
		}
	}
	template <class T>
	void LockableOrderedMap<T>::addBefore(const std::string& id, T* element, const std::string& entrypoint) {
		if(_isLocked) {
			_commandQueue.add(new AddCommandBefore<T>(id,element,entrypoint));
			_commandQueue.addElement(id,element);
		} else {
			addPair(id,element);
			tNameIterator ni = _names.find(id);
			tElementIterator ei = std::find(_elements.begin(),_elements.end(),ni->second);
			_elements.insert(ei,element);
		}
	}
	template <class T>
	void LockableOrderedMap<T>::addAfter(const std::string& id, T* element, const std::string& entrypoint) {
		if(_isLocked) {
			_commandQueue.add(new AddCommandAfter<T>(id,element,entrypoint));
			_commandQueue.addElement(id,element);
		} else {
			addPair(id,element);
			tNameIterator ni = _names.find(id);
			if(ni != _names.end()) {
				ni++;
				tElementIterator ei = std::find(_elements.begin(),_elements.end(),ni->second);
				_elements.insert(ei,element);
			}
		}
	}
	template <class T>
	void LockableOrderedMap<T>::remove(const std::string& id) {
		if(_isLocked) {
			_commandQueue.add(new RemoveCommand<T>(id));
		} else {
			tNameIterator i = _names.find(id);
			if(i != _names.end()) {
				tElementIterator j = std::find(_elements.begin(), _elements.end(), i->second);
				_elements.erase(j);
				_names.erase(id);
			}
		}
	}
	template <class T>
	void LockableOrderedMap<T>::removeAll() {
		if(_isLocked) {
			_commandQueue.add(new RemoveAllCommand<T>());
		} else {
			_elements.clear();
			_names.clear();
		}
	}
	template <class T>
	void LockableOrderedMap<T>::destroy(const std::string& id) {
		if(_isLocked) {
			_commandQueue.add(new DestroyCommand<T>(id));
		} else {
			tNameIterator i = _names.find(id);
			if(i != _names.end()) {
				tElementIterator j = std::find(_elements.begin(), _elements.end(), i->second);
				delete (*j);
				_elements.erase(j);
				_names.erase(id);
			}
		}
	}
	template <class T>
	void LockableOrderedMap<T>::destroyAll() {
		if(_isLocked) {
			_commandQueue.add(new DestroyAllCommand<T>());
		} else {
			for (tElementIterator i = _elements.begin(); i != _elements.end(); i++) {
				delete (*i);
			}
			_elements.clear();
			_names.clear();
		}
	}
	template <class T>
	void LockableOrderedMap<T>::lock() {
		_isLocked = true;
	}
	template <class T>
	void LockableOrderedMap<T>::unlock() {
		_isLocked = false;
		_commandQueue.execute(this);
	}
}

#endif // LOCKABLE_ORDERED_MAP_H
