// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// __DESCRIPTION__

namespace sxg::boom {

	class Bullet : public Component {
	private:
		// ______________ members
		float speed = 3;

	public:
		// ______________ base
		void start() override {
			Debug::Log("bullet start");
		}

		void update() override {
			move();
		}
	private:
		// ______________ commands
		void move() {
			Vector2 moveDelta = Vector2(1, 0) * speed * Time::deltaTime();
			transform().move(moveDelta);
			Debug::Log(gameobject().name() + "_bullet_update");
		}

		// ______________ queries



		using Component::Component; // must inherit ctor
		//Bullet* clone override()
	};

}