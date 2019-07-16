// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// __DESCRIPTION__

namespace sxg::boom {

	class BoomScene : public Scene {
	protected:
		BoomScene(const string& sceneName) : Scene(sceneName) {}
		
	private:


		// Inherited via Scene
		virtual vector<GameObject*> build() override {
			vector<GameObject*> scene;
			//build

			Debug::Log("building the scene..");


			return move(scene);
		}

	};

}