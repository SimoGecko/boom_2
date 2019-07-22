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
#include "Powerup.h"
#include "Extra.h"

// provides the instantiatables prefabs for boom

namespace sxg::boom {


	class BoomPrefabs : public Prefabs {
	public:
		BoomPrefabs() : Prefabs() {}

	private:
		// Inherited via Scene
		vector<GameObject*> build() override {
			vector<GameObject*> prefabs;
			//build______________________________________

			//BACKGROUND
			{
				GameObject* background = new GameObject("background", Tag::environment);
				prefabs.push_back(background);
				background->addRenderable("background", sf::IntRect(0, 0, 32, 32), Layer::background, 32, false);
			}

			//BLOCK
			{
				GameObject* block = new GameObject("block", Tag::block);
				prefabs.push_back(block);
				block->addComponent<Block>();
				block->addRenderable("block", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* blockAnim = block->addComponent<Animator>();
				blockAnim->setup(&(block->renderable().sprite()), 12, { 1, 4 }, "anim_block");
			}

			//BOMB
			{
				GameObject* bomb = new GameObject("bomb", Tag::bomb);
				prefabs.push_back(bomb);
				bomb->addComponent<Bomb>();
				bomb->addRenderable("bomb", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* bombAnim = bomb->addComponent<Animator>();
				bombAnim->setup(&(bomb->renderable().sprite()), 12, { 1, 3 }, "anim_bomb");
				//bomb->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			//BORDER
			{
				GameObject* border = new GameObject("border", Tag::environment);
				prefabs.push_back(border);
				border->addRenderable("border", sf::IntRect(0, 0, 32, 32), Layer::background, 32, false);
				Animator* borderAnim = border->addComponent<Animator>();
				borderAnim->setup(&(border->renderable().sprite()), 1, { 1,8 }, "anim_border");
			}

			//BULLET
			{
				GameObject* bullet = new GameObject("bullet", Tag::bullet);
				prefabs.push_back(bullet);
				bullet->addComponent<Bullet>();
				bullet->addRenderable("shot", sf::IntRect(0, 0, 8, 8), Layer::effects, 32, false); // don't add the renderable to the drawlist
				bullet->addComponent<CircleCollider>()->setRadius(0.1f);
				//effect
			}

			// COIN
			{
				GameObject* coin = new GameObject("coin", Tag::coin);
				prefabs.push_back(coin);
				coin->addComponent<Coin>();
				coin->addRenderable("coin", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* coinAnim = coin->addComponent<Animator>();
				coinAnim->setup(&(coin->renderable().sprite()), 24, { 1, 10 }, "anim_coin");
				coin->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			//ENEMY
			{

			}

			//EXPLOSION
			{
				GameObject* explosion = new GameObject("explosion", Tag::explosion);
				prefabs.push_back(explosion);
				explosion->addComponent<Explosion>();
				explosion->addRenderable("explosion", sf::IntRect(0, 0, 32, 32), Layer::effects, 32, false);
				Animator* explosionAnim = explosion->addComponent<Animator>();
				explosionAnim->setup(&(explosion->renderable().sprite()), 48, { 3, 4 }, "anim_explosion");
				explosion->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// EXTRA 
			{
				GameObject* extra = new GameObject("extra", Tag::extra);
				prefabs.push_back(extra);
				extra->addComponent<Extra>();
				extra->addRenderable("extra", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* extraAnim = extra->addComponent<Animator>();
				extraAnim->setup(&(extra->renderable().sprite()), 12, { 5, 4 }, "anim_extra");
				extra->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// POWERUP
			{
				GameObject* powerup = new GameObject("powerup", Tag::powerup);
				prefabs.push_back(powerup);
				powerup->addComponent<Powerup>();
				powerup->addRenderable("bonus", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* powerupAnim = powerup->addComponent<Animator>();
				powerupAnim->setup(&(powerup->renderable().sprite()), 12, { 1, 9 }, "anim_bonus");
				powerup->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// TELEPORTER
			{
				GameObject* teleporter = new GameObject("teleporter", Tag::teleporter);
				prefabs.push_back(teleporter);
				teleporter->addComponent<Teleporter>();
				teleporter->addRenderable("teleporter", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* teleportAnim = teleporter->addComponent<Animator>();
				teleportAnim->setup(&(teleporter->renderable().sprite()), 12, { 1, 8 }, "anim_teleporter");
				teleporter->addComponent<CircleCollider>()->setRadius(0.1f);
			}

			//WALL
			{
				GameObject* wall = new GameObject("wall", Tag::wall);
				prefabs.push_back(wall);
				wall->addRenderable("wall", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				//add collider
			}


			//___________________________________________
			return move(prefabs);
		}
	};
}