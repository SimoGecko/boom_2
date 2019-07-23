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
		const sf::Vector2i canvasOffset		= { -4, -1 };

		const sf::Vector2i headOffset		= { 16, 60 };
		const sf::Vector2i livesTextOffset	= { 52, 64 };

		const sf::Vector2i heartOffset		= { 16, 92 };
		const sf::Vector2i heartDist		= { 16, 18 };
		const sf::Vector2i heartMatrix		= { 2, 4 };

		const sf::Vector2i extraOffset		= { 13, 131 };
		const sf::Vector2i extraDist		= { 14, 0 };
		int nExtra = 5;

		const sf::Vector2i bonusOffset		= { 13, 150 };
		const sf::Vector2i bonusDist		= { 14, 0 };
		const sf::Vector2i bonusTextDist	= { 0, 16 };
		int nBonus = 5;

		const sf::Vector2i scoreTextOffset	= { 14,181 };
		const sf::Vector2i scoreNumberOffset= { 13, 197 };

		const sf::Vector2i dropShadowDist	= { 2,2 };
		const float ppu = 32.f;

		const string defaultFontName = "Born2bSportyV2";

	private:
		// ________________________________ data
		playerInfo p1Info;
		sf::Clock timer;
		vector<Animator*> hearts;
		sf::Text *livesText, *scoreText;

		// ________________________________ base
		void start() override {
			setupUI();
			setupText();
			
		}

		void update() override {
			if (Input::getKeyDown(sf::Keyboard::Q)) livesText->setString("changed text: score x2 00987");
			if (Input::getKeyDown(sf::Keyboard::E)) Font::removeText(livesText);

		}
		
		// ________________________________ commands
		void setupUI() {
			//hearts
			for(size_t r=0; r<heartMatrix.x; ++r){
				for (size_t c = 0; c < heartMatrix.y; ++c) {
					GameObject::Instantiate("heart", UIpos(heartOffset, heartDist, r, c));
				}
			}
			//head
			GameObject::Instantiate("head", UIpos(headOffset)); //to_v2f(headOffset)/ ppu + to_v2f(offset)

			//extra
			for (size_t c = 0; c < nExtra; ++c) {
				GameObject::Instantiate("extraIcon", UIpos(extraOffset, extraDist, 0, c));
			}

			//bonus
			for (size_t c = 0; c < nBonus; ++c) {
				GameObject::Instantiate("bonusIcon", UIpos(bonusOffset, bonusDist, 0, c));
			}

		}

		void setupText() {
			livesText = Font::getText(defaultFontName, 32, 32);
			livesText->setPosition(UIpos(livesTextOffset));
			livesText->setString("X 3");

			scoreText = Font::getText(defaultFontName, 32, 32);
			scoreText->setString("score:\n00000");
			scoreText->setPosition(UIpos(scoreTextOffset));
		}
 

		// ________________________________ queries
		sf::Vector2f UIpos(const sf::Vector2i offset, const sf::Vector2i dist = {0,0}, int r=0, int c=0) {
			return sf::Vector2f(offset.x + c * dist.x, offset.y + r * dist.y) / ppu + to_v2f(canvasOffset);
		}



		// ________________________________ cloning
	};
}