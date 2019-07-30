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
		

		static void addPoints(PointAmount pointAmount, sf::Vector2f position, Player* player) {
			//takes care of scoremanager aswell
			GameObject* pointsGo = GameObject::Instantiate("points", position);
			Points* points = pointsGo->getComponent<Points>();

			points->amount = pointAmount;

			Animator* anim = pointsGo->getComponent<Animator>();
			anim->playAnimation(pointAmount2String(points->amount));

			
			player->addScore(pointAmount2Int(points->amount));
		}

	private:
		// ________________________________ data
		const float lifeTime = 1.0f;
		const float moveupSpeed = 1.0f;
		PointAmount amount; // not really used


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

		static int pointAmount2Int(PointAmount amount) {
			return (int)amount * 10;
		}
		static const string pointAmount2String(PointAmount amount) {
			return "points_" + to_string((int)amount * 10);
		}

	};
}