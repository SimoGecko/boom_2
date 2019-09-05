// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "GameData.h"
#include "Extra.h"

// draws information on screen, such as time, score, lives, powerup, levelInfo

namespace sxg::boom {



	class Ui : public Component {
		CLONABLE(Ui)
	public:
		static Ui* instance() { return _instance; }

		void setMainText(const string& text) {
			mainText->setString(text);
			center(mainText);
		}



	private:
		// ________________________________ const

		static Ui* _instance;

		// int are pixels
		// float are units

		//offset = in pixels from topleft
		// dist = spacing between similar elements

		const sf::Vector2f canvasOffset = { -4.0f, -1.0f };
		const sf::Vector2f playerCanvasOffset = { 0.0f, 6.5f };

		const sf::Vector2i headOffset = { 16, 60 };
		const sf::Vector2i livesTextOffset = { 54, 59 };

		const sf::Vector2i heartOffset = { 16, 91 };
		const sf::Vector2i heartDist = { 16, 18 };
		const int nHeartsPerRow = 4;
		const int nHearts = 8;

		const sf::Vector2i extraOffset = { 12, 130 };
		const sf::Vector2i extraDist = { 14, 0 };
		const int nExtra = 5;

		const sf::Vector2i powerupOffset = { 12, 149 };
		const sf::Vector2i powerupDist = { 14, 0 };
		const sf::Vector2i powerupTextDist = { 3, 15 };
		const int nPowerup = 5;

		const sf::Vector2i scoreTextOffset = { 16,173 };
		//const sf::Vector2i scoreNumberOffset= { 13, 197 };

		const sf::Vector2i dropShadowDist = { 2,2 };
		const sf::Color	   dropShadowColor = { 24, 16, 74 }; // dark violet

		
		const sf::Vector2i timerTextOffset = { 22, 233 };
		const sf::Vector2i levelTextOffset = { 614, 4 };
		const sf::Vector2i mainTextOffset  = { 370, 240 };



		const float ppu = 32.f;

		const string defaultFontName = "boomFont";
		
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
		sf::Text* timerText;
		sf::Text* levelText;
		sf::Text* mainText;


		//refs
		vector<playerInfo>* playerInfos;
		GameData* data;


		// ________________________________ base
		void awake() {
			_instance = this;
			data = gameobject().getComponent<GameData>();

			setupGeneralText();
		}

		void start() override {
			playerUIs.resize(numPlayers());
			playerInfos = &(data->playerInfos);

			setupIcons();
			setupText();
			createDropShadow();

			setLevelText(data->level);
		}

		void update() override {
			//todo event callbacks to improve performance
			updatePlayerUI();
			setTimerText(data->levelTimer);
		}
		
		// ________________________________ commands
		void setupIcons() {
			for (size_t i = 0; i < numPlayers(); ++i) {
				playerUI& currentpUI = playerUIs[i];

				//hearts
				for (int h = 0; h < nHearts; ++h) {
					GameObject* heartGo = GameObject::Instantiate("heart", UIpos(heartOffset, i, heartDist, h/nHeartsPerRow, h%nHeartsPerRow));
					currentpUI.hearts.push_back(heartGo->getComponent<Animator>());
				}
				
				//head
				GameObject* headGo = GameObject::Instantiate("head", UIpos(headOffset, i));
				currentpUI.head = headGo->getComponent<Animator>();
				currentpUI.head->playAnimation("p" + to_string(i + 1) + "_head"); // head color

				//extra
				for (size_t c = 0; c < nExtra; ++c) {
					GameObject* extraGo = GameObject::Instantiate("extraIcon", UIpos(extraOffset, i, extraDist, 0, c));
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
			for (size_t i = 0; i < numPlayers(); ++i) {
				playerUI& currentpUI = playerUIs[i];
				currentpUI.livesText = setupIndividualText(UIpos(livesTextOffset, i));
				//currentpUI.powerupText = setupIndividualText(UIpos(powerupOffset, i, powerupTextDist, 1, 0));
				currentpUI.scoreText = setupIndividualText(UIpos(scoreTextOffset, i));
			}

		}

		void setupGeneralText() {
			//main text
			timerText = setupIndividualText(UIpos(timerTextOffset));
			levelText = setupIndividualText(UIpos(levelTextOffset));
			mainText  = setupIndividualText(UIpos(mainTextOffset));
		}

		sf::Text* setupIndividualText(sf::Vector2f pos) {
			sf::Text* text = Font::getText(defaultFontName, 16, 32);
			text->setPosition(pos);
			text->setString("");
			text->setLetterSpacing(1.6f);
			//create drop shadow
			return text;
		}
 
		void createDropShadow() {

		}

		void updatePlayerUI() {
			for (size_t i = 0; i < numPlayers(); ++i) {
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

		void setTimerText(float seconds) {
			timerText->setString(to_min_sec(seconds));
		}
		void setLevelText(int level) {
			levelText->setString(to_string_pad0(level, 2));
		}

		// ________________________________ queries
		sf::Vector2f UIpos(const sf::Vector2i offset, int playerNo = 0, const sf::Vector2i dist = {0,0}, int r=0, int c=0) {
			return sf::Vector2f(offset.x + c * dist.x, offset.y + r * dist.y) / ppu + (canvasOffset + playerCanvasOffset*(float)playerNo);
		}

		void center(sf::Text* text) {
			sf::Rect rect = text->getLocalBounds();
			if (rect.width*rect.height == 0) return;
			text->setOrigin(rect.width / 2, rect.height / 2);
		}

		int numPlayers() { return GameData::instance()->numPlayers; }


	};
}