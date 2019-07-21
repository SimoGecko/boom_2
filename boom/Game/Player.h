// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Bomb.h"

// prototypical class to move player around

namespace sxg::boom {

	class Player : public Component {
	private:
		// ______________ const
		const float speed = 2.5f;
		const int nMaxBombs = 3;

		// ______________ variables
		Animator* anim;
		//sf::Vector2f moveDelta;
		sf::Vector2i prevCell, nextCell;
		float movePercent;
		int availableBombs;

	public:
		// ______________ base
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
			//shoot();
			//Gizmos::drawCircle(transform().getPosition(), 0.5f);
		}

		void teleport(sf::Vector2f to) {
			//wait to stop
		}
	private:
		// ______________ commands
		void movement() {
			//IMPROVE TO BE SNAPPIER!
			bool moving = prevCell != nextCell;
			if (!moving) {
				sf::Vector2i input;
				//look for new dir
				if (Input::getKey(sf::Keyboard::A)) input.x -= 1;
				if (Input::getKey(sf::Keyboard::D)) input.x += 1;
				if (input.x == 0) {
					if (Input::getKey(sf::Keyboard::W)) input.y -= 1;
					if (Input::getKey(sf::Keyboard::S)) input.y += 1;
				}
				if (input != sf::Vector2i(0,0)) {
					bool freeCell = MapBuilder::instance->isWalkable(prevCell + input);
					if (freeCell) {
						moving = true;
						nextCell = prevCell + input;
						movePercent = 0;
					}
				}
			}
			if (moving) {
				movePercent += speed * Time::deltaTime();
				if (movePercent >= 1) {
					moving = false;
					prevCell = nextCell;
					transform().setPosition(prevCell.x, prevCell.y);
					//continue
					movement();
				}
				else {
					movePercent += speed * Time::deltaTime();
					transform().setPosition(lerp(prevCell, nextCell, movePercent));
				}
				//take care change of dir
			}

			//moveDelta = input * speed * Time::deltaTime();
			//transform().move(moveDelta);
		}

		void setAnimation() {
			sf::Vector2f moveDelta = to_v2f(nextCell - prevCell);
			bool moving = magnitude2(moveDelta) > 0;
			string animName;
			if (!moving) {
				animName = "idle_D";
			}
			else {
				dir playerDir = dirFromVector(moveDelta);
				char dirchar = charFromDir(playerDir);
				animName = "walk_" + string(1, dirchar);
			}
			if (animName != anim->currentAnimationName()) {
				anim->playAnimation(animName);
			}
		}

		void shoot() {
			if (Input::getMouseButtonDown(0)) {
				//instantiate new bullet at this position
				GameObject* bullet = GameObject::Instantiate("bullet", &transform());
				Audio::play("Shot");
			}
		}

		void placeBomb() {
			if (Input::getKeyDown(sf::Keyboard::Space)) {
				//instantiate new bullet at this position
				if (availableBombs > 0) {
					GameObject* bombGo = GameObject::Instantiate("bomb", to_v2f(currentCell()));
					availableBombs--;
					//call back on explosion
					bombGo->getComponent<Bomb>()->onExplode += [this]() {availableBombs++; };
				}
			}
		}

		// ______________ queries
		sf::Vector2i currentCell() { return movePercent < 0.5f ? prevCell : nextCell; }


		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Player(*this); }
	};

}