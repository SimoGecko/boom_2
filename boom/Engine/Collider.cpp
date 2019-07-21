// (c) Simone Guggiari 2019
#include "Collider.h"
#include "Physics.h"

namespace sxg::engine {

	
	void Collider::start() {
		Physics::addCollider(this);
	}

	Collider::~Collider() {
		Physics::removeCollider(this);
	}

	bool CircleCollider::intersects(const Collider& other) const {
		const CircleCollider* otherCircle = dynamic_cast<const CircleCollider*>(&other);
		if (otherCircle != nullptr) {
			return intersectsCircle(*otherCircle);
		}
		return false;// other.intersects(*this);
	}

	void CircleCollider::setRadius(float radius) { _radius = radius; }


	bool CircleCollider::intersectsCircle(const CircleCollider& other) const {
		float dist2 = magnitude2(transform().getPosition() - other.transform().getPosition());
		return dist2 <= pow(_radius + other._radius, 2);
	}
	bool CircleCollider::intersectsBox(const BoxCollider& other) const {
		float dist2 = magnitude2(transform().getPosition() - other.transform().getPosition());
		float boxEffectiveRadius = 0; // TODO
		return dist2 <= pow(_radius + boxEffectiveRadius, 2);
	}
	
	void BoxCollider::setSize(sf::Vector2f size) { _size = size; }


	bool BoxCollider::intersectsCircle(const CircleCollider& other) const {
		//same code as before
		return false;
		//return other.intersectsBox(*this);
	}

	bool BoxCollider::intersectsBox(const BoxCollider& other) const {
		sf::FloatRect myRect(transform().getPosition(), _size);
		sf::FloatRect otherRect(other.transform().getPosition(), other._size);
		return myRect.intersects(otherRect);
	}
	
}