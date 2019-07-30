// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Score.h"
#include "Coin.h"
#include "Enemy.h"
#include "GameManager.h"

// static definitions for things to be outside the class (ugly ik)

namespace sxg::boom {

	MapBuilder* MapBuilder::instance = nullptr;
	Score* Score::instance = nullptr;

	int Coin::nCoins = 0;
	Event Coin::onAllCoinsCollected;

	int Enemy::nEnemies = 0;
	Event Enemy::onAllEnemiesDefeated;
	
	const int GameManager::nPlayers;

}