// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Pickup.h"
// pickup that represents a letter in the word EXTRA, which when completed rewards an additional life

namespace sxg::boom {

	class Extra : public Pickup {
		CLONABLE(Extra)
	public:
		enum class ExtraLetter{E,X,T,R,A};
		
		void switchToNextLetter() {
			string animName = /*(letters + letters)*/letters2.substr(currentLetterIndex, 2);
			Debug::log("extra anim: " + animName);
			currentLetterIndex = (currentLetterIndex+1)%letters.size();
			anim->playAnimation(animName);
			callbackLetterChange();
		}
		

	private:
		// ________________________________ data
		const float timeForLetter = 3.f;
		const string letters = "EXTRA";
		const string letters2 = "EXTRAE";
		int currentLetterIndex;
		Animator* anim;

		// ________________________________ base
		void start() override {
			anim = gameobject().getComponent<Animator>();
			currentLetterIndex = Random::range(0, letters.size());
			string animName = letters.substr(currentLetterIndex, 1);
			Debug::log("extra anim: " + animName);
			anim->playAnimation(animName); // THE ERROR IS HERE; PROBABLY DATA RACE
			callbackLetterChange();
		}

		void update() override {
		
		}

		
		
		// ________________________________ commands
		void pickup(Player& player) override {
			
			ExtraLetter currentLetter = (ExtraLetter)currentLetterIndex;
			char currentLetterChar = letters[currentLetterIndex];
			//notify player of pickup
			gameobject().destroy();
			
		}

		void callbackLetterChange() {
			invoke([this]() {this->switchToNextLetter(); }, timeForLetter);
		}
		


		// ________________________________ queries



	};
}