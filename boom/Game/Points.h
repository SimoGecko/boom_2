// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Player.h"

// visual representation of points that can be earned by performing actions

namespace sxg::boom {

	enum class PointAmount {
		p10 = 1, p50 = 5, p100 = 10, p150 = 15, p200 = 20, p300 = 30, p400 = 40, p500 = 50, p600 = 60, p700 = 70, p800 = 80, p900 = 90, p1000 = 100,
		p5000, p100000, life_1up, life_2up,
	};

	class Points : public Component {
	CLONABLE(Points)
	public:
		

		void setup(PointAmount pointAmount, Player* player) {
			amount = pointAmount;
			Animator* anim = gameobject().getComponent<Animator>();
			anim->playAnimation(pointAmount2String(amount));
			player->addScore(pointAmount2Int(amount));
		}

	private:
		// ________________________________ data
		const float lifeTime = 1.0f;
		const float moveupSpeed = 1.0f;
		PointAmount amount;


		// ________________________________ base
		void start() override {
			gameobject().destroy(lifeTime);
		}

		void update() override {
			moveup();
		}
		
		// ________________________________ commands
		void moveup() {
			transform().move(sf::Vector2f(0, -moveupSpeed)*Time::deltaTime());
		}




		// ________________________________ queries

		int pointAmount2Int(PointAmount amount) {
			return (int)amount * 10;
		}
		const string pointAmount2String(PointAmount amount) {
			return "points_" + to_string((int)amount * 10);
		}

	};
}