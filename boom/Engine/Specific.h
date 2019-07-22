// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// includes specific elements such as tags, layers

namespace sxg::engine {

	enum Tag {
		defaultTag = 0,

		block,
		bomb,
		bullet,
		coin,
		enemy,
		environment,
		explosion,
		extra,
		player,
		powerup,
		teleporter,
		wall,
	};

	enum Layer {
		defaultLayer = 0,
		background,
		elements,
		characters,
		effects,
		ui,
	};


}