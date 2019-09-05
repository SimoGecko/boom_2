// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "MapBuilder.h"
#include "Map.h"
#include "Ui.h"
#include "GameData.h"
#include "GameManager.h"
#include "Spawner.h"

// provides the general game scene for boom

namespace sxg::boom {

	class BoomScene : public Scene {
	public:
		BoomScene(const string& sceneName) : Scene(sceneName) {}

	private:
		// Inherited via Scene
		vector<GameObject*> build() override {
			vector<GameObject*> scene;
			//build______________________________________

			// MANAGER
			{
				GameObject* manager = new GameObject("manager");
				scene.push_back(manager);
				manager->addComponent<GameManager>();
				manager->addComponent<GameData>();
				manager->addComponent<MapBuilder>();
				manager->addComponent<Map>();
				manager->addComponent<Spawner>();
				manager->addComponent<Ui>();
			}

			

			//BACKGROUND
			{
				GameObject* background = new GameObject("background");
				scene.push_back(background);
				background->addRenderable("background/panel", sf::IntRect(0, 0, 96, 480), Layer::background, 32, true);
				background->renderable().sprite().move(-4, -1);
			}



			//___________________________________________
			return move(scene);
		}

	};

}