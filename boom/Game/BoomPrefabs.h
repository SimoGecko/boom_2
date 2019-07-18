// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Bullet.h"

// provides the instantiatables prefabs for boom

namespace sxg::boom {

	class BoomPrefabs : public Prefabs {
	public:
		BoomPrefabs() : Prefabs() {}

	private:
		// Inherited via Scene
		vector<pair<string, GameObject*>> build() override {
			vector<pair<string, GameObject*>> prefabs;
			Debug::Log("building boom prefabs...");
			//build______________________________________

			//BULLET
			GameObject* bullet = new GameObject("bullet");
			prefabs.push_back({bullet->name(), bullet });
			bullet->addComponent<Bullet>();
			sf::Sprite bulletSprite(Resources::Get<sf::Texture>("shot"), sf::IntRect(0, 0, 8, 8));
			bullet->SetRenderable(new Renderable(bulletSprite, 2, 32, false)); // don't add the renderable to the drawlist

			//___________________________________________
			Debug::Log("...done building boom prefabs");
			return move(prefabs);
		}
	};

}