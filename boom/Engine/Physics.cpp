// (c) Simone Guggiari 2019
#include "Physics.h"


namespace sxg::engine {

	void Physics::update() {
		set<pair<GameObject*, GameObject*>> frameCollisions;

		for (size_t i = 0; i < _allColliders.size(); ++i) {
			for (size_t j = i + 1; j < _allColliders.size(); ++j) {
				//if collision, call back on both
				if (_allColliders[i]->intersects(*_allColliders[j])) {
					GameObject* goA = &_allColliders[i]->gameobject();
					GameObject* goB = &_allColliders[j]->gameobject();
					frameCollisions.insert({ goA, goB });
				}
			}
		}
		
		//check diff between previous and current collisions
		set<pair<GameObject*, GameObject*>> collisionEnter, collisionExit;
		set_difference(frameCollisions.begin(), frameCollisions.end(), _collisions.begin(), _collisions.end(), inserter(collisionEnter, collisionEnter.begin()));
		set_difference(_collisions.begin(), _collisions.end(), frameCollisions.begin(), frameCollisions.end(), inserter(collisionExit, collisionExit.begin()));
		
		for (const pair<GameObject*, GameObject*>& p : collisionEnter) {
			p.first ->onCollisionEnter(*p.second);
			p.second->onCollisionEnter(*p.first);
			//Debug::log("collision enter: " + p.first->name() + " " + p.second->name());
		}
		//collision exit
		for (const pair<GameObject*, GameObject*>& p : collisionExit) {
			p.first ->onCollisionExit(*p.second);
			p.second->onCollisionExit(*p.first);
		}

		//setit
		_collisions = frameCollisions;
		
	}

	void Physics::addCollider(Collider* collider) {
		//ensure not already present
		auto it = find(_allColliders.begin(), _allColliders.end(), collider);
		if (it != _allColliders.end()) {
			const string& name = collider->gameobject().name();
			Debug::logError("Physics::_allColliders already contains collider: " + name);
			return;
		}
		_allColliders.push_back(collider);
	}
	void Physics::removeCollider(Collider* collider) {
		auto it = find(_allColliders.begin(), _allColliders.end(), collider);
		if (it == _allColliders.end()) {
			const string& name = collider->gameobject().name();
			Debug::logError("Physics::_allColliders doesn't contains collider to remove: " + name);
			return;
		}
		_allColliders.erase(it);
	}

	vector<Collider*> Physics::_allColliders;
	set<pair<GameObject*, GameObject*>> Physics::_collisions;
}