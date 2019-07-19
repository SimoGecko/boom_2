// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Player.h"
#include "Background.h"
#include "MapBuilder.h"

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
			GameObject* manager = new GameObject("manager");
			scene.push_back(manager);
			manager->addComponent<MapBuilder>();



			//PlAYER
			GameObject* player = new GameObject("player");
			scene.push_back(player);
			player->addComponent<Player>();
			player->SetRenderable(new Renderable("player", sf::IntRect(0, 0, 32, 32), Layer::characters, 32));
			Animator* anim = player->addComponent<Animator>();
			anim->setup(&(player->renderable().sprite()), 12, { 8, 8 });
			anim->loadAnimationsFromFile("anim_boom");

			//BACKGROUND
			GameObject* background = new GameObject("background"); // temporary
			scene.push_back(background);
			background->SetRenderable(new Renderable("mockup", sf::IntRect(0, 0, 640, 480), Layer::background, 32));
			background->renderable().sprite().move(-4, -1);




			//___________________________________________
			return move(scene);
		}

	};

}