// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Block.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Coin.h"
#include "Explosion.h"
#include "Teleporter.h"

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

			//BACKGROUND
			GameObject* background = new GameObject("background", Tag::environment);
			prefabs.push_back({ background->name(), background });
			background->SetRenderable(new Renderable("background", sf::IntRect(0, 0, 32, 32), Layer::background, 32, false));

			//BORDER
			GameObject* border = new GameObject("border", Tag::environment);
			prefabs.push_back({ border->name(), border });
			border->SetRenderable(new Renderable("border", sf::IntRect(0, 0, 32, 32), Layer::background, 32, false));
			Animator* borderAnim = border->addComponent<Animator>();
			borderAnim->setup(&(border->renderable().sprite()), 1, { 1,8 }, "anim_border");

			//BULLET
			GameObject* bullet = new GameObject("bullet", Tag::bullet);
			prefabs.push_back({ bullet->name(), bullet });
			bullet->addComponent<Bullet>();
			bullet->SetRenderable(new Renderable("shot", sf::IntRect(0, 0, 8, 8), Layer::effects, 32, false)); // don't add the renderable to the drawlist
			//effect

			//WALL
			GameObject* wall = new GameObject("wall", Tag::wall);
			prefabs.push_back({ wall->name(), wall });
			wall->SetRenderable(new Renderable("wall", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			//add collider

			//BLOCK
			GameObject* block = new GameObject("block", Tag::block);
			prefabs.push_back({ block->name(), block });
			block->addComponent<Block>();
			block->SetRenderable(new Renderable("block", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* blockAnim = block->addComponent<Animator>();
			blockAnim->setup(&(block->renderable().sprite()), 12, { 1, 4 }, "anim_block");

			// COIN
			GameObject* coin = new GameObject("coin", Tag::coin);
			prefabs.push_back({ coin->name(), coin });
			coin->addComponent<Coin>();
			coin->SetRenderable(new Renderable("coin", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* coinAnim = coin->addComponent<Animator>();
			coinAnim->setup(&(coin->renderable().sprite()), 12, { 1, 10 }, "anim_coin");

			// TELEPORTER
			GameObject* teleporter = new GameObject("teleporter", Tag::teleporter);
			prefabs.push_back({ teleporter->name(), teleporter });
			teleporter->addComponent<Teleporter>();
			teleporter->SetRenderable(new Renderable("teleporter", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* teleportAnim = teleporter->addComponent<Animator>();
			teleportAnim->setup(&(teleporter->renderable().sprite()), 12, { 1, 8 }, "anim_teleporter");

			//BOMB
			GameObject* bomb = new GameObject("bomb", Tag::bomb);
			prefabs.push_back({ bomb->name(), bomb });
			bomb->addComponent<Bomb>();
			bomb->SetRenderable(new Renderable("bomb", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false));
			Animator* bombAnim = bomb->addComponent<Animator>();
			bombAnim->setup(&(bomb->renderable().sprite()), 12, { 1, 3 }, "anim_bomb");


			//EXPLOSION
			GameObject* explosion = new GameObject("explosion", Tag::explosion);
			prefabs.push_back({ explosion->name(), explosion });
			explosion->addComponent<Explosion>();
			explosion->SetRenderable(new Renderable("explosion", sf::IntRect(0, 0, 32, 32), Layer::effects, 32, false));
			Animator* explosionAnim = explosion->addComponent<Animator>();
			explosionAnim->setup(&(explosion->renderable().sprite()), 36, { 4, 4 }, "anim_explosion");

			//ENEMY




			//___________________________________________
			return move(prefabs);
		}
	};

}