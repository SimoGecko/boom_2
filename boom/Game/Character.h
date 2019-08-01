// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Map.h"
#include "Living.h"
#include "Explosion.h"

// abstract base class for characters (player + enemies) that move, have health

namespace sxg::boom {

	class Player;

	class Character : public Component, public Living {
	public:
		bool canTeleport() {
			return canTeleportBool;
		}

		void teleport(sf::Vector2f to) {
			if (!canTeleportBool) return;
			//wait to stop
			teleportTo = to_v2i(to);
			mustTeleport = true;
			canTeleportBool = false;
		}

	protected:
		// ________________________________ data
		//int explosionDamage = 1;

		Animator* anim;
		//Player* damageResponsiblePlayer;
		//movement
		sf::Vector2i prevCell, nextCell;
		float movePercent;
		bool canMove;

		bool mustTeleport;
		bool canTeleportBool;
		sf::Vector2i teleportTo;

		// ________________________________ base
	protected:
		void start() override {
			anim = gameobject().getComponent<Animator>();

			prevCell = nextCell = to_v2i(transform().getPosition());
			movePercent = 0;
			canMove = true;

			mustTeleport = false;
			canTeleportBool = true;
		}

		void update() override {
			if(canMove) movement();
			setAnimation();
		}

		
		void onCollisionEnter(GameObject& other) {

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
					if (mustTeleport) {
						mustTeleport = false;
						nextCell = teleportTo; // go there
						invoke([this] {canTeleportBool = true; }, 0.1f);
					}

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
			return Map::instance()->isWalkable(prevCell + delta);
		}
		sf::Vector2i moveDelta() { return nextCell - prevCell; }
		bool moving() { return nextCell != prevCell; }
		sf::Vector2i currentCell() { return movePercent < 0.5f ? prevCell : nextCell; }

		virtual float moveSpeed() = 0;
		virtual bool attacking() { return false; }
	};
}