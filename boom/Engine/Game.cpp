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
		BuildList::AddActiveScenesAndPrefabs();

		//remove from build
		sxg::boom::Tools::start();

		//start up all components and gameobjects
		Screen ::start();
		Time   ::start();
		Input  ::start();
		Audio  ::start();
		Random ::start();
		Prefabs::start();
		Scene  ::start(); // build scenes, load default one, call start on gameobjects
	}

	void Game::update() {
		//updates up all components and gameobjects
		Time   ::update();
		Input  ::update();
		Physics::update();
		Gizmos ::update();
		Scene  ::update();

		vector<GameObject*> allGo = GameObject::All(); // fix it to avoid modification
		//for (size_t i = 0; i < GameObject::All().size(); ++i) GameObject::All()[i]->update();
		for (GameObject* go : allGo) go->update();
	}

	void Game::draw() {
		// draws all renderables
		for (Renderable* renderable : Renderable::All()) {
			renderable->draw();
		}
		Font  ::draw();
		Gizmos::draw();
	}


}