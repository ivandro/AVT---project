#include "Group.h"

namespace cg {

	Group::Group(const std::string& id) : Entity(id) {
	}
	Group::~Group() {
		_entities.unlock();
		_entities.destroyAll();
	}
	unsigned int Group::size() {
		return _entities.size();
	}
	bool Group::exists(const std::string& id) {
		return _entities.exists(id);
	}
	Entity* Group::get(const std::string& id) {
		return _entities.get(id);
	}
	void Group::addAtBeginning(Entity* entity) {
		std::string id = entity->getId();
		_entities.addAtBeginning(id,entity);
	}
	void Group::addAtEnd(Entity* entity) {
		std::string id = entity->getId();
		_entities.addAtEnd(id,entity);
	}
	void Group::addBefore(Entity* entity,std::string& entrypoint) {
		std::string id = entity->getId();
		_entities.addBefore(id,entity,entrypoint);
	}
	void Group::addAfter(Entity* entity,std::string& entrypoint) {
		std::string id = entity->getId();
		_entities.addAfter(id,entity,entrypoint);
	}
	void Group::remove(const std::string& id) {
		_entities.remove(id);
	}
	void Group::removeAll() {
		_entities.removeAll();
	}
	void Group::destroy(const std::string& id) {
		_entities.destroy(id);
	}
	void Group::destroyAll() {
		_entities.destroyAll();
	}
	void Group::init() {
		preInit();
		createEntities();
		for(LockableOrderedMap<Entity>::iterator i = _entities.begin(); i != _entities.end(); i++) {
			(*i)->init();
		}
		postInit();
	}
	void Group::dump(std::ofstream& file) {
		file << state << " " << _id << " [Group of " << size() << "]";
		for(LockableOrderedMap<Entity>::iterator i = _entities.begin(); i != _entities.end(); i++) {
			file << std::endl;
			file << "    ";
			(*i)->dump(file);
		}
	}
	LockableOrderedMap<Entity>* Group::getEntities() {
		return &_entities; 
	}
	LockableOrderedMap<Entity>::iterator Group::begin() { 
		return _entities.begin(); 
	}
	LockableOrderedMap<Entity>::iterator Group::end() { 
		return _entities.end(); 
	}
}