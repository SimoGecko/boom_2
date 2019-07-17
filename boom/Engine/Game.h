// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Screen.h"
#include "Time.h"
#include "Renderable.h"
#include "Scene.h"

//move somewhere else
#include "../Game/boomScene.h"

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