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
		void dropBomb(float timer, int distance, Player* player) {
			bombTimer = timer;
			bombDistance = distance;
			owner = player;

			setTriggers();
		}

	private:
		// ________________________________ const
		const float tickingOffset = 0.5f;
		const float triggerExplosionDelayPerUnit = 0.2f;

		float bombTimer; // the player sets these
		int bombDistance;
		Player* owner;
		bool exploded;
		// ________________________________ variables


		// ________________________________ base
		void start() override {
			exploded = false;
		}

		void update() override {

		}

		void onCollisionEnter(GameObject& other) override {
			if (other.tag() == Tag::explosion) {
				triggerFromExplosion(other.getComponent<Explosion>());
			}
		}

		
		// ________________________________ commands
		void triggerFromExplosion(Explosion* explosion) {
			//explode immediately due to triggering
			sf::Vector2f delta = transform().getPosition() - explosion->getOrigin();
			int distanceFromOgirin = magnitude1(to_v2i(delta));
			invoke([this]() {this->explode(); }, triggerExplosionDelayPerUnit * distanceFromOgirin);
		}

		void setTriggers() {
			invoke([this]() {this->startTicking(); }, bombTimer - tickingOffset);
			invoke([this]() {this->explode(); }, bombTimer);
		}

		void startTicking() {
			if (exploded) return;
			gameobject().getComponent<Animator>()->playAnimation("ticking");
		}

		void explode() {
			if (exploded) return; // avoid repeated calls
			exploded = true;

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
			Explosion* explosion = explosionGo->getComponent<Explosion>();
			explosion->setup(owner, transform().getPosition());

			const string& animName = stringFromOrientation(orient);
			explosionGo->getComponent<Animator>()->playAnimation(animName);
		}


		// ________________________________ queries


	};
}