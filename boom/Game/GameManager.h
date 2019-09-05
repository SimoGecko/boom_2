// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "GameData.h"
// manages the game state and flow (PERSISTENT)

#include "Player.h"
#include "Spawner.h"
#include "MapBuilder.h"
#include "Ui.h"

namespace sxg::boom {

	class GameManager : public Component {
	CLONABLE(GameManager)
	public:

	private:
		// ________________________________ data
		sf::Clock timer;
		
		const float levelTime  = 4 * 60.f;
		const float extraGameDuration = 1 * 60.f;
		const float hurryUpAdvance = 30.f;
		const float introDuration = 3.f;
		const float outroDuration = 3.f;

		bool running;

		static const int nPlayers = 2;
		GameData* data;


		// ________________________________ base
		void awake() override {
			data = gameobject().getComponent<GameData>();
			data->numPlayers = nPlayers;
			data->playerInfos.resize(nPlayers);
		}

		void start() override {
			data->level = 1;
			running = false;

			startLevel(data->level);
			//consider pause aswell
			invoke([this] {showHurryUp(); }, levelTime - hurryUpAdvance);
			invoke([this] {onTimerEnded(); }, levelTime);
			//deal gameover
		}

		void update() override {
			if (running) {
				data->levelTimer -= Time::deltaTime();
				if (data->levelTimer < 0) data->levelTimer = 0;
			}
		}
		
		// ________________________________ commands
		void startLevel(int level) {
			data->levelTimer = levelTime;
			Ui::instance()->setMainText("Level " + to_string_pad0(data->level, 2) + "\nGET READY!");
			invoke([=] {spawnLevel(level); }, introDuration);
		}

		void spawnLevel(int level) {
			//disable ui text
			Ui::instance()->setMainText("");

			MapBuilder::instance()->buildLevel(level);
			Spawner::instance()->instantiatePlayers(GameData::instance()->numPlayers);
			Spawner::instance()->instantiateEnemies();

			Coin::onAllCoinsCollected += [this] {
				startExtraGame();
				invoke([this] {stopExtraGame(); }, extraGameDuration);
			};
			Enemy::onAllEnemiesDefeated += [this] {levelComplete(); };
			running = true;
		}



		void showHurryUp() {
			//show title
			GameObject::Instantiate("writing_hurryUp");
		}

		void onTimerEnded() {
			//make all enemies faster
			forallEnemies([](Enemy* enemy) {enemy->speedUp(); });
		}



		void startExtraGame() {
			//turn all into amoeba
			GameObject::Instantiate("writing_extraGame");
			forallEnemies([](Enemy* enemy) {enemy->setAmeba(true); });
		}

		void stopExtraGame() {
			//turn all into normal
			forallEnemies([](Enemy* enemy) {enemy->setAmeba(false); });
		}

		void levelComplete() {
			running = false;
			//wait some time
			invoke([this] {notifyPlayers(); }, outroDuration/2);
			invoke([this] {levelCompleteEnd(); }, outroDuration);
		}

		void notifyPlayers() {
			vector<GameObject*> players = GameObject::FindGameObjectsWithTag(Tag::player);
			for (GameObject* go : players) go->getComponent<Player>()->notifyEnd();
		}

		void levelCompleteEnd() {
			//delete map and players

			//if timer>0, show timer screen

			//load next level
			Scene::load("boom_scene");
		}

		void timerBonus() {
			//TIME BONUS!
			//increase score iteratively

			//show title
		}

		void gameover() {
			//...
			GameObject::Instantiate("writing_gameOver");

		}


		void forallEnemies(function<void(Enemy*)> effect) {
			vector<GameObject*> enemies = GameObject::FindGameObjectsWithTag(Tag::enemy);

			for_each(enemies.begin(), enemies.end(),
				[=](GameObject* go) { effect(go->getComponent<Enemy>()); }
			);
		}

		// ________________________________ queries



	};
}