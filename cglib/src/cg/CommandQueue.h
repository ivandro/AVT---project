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

#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <string>
#include <queue>
#include "LockableOrderedMap.h"

namespace cg {

	template<class T>
	class LockableOrderedMap;

	//---<CommandQueue>---

	template <class T>
	class Command {
	public:
		Command() {}
		virtual ~Command() {}
		virtual void execute(LockableOrderedMap<T>* activity_map) = 0;
	};

	template <class T>
	class CommandQueue {
	private:
		std::queue<Command<T>*> _commands;
		std::map<const std::string,T*> _newElements;
        typedef typename std::map<const std::string,T*>::iterator newElementItr;

	public:
		CommandQueue() {}
		~CommandQueue() { destroy(); }
		void add(Command<T>* command);
		void addElement(const std::string& id, T* element);
		bool existsElement(const std::string& id);
		T* getElement(const std::string& id);
		void execute(LockableOrderedMap<T>* activity_map);
		void destroy();
	};
	template <class T>
	void CommandQueue<T>::add(Command<T>* command) {
		_commands.push(command);
	}
	template <class T>
	void CommandQueue<T>::addElement(const std::string& id, T* element) {
		std::pair<newElementItr,bool> result = _newElements.insert( std::make_pair(id,element) );
		if(result.second == false) {
			throw std::invalid_argument("[cg::CommandQueue] element '" + id + "' already exists.");
		}
	}
	template <class T>
	bool CommandQueue<T>::existsElement(const std::string& id) {
		return (_newElements.count(id) != 0);
	}
	template <class T>
	T* CommandQueue<T>::getElement(const std::string& id) {
		newElementItr i = _newElements.find(id);
		if(i == _newElements.end()) {
			return 0;
		}
		return i->second;
	}
	template <class T>
	void CommandQueue<T>::execute(LockableOrderedMap<T>* lomap) {
		while(_commands.empty() == false) {
			Command<T>* c = _commands.front();
			c->execute(lomap);
			_commands.pop();
			delete c;
		}
		_newElements.clear();
	}
	template <class T>
	void CommandQueue<T>::destroy() {
		while(_commands.empty() == false) {
			Command<T>* c = _commands.front();
			_commands.pop();
			delete c;
		}
		_newElements.clear();
	}

	//---<Commands>---

	template <class T>
	class AddCommandAtBeginning : public Command<T> {
	private:
		std::string _id;
		T* _element;
	public:
		AddCommandAtBeginning(const std::string& id, T* element) {
			_id = id;
			_element = element;
		}
		~AddCommandAtBeginning() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->addAtBeginning(_id,_element);
		}
	};

	template <class T>
	class AddCommandAtEnd : public Command<T> {
	private:
		std::string _id;
		T* _element;
	public:
		AddCommandAtEnd(const std::string& id, T* element) {
			_id = id;
			_element = element;
		}
		~AddCommandAtEnd() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->addAtEnd(_id,_element);
		}
	};

	template <class T>
	class AddCommandBefore : public Command<T> {
	private:
		std::string _id;
		T* _element;
		std::string _entrypoint;
	public:
		AddCommandBefore(const std::string& id, T* element, const std::string& entrypoint) {
			_id = id;
			_element = element;
			_entrypoint = entrypoint;
		}
		~AddCommandBefore() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->addBefore(_id,_element,_entrypoint);
		}
	};

	template <class T>
	class AddCommandAfter : public Command<T> {
	private:
		std::string _id;
		T* _element;
		std::string _entrypoint;
	public:
		AddCommandAfter(const std::string& id, T* element, const std::string& entrypoint) {
			_id = id;
			_element = element;
			_entrypoint = entrypoint;
		}
		~AddCommandAfter() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->addAfter(_id,_element,_entrypoint);
		}
	};

	template <class T>
	class RemoveCommand : public Command<T> {
	private:
		std::string _id;
	public:
		RemoveCommand(const std::string& id) {
			_id = id;
		}
		~RemoveCommand() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->remove(_id);
		}
	};

	template <class T>
	class RemoveAllCommand : public Command<T> {
	public:
		RemoveAllCommand() {
		}
		~RemoveAllCommand() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->removeAll();
		}
	};

	template <class T>
	class DestroyCommand : public Command<T> {
	private:
		std::string _id;
	public:
		DestroyCommand(const std::string& id) {
			_id = id;
		}
		~DestroyCommand() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->destroy(_id);
		}
	};

	template <class T>
	class DestroyAllCommand : public Command<T> {
	public:
		DestroyAllCommand() {
		}
		~DestroyAllCommand() {
		}
		void execute(LockableOrderedMap<T>* lomap) {
			lomap->destroyAll();
		}
	};

}


#endif