// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Player.h"
#include "Background.h"

// provides the general game scene for boom

namespace sxg::boom {

	class BoomScene : public Scene {
	public:
		BoomScene(const string sceneName) : Scene(sceneName) {}
		
	private:
		// Inherited via Scene
		virtual vector<GameObject*> build() override {
			vector<GameObject*> scene;
			//build______________________________________

			//PlAYER
			GameObject* player = new GameObject("player");
			//player->addComponent<Player>(); // unresolved external for this particular one
			scene.push_back(player);

			//BACKGROUND
			GameObject* background = new GameObject("background");
			scene.push_back(background);
			//background->SetRenderable()


			//___________________________________________
			return move(scene);
		}

	};

}