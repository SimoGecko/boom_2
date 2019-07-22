// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// draws information on screen, such as time, score, lives, powerup, levelInfo

namespace sxg::boom {

	struct playerInfo {
		int lives;
		int halfHearts;
		bool extra[5];
		int score;
	};

	class Ui : public Component {
		CLONABLE(Ui)
	public:
	
	
	private:
		// ________________________________ data
		playerInfo p1Info;
		sf::Clock timer;

		// ________________________________ base
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
 

		// ________________________________ queries



		// ________________________________ cloning
	};
}