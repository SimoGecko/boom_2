// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Bullet.h"

// provides the instantiatables prefabs for boom

namespace sxg::boom {

	class BoomPrefabs : public Prefabs {
	public:
		BoomPrefabs() : Prefabs() {}

	private:
		// Inherited via Scene
		vector<pair<string, GameObject*>> build() override {
			vector<pair<string, GameObject*>> prefabs;
			//build______________________________________

			//BULLET
			GameObject* bullet = new GameObject("bullet");
			prefabs.push_back({ bullet->name(), bullet });
			bullet->addComponent<Bullet>();
			//sf::Sprite bulletSprite = new sf::Sprite(Resources::Get<sf::Texture>("shot"), sf::IntRect(0, 0, 8, 8));
			bullet->SetRenderable(new Renderable("shot", sf::IntRect(0, 0, 8, 8), Layer::elements, 32, false)); // don't add the renderable to the drawlist

			//WALL
			GameObject* wall = new GameObject("wall");
			prefabs.push_back({ wall->name(), wall });
			wall->SetRenderable(new Renderable("wall", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));

			//BLOCK
			GameObject* block = new GameObject("block");
			prefabs.push_back({ block->name(), block });
			block->SetRenderable(new Renderable("block", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* blockAnim = block->addComponent<Animator>();
			blockAnim->setup(&(block->renderable().sprite()), 12, { 1, 4 });
			blockAnim->loadAnimationsFromFile("anim_block");

			// COIN
			GameObject* coin = new GameObject("coin");
			prefabs.push_back({ coin->name(), coin });
			coin->SetRenderable(new Renderable("coin", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* coinAnim = block->addComponent<Animator>();
			coinAnim->setup(&(coin->renderable().sprite()), 12, { 1, 10 });
			coinAnim->loadAnimationsFromFile("anim_coin");

			// TELEPORTER
			GameObject* teleporter = new GameObject("teleporter");
			prefabs.push_back({ teleporter->name(), teleporter });
			teleporter->SetRenderable(new Renderable("teleporter", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* teleportAnim = teleporter->addComponent<Animator>();
			teleportAnim->setup(&(block->renderable().sprite()), 12, { 1, 8 });
			teleportAnim->loadAnimationsFromFile("anim_teleporter");

			//BOMB


			//EXPLOSION


			//ENEMY
			//___________________________________________
			return move(prefabs);
		}
	};

}