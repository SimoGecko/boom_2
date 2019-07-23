// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Player.h"
#include "MapBuilder.h"
#include "Ui.h"
#include "Tools.h"

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
				manager->addComponent<MapBuilder>();
				manager->addComponent<Ui>();
			}

			

			//BACKGROUND
			{
				GameObject* background = new GameObject("background");
				scene.push_back(background);
				background->addRenderable("panel", sf::IntRect(0, 0, 96, 480), Layer::background, 32, true);
				background->renderable().sprite().move(-4, -1);
			}



			//___________________________________________
			return move(scene);
		}

	};

}