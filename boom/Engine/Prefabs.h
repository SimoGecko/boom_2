// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// provides access to pre-build gameobjects for easy cloning and instantiation in the scene

namespace sxg::engine {
	class GameObject; // forward decl

	class Prefabs {
	public:
		virtual vector<GameObject*> build() = 0; // this has to be implemented by each

	protected:
		Prefabs(const string& name);

	private:
		static unordered_map<string, GameObject*> _allPrefabs;

	};

}