// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
//#include "GameObject.h"

// provides access to pre-build gameobjects for easy cloning and instantiation in the scene

namespace sxg::engine {

	class GameObject; // forward decl

	class Prefabs {
	public:
		Prefabs();
		virtual ~Prefabs();

		static void start();
		static GameObject* getPrefab(const string& prefabName);

	protected:
		virtual vector<pair<string, GameObject*>> build() = 0; // this has to be implemented by each

	private:
		static unordered_map<string, GameObject*> _allPrefabs;
		static vector<Prefabs*> _allBuilders;
	};

}