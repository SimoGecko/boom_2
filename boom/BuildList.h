// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// the BUILD scene + prefabs list
#include "Game/BoomPrefabs.h"
#include "Game/BoomScene.h"

// lists here the scenes and prefabs to be included in the build

namespace sxg::engine {

	class BuildList {
	public:
		static void AddActiveScenesAndPrefabs() {
			new sxg::boom::BoomScene("boom_scene");
			new sxg::boom::BoomPrefabs();
		}
	};

}