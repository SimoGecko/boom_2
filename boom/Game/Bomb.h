// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//#include "Explosion.h"
#include "MapBuilder.h"
#include "Explosion.h"

//#include "Player.h"
// placeable bomb that explodes after some time and destroys blocks/kills enemies

namespace sxg::boom {

	class Player;

	class Bomb : public Component {
		CLONABLE(Bomb)
	public:
		Event onExplode;
		void trigger(float timer, int distance, Player* player) {
			bombTimer = timer;
			bombDistance = distance;
			owner = player;

			triggerBomb();
		}

	private:
		// ________________________________ const
		const float tickingOffset = 0.5f;

		float bombTimer; // the player sets these
		int bombDistance;
		Player* owner;

		// ________________________________ variables


		// ________________________________ base
		void start() override {

		}

		void update() override {

		}

		
		// ________________________________ commands
		void triggerBomb() {
			invoke([this]() {this->startTicking(); }, bombTimer - tickingOffset);
			invoke([this]() {this->explode(); }, bombTimer);
		}

		void startTicking() {
			gameobject().getComponent<Animator>()->playAnimation("ticking");
		}

		void explode() {
			onExplode();
			instantiateExplosion();

			gameobject().destroy();
		}

		void instantiateExplosion() {
			sf::Vector2i pos = to_v2i(transform().getPosition());
			instantiateExplosionPiece(pos, orientation::center);

			instantiateExplosionDirection(pos, {  1, 0 }, orientation::horizontal);
			instantiateExplosionDirection(pos, { -1, 0 }, orientation::horizontal);
			instantiateExplosionDirection(pos, { 0,  1 }, orientation::vertical);
			instantiateExplosionDirection(pos, { 0, -1 }, orientation::vertical);
		}

		void instantiateExplosionDirection(sf::Vector2i origin, sf::Vector2i delta, orientation orient) {
			int mapDistance = MapBuilder::instance->getExplosionDist(origin, delta);
			for (int i = 1; i <= min(bombDistance, mapDistance); ++i) {
				instantiateExplosionPiece(origin + i * delta, orient);
			}
		}

		void instantiateExplosionPiece(sf::Vector2i position, orientation orient) {
			GameObject* explosionGo = GameObject::Instantiate("explosion", to_v2f(position));
			const string& animName = stringFromOrientation(orient);
			explosionGo->getComponent<Animator>()->playAnimation(animName);
			explosionGo->getComponent<Explosion>()->setPlayer(owner);
		}


		// ________________________________ queries


	};
}