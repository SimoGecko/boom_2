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
			Debug::Log("building boom scene...");
			//build______________________________________

			//PlAYER
			GameObject* player = new GameObject("player");
			player->addComponent<Player>(); // unresolved external for this particular one
			scene.push_back(player);
			//const sf::Texture& playertex = Resources::Get<sf::Texture>("player"); // ERROR:
			//an internal OpenGL call failed in Texture.cpp(98)
			sf::Texture* playertex = new sf::Texture();
			playertex->loadFromFile("Assets/Images/player.png");
			sf::Sprite playerSprite(*playertex, sf::IntRect(0, 0, 32, 32));
			player->SetRenderable(new Renderable(playerSprite, 1, 32));


			//BACKGROUND
			GameObject* background = new GameObject("background");
			scene.push_back(background);
			sf::Texture* backgroundtex = new sf::Texture();
			backgroundtex->loadFromFile("Assets/Images/mockup.png");
			sf::Sprite backgroundSprite(*backgroundtex, sf::IntRect(0, 0, 640, 480));
			backgroundSprite.move(-4, -1);
			background->SetRenderable(new Renderable(backgroundSprite, -1, 32));



			//___________________________________________
			Debug::Log("...done building boom scene");
			return move(scene);
		}

	};

}