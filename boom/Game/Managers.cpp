// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Score.h"
#include "Coin.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Map.h"
#include "CharacterManager.h"
// static definitions for things to be outside the class (ugly ik)

namespace sxg::boom {

	//MANAGERS
	Map* Map::_instance = nullptr;
	MapBuilder* MapBuilder::_instance = nullptr;
	GameManager* GameManager::_instance = nullptr;
	Score* Score::_instance = nullptr;
	CharacterManager* CharacterManager::_instance = nullptr;
	//points
	//UI

	//static data/events
	int Coin::nCoins = 0;
	Event Coin::onAllCoinsCollected;

	int Enemy::nEnemies = 0;
	Event Enemy::onAllEnemiesDefeated;

	//const int GameManager::instance()->nPlayers;

}