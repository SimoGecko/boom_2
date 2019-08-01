// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Score.h"
#include "GameManager.h"
#include "Extra.h"

// draws information on screen, such as time, score, lives, powerup, levelInfo

namespace sxg::boom {



	class Ui : public Component {
		CLONABLE(Ui)
	public:
		const sf::Vector2f canvasOffset		= { -4.0, -1.0 };

		const sf::Vector2i headOffset		= { 16, 60 };
		const sf::Vector2i livesTextOffset	= { 54, 59 };

		const sf::Vector2i heartOffset		= { 16, 91 };
		const sf::Vector2i heartDist		= { 16, 18 };
		const int nHeartsPerRow = 4;
		const int nHearts = 8;

		const sf::Vector2i extraOffset		= { 12, 130 };
		const sf::Vector2i extraDist		= { 14, 0 };
		const int nExtra = 5;

		const sf::Vector2i powerupOffset	= { 12, 149 };
		const sf::Vector2i powerupDist		= { 14, 0 };
		const sf::Vector2i powerupTextDist	= { 3, 15 };
		const int nPowerup = 5;

		const sf::Vector2i scoreTextOffset	= { 16,173 };
		//const sf::Vector2i scoreNumberOffset= { 13, 197 };

		const sf::Vector2i dropShadowDist	= { 2,2 };
		const sf::Color	   dropShadowColor  = { 24, 16, 74 }; // dark violet

		const sf::Vector2f playerCanvasOffset = { 6.5, 0.0 };
		const float ppu = 32.f;

		const string defaultFontName = "boomFont";

	private:
		// ________________________________ data

		struct playerUI {
			vector<Animator*> hearts;
			Animator* head;
			vector<Animator*> extraIcons;
			vector<Animator*> powerupIcons;

			sf::Text* livesText;
			sf::Text* powerupText;
			sf::Text* scoreText;

			playerUI() : head(nullptr), livesText(nullptr), powerupText(nullptr), scoreText(nullptr) { }
		};

		vector<playerUI> playerUIs;
		sf::Text *timerText, *levelText;


		//refs
		vector<playerInfo>* playerInfos;


		// ________________________________ base
		void start() override {
			playerUIs.resize(GameManager::instance()->nPlayers);
			playerInfos = &(Score::instance()->playerInfos);

			setupIcons();
			setupText();
			createDropShadow();
			
		}

		void update() override {
			//todo event callbacks to improve performance
			updatePlayerUI();
		}
		
		// ________________________________ commands
		void setupIcons() {
			for (size_t i = 0; i < GameManager::instance()->nPlayers; ++i) {
				playerUI& currentpUI = playerUIs[i];

				//hearts
				for (int i = 0; i < nHearts; ++i) {
					GameObject* heartGo = GameObject::Instantiate("heart", UIpos(heartOffset, heartDist, i/nHeartsPerRow, i%nHeartsPerRow));
					currentpUI.hearts.push_back(heartGo->getComponent<Animator>());
				}
				
				//head
				GameObject* headGo = GameObject::Instantiate("head", UIpos(headOffset));
				currentpUI.head = headGo->getComponent<Animator>();
				//set head color

				//extra
				for (size_t c = 0; c < nExtra; ++c) {
					GameObject* extraGo = GameObject::Instantiate("extraIcon", UIpos(extraOffset, extraDist, 0, c));
					currentpUI.extraIcons.push_back(extraGo->getComponent<Animator>());
				}

				//powerup
				for (size_t c = 0; c < nPowerup; ++c) {
					//GameObject* powerupGo = GameObject::Instantiate("powerupIcon", UIpos(powerupOffset, powerupDist, 0, c));
					//currentpUI.powerupIcons.push_back(powerupGo->getComponent<Animator>());
				}
			}
		}

		void setupText() {
			for (size_t i = 0; i < GameManager::instance()->nPlayers; ++i) {
				playerUI& currentpUI = playerUIs[i];

				currentpUI.livesText = Font::getText(defaultFontName, 16, 32);
				currentpUI.livesText->setPosition(UIpos(livesTextOffset));
				currentpUI.livesText->setString("*0");
				currentpUI.livesText->setLetterSpacing(1.6f);

				//currentpUI.powerupText = Font::getText(defaultFontName, 8, 32);
				//currentpUI.powerupText->setString("*5");
				//currentpUI.powerupText->setPosition(UIpos(powerupOffset, powerupTextDist, 1, 0));
				//currentpUI.powerupText->setLetterSpacing(1.6f);

				currentpUI.scoreText = Font::getText(defaultFontName, 16, 32);
				currentpUI.scoreText->setString("score\n000000");
				currentpUI.scoreText->setPosition(UIpos(scoreTextOffset));
				currentpUI.scoreText->setLetterSpacing(1.6f);
			}
		}
 
		void createDropShadow() {

		}

		void updatePlayerUI() {
			for (size_t i = 0; i < GameManager::instance()->nPlayers; ++i) {
				playerUI& currentpUI = playerUIs[i];
				playerInfo& currentInfo = playerInfos->at(i);
				
				//#lives
				string livesString = "*" + to_string(currentInfo.lives);
				currentpUI.livesText->setString(livesString);

				//#hearts
				for (int i = 0; i < currentpUI.hearts.size(); ++i) {
					const vector<string> heartAnim({ "empty", "half", "full" });
					int heartStatus = clamp(currentInfo.halfHearts-2*i, 0, 2);
					currentpUI.hearts[i]->playAnimation(heartAnim[heartStatus]);
				}

				//EXTRA
				for (int i = 0; i < nExtra; ++i) {
					bool hasLetter = currentInfo.extra[i];
					if (hasLetter) {
						currentpUI.extraIcons[i]->playAnimation(string(1, "EXTRA"[i]));
					}
					else {
						currentpUI.extraIcons[i]->playAnimation("empty");
					}
				}

				//powerup

				//score
				string scoreFormatString = to_string_pad0(currentInfo.score, 6);
				currentpUI.scoreText->setString("score\n" + scoreFormatString);
			}
		}

		// ________________________________ queries
		sf::Vector2f UIpos(const sf::Vector2i offset, const sf::Vector2i dist = {0,0}, int r=0, int c=0) {
			return sf::Vector2f(offset.x + c * dist.x, offset.y + r * dist.y) / ppu + (canvasOffset);
		}



	};
}