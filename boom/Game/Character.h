// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Living.h"
#include "Explosion.h"
#include "Player.h"

// abstract base class for characters (player + enemies) that move, have health

namespace sxg::boom {

	class Character : public Component, public Living {
	public:

	protected:
		// ________________________________ data
		int explosionDamage = 1;

		Animator* anim;
		Player* damageResponsiblePlayer;
		//movement
		sf::Vector2i prevCell, nextCell;
		float movePercent;
		bool doMove;

		// ________________________________ base
	protected:
		void start() override {
			anim = gameobject().getComponent<Animator>();
			prevCell = nextCell = to_v2i(transform().getPosition());
			movePercent = 0;
			doMove = true;
		}

		void update() override {
			if(doMove) movement();
			setAnimation();
		}

		
		void onCollisionEnter(GameObject& other) {
			if (other.tag() == Tag::explosion) {
				damageResponsiblePlayer = other.getComponent<Explosion>()->getPlayer();

				takeDamage(explosionDamage);
			}
			if (other.tag() == Tag::teleporter) {
				//TELEPORT
			}
		}
		

	private:
		// ________________________________ commands
		void movement() {
			sf::Vector2i oldMoveDelta = moveDelta();

			if (moving()) {
				movePercent += moveSpeed() * Time::deltaTime();
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
			if (magnitude1(input) == 0) return;

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

		// either player input or AI control
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
			if (dead()) animName = "death";
			if (animName != anim->currentAnimationName()) {
				anim->playAnimation(animName);
			}
		}

		// ________________________________ queries


	protected:
		bool freeCell(sf::Vector2i delta) {
			return MapBuilder::instance->isWalkable(prevCell + delta);
		}
		sf::Vector2i moveDelta() { return nextCell - prevCell; }
		bool attacking() { return false; }
		bool moving() { return nextCell != prevCell; }
		virtual float moveSpeed() = 0;
		sf::Vector2i currentCell() { return movePercent < 0.5f ? prevCell : nextCell; }

	};
}