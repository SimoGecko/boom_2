// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Bomb.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Component {
		CLONABLE(Player)
	public:
		void teleport(sf::Vector2f to) {
			//wait to stop
		}
	private:
		// ________________________________ const
		const float speed = 5.f;
		const float speedBoost = 2.f;

		const int nMaxBombs = 3;
		const int nMaxBombsPowerup = 6;

		// ________________________________ variables
		Animator* anim;
		sf::Vector2i prevCell, nextCell;
		float movePercent;

		int availableBombs;

		// ________________________________ base
		void start() override {
			anim = gameobject().getComponent<Animator>();
			prevCell = nextCell = { 0,0 };
			movePercent = 0;
			availableBombs = nMaxBombs;
		}

		void update() override {
			movement();
			placeBomb();
			setAnimation();
		}

		
		// ________________________________ commands
		void movement() {
			sf::Vector2i oldMoveDelta = moveDelta();

			if (moving()) {
				movePercent += speed * Time::deltaTime();
				if (movePercent < 1) {
					transform().setPosition(lerp(prevCell, nextCell, movePercent));
				}
				else {
					prevCell = nextCell;
					transform().setPosition(prevCell.x, prevCell.y);
					movePercent = 0;
				}
			}

			sf::Vector2i input = getInput();
			if (magnitude(input) == 0) return;

			// (not moving + input) -> start/continue moving
			// if continue moving, try first the previous direction axis
			if (abs(oldMoveDelta.x) > 0) {
				tryMove({ input.x, 0 });
				tryMove({ 0, input.y });
			} else {
				tryMove({ 0, input.y });
				tryMove({ input.x, 0 });
			}

			// (moving + input) -> change of dir
			if (moving() && input == -moveDelta()) {
				movePercent = 1 - movePercent;
				swap(nextCell, prevCell);
			}
		}

		void tryMove(sf::Vector2i delta) {
			if (!moving()) {
				bool freeCell = MapBuilder::instance->isWalkable(prevCell + delta);
				if (freeCell) {
					nextCell = prevCell + delta;
				}
			}
		}

		sf::Vector2i moveDelta() { return nextCell - prevCell; }
		bool moving() { return nextCell != prevCell; }

		sf::Vector2i getInput() {
			sf::Vector2i input;
			if (Input::getKey(sf::Keyboard::A)) input.x -= 1;
			if (Input::getKey(sf::Keyboard::D)) input.x += 1;
			if (Input::getKey(sf::Keyboard::W)) input.y -= 1;
			if (Input::getKey(sf::Keyboard::S)) input.y += 1;
			return input;
		}

		

		void setAnimation() {
			string animName;
			if (!moving()) {
				animName = "idle_D";
			}
			else {
				dir playerDir = dirFromVector(to_v2f(moveDelta()));
				char dirchar = charFromDir(playerDir);
				animName = "walk_" + string(1, dirchar);
			}
			if (animName != anim->currentAnimationName()) {
				anim->playAnimation(animName);
			}
		}

		void shoot() {
			if (Input::getMouseButtonDown(0)) {
				GameObject* bullet = GameObject::Instantiate("bullet", &transform());
				Audio::play("Shot");
			}
		}

		void placeBomb() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				if (availableBombs > 0) {
					GameObject* bombGo = GameObject::Instantiate("bomb", to_v2f(currentCell()));
					availableBombs--;
					//call back on explosion
					bombGo->getComponent<Bomb>()->onExplode += [this]() {availableBombs++; };
				}
			}
		}

		// ________________________________ queries
		sf::Vector2i currentCell() { return movePercent < 0.5f ? prevCell : nextCell; }


	};
}