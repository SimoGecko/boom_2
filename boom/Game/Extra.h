// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Collectible.h"
// pickup that represents a letter in the word EXTRA, which when completed rewards an additional life

namespace sxg::boom {

	class Extra : public Collectible {
		CLONABLE(Extra)
	public:
		enum class ExtraLetter{E,X,T,R,A};
		
		void switchToNextLetter() {
			string animName = (letters + letters).substr(currentLetterIndex, 2);
			currentLetterIndex = (currentLetterIndex+1)%letters.size();
			anim->playAnimation(animName);
			callbackLetterChange();
		}
		

	private:
		// ________________________________ data
		const float timeForLetter = 3.f;
		const string letters = "EXTRA";
		const float lifetime = 15.0f;
		const PointAmount myPointsOnPickup = PointAmount::p100;


		int currentLetterIndex;
		
		// ________________________________ base
		void start() override {
			Collectible::start();
			pointsOnPickup = myPointsOnPickup;

			currentLetterIndex = Random::range(0, letters.size());
			string animName = letters.substr(currentLetterIndex, 1);
			anim->playAnimation(animName);

			callbackLetterChange();

			gameobject().destroy(lifetime);
		}

		void update() override {
		
		}

		
		
		// ________________________________ commands
		void pickup(Player& player) override {
			ExtraLetter currentLetter = (ExtraLetter)currentLetterIndex;
			char currentLetterChar = letters[currentLetterIndex];
			//notify player of pickup
			player.collectLetter((int)currentLetter);

			gameobject().destroy();
		}

		void callbackLetterChange() {
			invoke([this]() {this->switchToNextLetter(); }, timeForLetter);
		}
		


		// ________________________________ queries
		/*
		const string extraLetter(int i) {
			Debug::ensure(0 <= i && i < letters.size());
			return string(1, letters[i]);
		}
		*/

	};
}