// (c) Simone Guggiari 2019
#include "Game.h"


namespace sxg::engine {
	Game::Game() {
		run();
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

		//start up all components and gameobjects
		Time::start();
		Scene::start(); // build scenes, load default one
	}

	void Game::update() {
		//updates up all components and gameobjects
		Time::update();

		// 

	}

	void Game::draw() {
		// draws all renderables
		for (Renderable* renderable : Renderable::All()) {
			renderable->draw();
		}
	}


}