// (c) Simone Guggiari 2019
#include "Game.h"


namespace sxg::engine {
	Game::Game() {
		run(); // keep it in ctor?
	}

	void Game::run() {
		//the game loop

		start();

		while (Screen::window().isOpen()) {
			int numRepetitions = Time::nLoopRepetitions();

			while (numRepetitions--) { // still has time in the accumulator

				//poll event
				sf::Event event;
				while (Screen::window().pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						Screen::window().close();
					}
				}

				update();
			}

			Screen::window().clear();
			draw();
			Screen::window().display();

		}
	}

	void Game::start() {
		//create prefabs and scenes
		new sxg::boom::BoomScene("boom_scene");
		new sxg::boom::BoomPrefabs();

		//start up all components and gameobjects
		Screen ::start();
		Prefabs::start();
		Scene  ::start(); // build scenes, load default one
		Time   ::start();
		Input  ::start();

		//for (GameObject* go : GameObject::All()) go->start();
		for (size_t i = 0; i < GameObject::All().size(); ++i) GameObject::All()[i]->start();
	}

	void Game::update() {
		//updates up all components and gameobjects
		Time ::update();
		Input::update();

		//for (GameObject* go : GameObject::All()) go->update();
		for (size_t i = 0; i < GameObject::All().size(); ++i) GameObject::All()[i]->update();
	}

	void Game::draw() {
		// draws all renderables
		for (Renderable* renderable : Renderable::All()) {
			renderable->draw();
		}
	}


}