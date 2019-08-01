// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// includes specific elements such as tags, layers

namespace sxg::engine {

	enum class Tag {
		defaultTag = 0,

		empty,
		block,
		bomb,
		bullet,
		coin,
		effect,
		enemy,
		environment,
		explosion,
		extra,
		player,
		points,
		powerup,
		teleporter,
		ui,
		wall,
	};

	enum class Layer {
		defaultLayer = 0,
		background,
		elements,
		characters,
		foreground,
		effects,
		ui,
	};


}