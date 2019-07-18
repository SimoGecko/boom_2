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
		BoomScene(const string& sceneName) : Scene(sceneName) {}
		
	private:
		// Inherited via Scene
		vector<GameObject*> build() override {
			vector<GameObject*> scene;
			Debug::Log("building boom scene...");
			//build______________________________________

			//PlAYER
			GameObject* player = new GameObject("player");
			scene.push_back(player);
			player->addComponent<Player>(); // unresolved external for this particular one
			//const sf::Texture& playertex = ; // ERROR:
			//an internal OpenGL call failed in Texture.cpp(98)
			//sf::Texture* playertex = new sf::Texture();
			//playertex->loadFromFile("Assets/Images/player.png");
			sf::Sprite playerSprite(Resources::Get<sf::Texture>("player"), sf::IntRect(0, 0, 32, 32));
			player->SetRenderable(new Renderable(playerSprite, 1, 32));

			Animator* anim = player->addComponent<Animator>();
			//Animator* anim = player->getComponent<Animator>();
			if (anim != nullptr) {
				anim->setup(&playerSprite, 12, 8, 8);
				anim->addAnimation("front", { 0,0 }, 8);
			}

			//BACKGROUND
			GameObject* background = new GameObject("background");
			scene.push_back(background);
			//sf::Texture* backgroundtex = new sf::Texture();
			//backgroundtex->loadFromFile("Assets/Images/mockup.png");
			sf::Sprite backgroundSprite(Resources::Get<sf::Texture>("mockup"), sf::IntRect(0, 0, 640, 480));
			backgroundSprite.move(-4, -1);
			background->SetRenderable(new Renderable(backgroundSprite, -1, 32));


			//___________________________________________
			Debug::Log("...done building boom scene");
			return move(scene);
		}

	};

}