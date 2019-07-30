// (c) Simone Guggiari 2019
#include "Physics.h"


namespace sxg::engine {

	void Physics::update() {
		set<pair<Collider*, Collider*>> frameCollisions;

		for (size_t i = 0; i < _allColliders.size(); ++i) {
			for (size_t j = i + 1; j < _allColliders.size(); ++j) {
				//if collision, call back on both
				if (_allColliders[i]->intersects(*_allColliders[j])) {
					frameCollisions.insert({ _allColliders[i], _allColliders[j] });
				}
			}
		}
		
		//check diff between previous and current collisions
		set<pair<Collider*, Collider*>> collisionEnter, collisionExit;
		set_difference(frameCollisions.begin(), frameCollisions.end(), _collisions.begin(), _collisions.end(), inserter(collisionEnter, collisionEnter.begin()));
		set_difference(_collisions.begin(), _collisions.end(), frameCollisions.begin(), frameCollisions.end(), inserter(collisionExit, collisionExit.begin()));
		
		//collision ENTER
		for (const pair<Collider*, Collider*>& p : collisionEnter) {
			if (p.first == nullptr || p.second == nullptr) {
				Debug::logError("Found nullptr gameobject while checking collisionEnter");
				continue;
			}
			GameObject& goA = p.first ->gameobject();
			GameObject& goB = p.second->gameobject();
			goA.onCollisionEnter(goB);
			goB.onCollisionEnter(goA);
		}
		//collision EXIT
		/*
		//for when it's gonna be needed
		for (const pair<Collider*, Collider*>& p : collisionExit) {
			if (p.first == nullptr || p.second == nullptr) {
				Debug::logError("Found nullptr gameobject while checking collisionExit");
				continue;
			}
			if (_collidersRemovedLastFrame.count(p.first) || _collidersRemovedLastFrame.count(p.second)) {
				continue;
			}
			GameObject& goA = p.first->gameobject();
			GameObject& goB = p.second->gameobject();
			goA.onCollisionExit(goB);
			goB.onCollisionExit(goA);
		}
		*/

		//setit
		_collisions = frameCollisions;
		
		_collidersRemovedLastFrame.clear();
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

		//TODO ensure it's not inside active collisions
		_collidersRemovedLastFrame.insert(collider);
	}


	vector<Collider*> Physics::_allColliders;
	set<pair<Collider*, Collider*>> Physics::_collisions; // use weak pointers (solves the problem of checking if valid)
	set<Collider*> Physics::_collidersRemovedLastFrame;
}