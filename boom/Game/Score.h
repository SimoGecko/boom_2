// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "GameManager.h"

// manages PERSISTENT data for level, players (score/time/lives)

namespace sxg::boom {

	struct playerInfo {
		int lives;
		int halfHearts;
		int score;
		vector<bool> extra;

		playerInfo() : lives(3), halfHearts(16), score(0), extra(5, false) {}
	};

	class Score : public Component {
	CLONABLE(Score)
	public:
		static Score* instance;

		vector<playerInfo> playerInfos; // live here but player and UI get access to it

		
	private:
		// ________________________________ data


		sf::Clock timer;
		int level;
		friend class Ui;


		// ________________________________ base
		void awake() override {
			if (instance != nullptr) Debug::logError("Multiple copies of singleton: Score");
			instance = this;

			playerInfos.resize(GameManager::nPlayers);
		}
		
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
 


		// ________________________________ queries
		/*
		vector<playerInfo*> playerInfoPtr() {
			vector<playerInfo*> ans;
			for (playerInfo& pi : playerInfos) ans.push_back(&pi);
			return ans;
		}
		
		playerInfo* getPlayerInfo(int index) {
			return &playerInfos[index];
		}
		
		
		*/

		



	};
}