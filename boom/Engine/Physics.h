// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "GameObject.h"
#include "Collider.h"

// rudimental physics engine that checks collisions between colliders and calls callbacks function on collision

namespace sxg::engine {

	class Collider;

	class Physics {
		struct RaycastHit {
			Collider* collider;
			float distance;
			sf::Vector2f point;
		};

	public:
		static bool intersects(const Ray& ray, const Collider& collider, int& outDist);
		static bool raycast   (const Ray& ray, RaycastHit& hit, float maxDist, int collisionMask);
		static vector<Collider&> overlapSphere(sf::Vector2f position, float radius, int layerMask);

		static void start();
		static void update();

		static void addCollider(Collider* collider);
		static void removeCollider(Collider* collider);
		//static void removeGameObject(GameObject* gameobject);

	private:
		static vector<Collider*> _allColliders; // make one static and one dynamic
		static set<pair<Collider*, Collider*>> _collisions;
		static set<Collider*> _collidersRemovedLastFrame;
	};

}