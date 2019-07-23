// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"

// abstract base class for characters (player + enemies) that move, have health

namespace sxg::boom {

	class Character : public Component {
	public:

	protected:
		// ________________________________ data
		float moveSpeed = 5.f;
		float startingHealth = 3;


		//variables
		Animator* anim;
		sf::Vector2i prevCell, nextCell;
		float movePercent;

		float health;

		// ________________________________ base
	protected:
		void start() override {
			anim = gameobject().getComponent<Animator>();
			prevCell = nextCell = to_v2i(transform().getPosition());
			movePercent = 0;
		}

		void update() override {
			movement();
			setAnimation();

		}

		void onCollisionEnter(GameObject& other) {

			if (other.tag() == Tag::explosion) {
				takeDamage(1);
			}
		}

	private:
		// ________________________________ commands
		void movement() {
			sf::Vector2i oldMoveDelta = moveDelta();

			if (moving()) {
				movePercent += speed() * Time::deltaTime();
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
			}
			else {
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
			if (!moving() && freeCell(delta)) {
				nextCell = prevCell + delta;
			}
		}

		virtual sf::Vector2i getInput() = 0;

		void setAnimation() {
			string animName;
			if (!moving()) {
				animName = "idle_D";
			}
			else {
				dir playerDir = dirFromVector(to_v2f(moveDelta()));
				char dirchar = charFromDir(playerDir);
				string prefix = attacking() ? "attack_" : "walk_";
				animName = prefix + string(1, dirchar);
			}
			if (animName != anim->currentAnimationName()) {
				anim->playAnimation(animName);
			}
		}

		void takeDamage(int damage) {
			Debug::log(gameobject().name() + " took damage!");
		}


		// ________________________________ queries


	protected:
		bool freeCell(sf::Vector2i delta) {
			return MapBuilder::instance->isWalkable(prevCell + delta);
		}
		sf::Vector2i moveDelta() { return nextCell - prevCell; }
		bool attacking() { return false; }
		bool moving() { return nextCell != prevCell; }
		virtual float speed() { return moveSpeed; };
		sf::Vector2i currentCell() { return movePercent < 0.6f ? prevCell : nextCell; }

	};
}