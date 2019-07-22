// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

#include "../Engine.h"
#include "../BuildList.h"

// class that manages the gameloop and calls the appropriate components

namespace sxg::engine {
	class Game {
	public:
		Game();
		virtual ~Game() {};
	private:
		void run();

		void start();
		void update();
		void draw();
	};
}