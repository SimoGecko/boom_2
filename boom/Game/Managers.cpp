// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "GameData.h"
#include "Coin.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Map.h"
#include "Ui.h"

// static definitions for things to be outside the class (ugly ik)

namespace sxg::boom {

	MapBuilder* MapBuilder::_instance = nullptr;
	GameData* GameData::_instance = nullptr;
	Map* Map::_instance = nullptr;
	Spawner* Spawner::_instance = nullptr;
	Ui* Ui::_instance = nullptr;

	int Coin::nCoins = 0;
	Event Coin::onAllCoinsCollected;

	int Enemy::nEnemies = 0;
	Event Enemy::onAllEnemiesDefeated;
	
}