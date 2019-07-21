// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Component.h"
//#include "Physics.h"

// simple collider that is used by the physics engine to find collisions and call the appropriate callbacks

namespace sxg::engine {

	class Collider : public Component {

	public:
		void start() override;
		//void update() override;

		virtual ~Collider();

	protected:
		friend class Physics;
		virtual bool intersects(const Ray& ray, float& outDist) const = 0;
		virtual bool intersects(const Collider& other) const = 0;
		bool isStatic; // used to optimize the engine
	};

	class BoxCollider; // forward decl

	class CircleCollider : public Collider { // sphere collider at the same position as the gameobject
	public:
		bool intersects(const Ray& ray, float& outDist) const override { return false; };
		bool intersects(const Collider& other) const override;
		void setRadius(float radius);

	protected:
		float _radius;

		bool intersectsCircle(const CircleCollider& other) const;
		bool intersectsBox   (const BoxCollider& other) const;

		Component* clone() { return new CircleCollider(*this); }
	};

	class BoxCollider : public Collider { // axis-aligned bounding-box with center same as the gameobject transform
	public:
		bool intersects(const Ray& ray, float& outDist) const override;
		bool intersects(const Collider& other) const override;
		void setSize(sf::Vector2f size);
	protected:
		sf::Vector2f _size;

		bool intersectsCircle(const CircleCollider& other) const;
		bool intersectsBox   (const BoxCollider&    other) const;

		Component* clone() { return new BoxCollider(*this); }
	};

}