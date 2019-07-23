// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "MapBuilder.h"
#include "Coin.h"

// static definitions for things to be outside the class

namespace sxg::boom {

	MapBuilder* MapBuilder::instance = nullptr;

	int Coin::nCoins = 0;
}