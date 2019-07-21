// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// includes specific elements such as tags, layers

namespace sxg::engine {

	enum Tag {
		defaultTag = 0,
		environment,
		player,
		enemy,
		bullet,
		wall,
		block,
		coin,
		powerup,
		teleporter,
		bomb,
		explosion,
	};

	enum Layer {
		defaultLayer = 0,
		background,
		elements,
		characters,
		effects,
		ui
	};


}