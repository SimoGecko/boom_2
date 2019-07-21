// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//#include "Explosion.h"
#include "MapBuilder.h"
// placeable bomb that explodes after some time and destroys blocks/kills enemies

namespace sxg::boom {

	class Bomb : public Component {
	public:
		Event onExplode;

	private:
		// ______________ const
		const float bombTimer = 3.f;
		const float tickingOffset = 1.f;
		const int distance = 2;

		// ______________ variables


	public:
		// ______________ base
		void start() override {
			Time::callback([this]() {this->startTicking(); }, bombTimer - tickingOffset);
			Time::callback([this]() {this->explode(); }, bombTimer);

			//test graveyard
			//Time::callback(bind(&Bomb::startTicking, this), bombTimer - tickingOffset);
			//Time::callback(&printTestBomb(), 1.f);
			//Time::callback(explode(), bombTimer);

			//Time::callback([]() {cout << "test" << endl; }, 1.f); // THIS WORKS
			//Time::callback([]() {Bomb::printTestBomb(); }, 1.f); // THIS WORKS
			//invoke()
			//Time::callback(bind(&Bomb::startTicking, this), 1.f);
			//invoke(&Bomb::startTicking, 1);
		}

		void update() override {

		}

		

		
	private:
		// ______________ commands
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

			tryInstantiateExplosionPiece(pos, {  1, 0 }, orientation::horizontal);
			tryInstantiateExplosionPiece(pos, { -1, 0 }, orientation::horizontal);
			tryInstantiateExplosionPiece(pos, { 0,  1 }, orientation::vertical);
			tryInstantiateExplosionPiece(pos, { 0, -1 }, orientation::vertical);
		}

		void tryInstantiateExplosionPiece(sf::Vector2i origin, sf::Vector2i delta, orientation orient) {
			for (int i = 1; i <= distance; ++i) {
				sf::Vector2i position = origin + i * delta;
				bool valid = MapBuilder::instance->isValidExplosionPlace(position);
				if (valid) {
					instantiateExplosionPiece(position, orient);
				}
				else {
					break; // found something to block explosion
				}
			}
		}
		void instantiateExplosionPiece(sf::Vector2i position, orientation orient) {
			//instantiate it there
			GameObject* explosionGo = GameObject::Instantiate("explosion", to_v2f(position));
			//Explosion* explosion = explosionGo->getComponent<Explosion>();
			const string& animName = stringFromOrientation(orient);
			explosionGo->getComponent<Animator>()->playAnimation(animName);
		}


		// ______________ queries



		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Bomb(*this); }
	};

}