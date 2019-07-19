// (c) Simone Guggiari 2019
#include "Prefabs.h"


namespace sxg::engine {
	Prefabs::Prefabs() {
		_allBuilders.push_back(this);
	}

	Prefabs::~Prefabs() {
		//the static class owns all the prefabs, not the small class anymore
		//delete all prefabs
		for (auto& e : _allPrefabs) delete e.second;
		for (Prefabs* builder : _allBuilders) delete builder;
	}

	void Prefabs::start() {
		//call build on all builders
		for (Prefabs* builder : _allBuilders) {
			vector<pair<string, GameObject*>> prefabs = builder->build();
			//insert into full list
			for (auto& goPair : prefabs) {
				const string& name = goPair.first;
				GameObject* go     = goPair.second;

				if (_allPrefabs.count(name) > 0) {
					Debug::logError("Duplicate prefab name: " + name);
				}
				else {
					_allPrefabs[name] = go;
				}
			}
		}
	}

	GameObject* Prefabs::getPrefab(const string& name) {
		if (_allPrefabs.count(name) ==0) {
			Debug::logError("No prefab with name: " + name);
			return nullptr;
		}
		return _allPrefabs[name];
	}

	//static definitions
	unordered_map<string, GameObject*> Prefabs::_allPrefabs;
	vector<Prefabs*> Prefabs::_allBuilders;
}