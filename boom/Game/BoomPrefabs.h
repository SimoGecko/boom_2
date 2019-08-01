// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

//SCRIPTS
#include "Block.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Coin.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Extra.h"
#include "Flash.h"
#include "Player.h"
#include "Points.h"
#include "Powerup.h"
#include "Teleporter.h"
#include "Title.h"

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

			// ___________________________________ ENVIRONMENT

			const string environment = "_2";

			//BACKGROUND
			{
				GameObject* background = new GameObject("background", Tag::environment);
				prefabs.push_back(background);
				background->addRenderable("background/background" + environment, sf::IntRect(0, 0, 32, 32), Layer::background, 32, false);
			}

			//BORDER
			{
				GameObject* border = new GameObject("border", Tag::environment);
				prefabs.push_back(border);
				border->addRenderable("background/border" + environment, sf::IntRect(0, 0, 32, 32), Layer::background, 32, false);
				Animator* borderAnim = border->addComponent<Animator>();
				borderAnim->setup(&(border->renderable().sprite()), 1, { 1,8 }, "anim/border");
			}

			//BLOCK
			{
				GameObject* block = new GameObject("block", Tag::block);
				prefabs.push_back(block);
				block->addComponent<Block>();
				block->addRenderable("blocks/block" + environment, sf::IntRect(0, 0, 32, 32), Layer::foreground, 32, false);
				Animator* blockAnim = block->addComponent<Animator>();
				blockAnim->setup(&(block->renderable().sprite()), 8, { 1, 4 }, "anim/block");
				block->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			//WALL
			{
				GameObject* wall = new GameObject("wall", Tag::wall);
				prefabs.push_back(wall);
				wall->addRenderable("blocks/wall" + environment, sf::IntRect(0, 0, 32, 32), Layer::foreground, 32, false);
				//add collider -> or not
			}

			// ___________________________________ ELEMENTS


			//BOMB
			{
				GameObject* bomb = new GameObject("bomb", Tag::bomb);
				prefabs.push_back(bomb);
				bomb->addComponent<Bomb>();
				bomb->addRenderable("elements/bomb", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* bombAnim = bomb->addComponent<Animator>();
				bombAnim->setup(&(bomb->renderable().sprite()), 12, { 1, 3 }, "anim/bomb");
				bomb->addComponent<CircleCollider>()->setRadius(0.5f);
			}





			//EXPLOSION
			{
				GameObject* explosion = new GameObject("explosion", Tag::explosion);
				prefabs.push_back(explosion);
				explosion->addComponent<Explosion>();
				explosion->addRenderable("elements/explosion", sf::IntRect(0, 0, 32, 32), Layer::effects, 32, false);
				Animator* explosionAnim = explosion->addComponent<Animator>();
				explosionAnim->setup(&(explosion->renderable().sprite()), 48, { 3, 4 }, "anim/explosion");
				explosion->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// TELEPORTER
			{
				GameObject* teleporter = new GameObject("teleporter", Tag::teleporter);
				prefabs.push_back(teleporter);
				teleporter->addComponent<Teleporter>();
				teleporter->addRenderable("elements/teleporter", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* teleportAnim = teleporter->addComponent<Animator>();
				teleportAnim->setup(&(teleporter->renderable().sprite()), 12, { 1, 8 }, "anim/teleporter");
				teleporter->addComponent<CircleCollider>()->setRadius(0.1f);
			}
			

			// ___________________________________ UI

			//HEART
			{
				GameObject* heart = new GameObject("heart", Tag::ui);
				prefabs.push_back(heart);
				heart->addRenderable("ui/heart", sf::IntRect(0, 0, 16, 16), Layer::ui, 32, false);
				Animator* heartAnim = heart->addComponent<Animator>();
				heartAnim->setup(&(heart->renderable().sprite()), 1, { 1, 3 }, "anim/heart");
			}

			//HEAD
			{
				GameObject* head = new GameObject("head", Tag::ui);
				prefabs.push_back(head);
				head->addRenderable("ui/playerheads", sf::IntRect(0, 0, 16, 16), Layer::ui, 32, false);
				Animator* headAnim = head->addComponent<Animator>();
				headAnim->setup(&(head->renderable().sprite()), 1, { 1, 2 }, "anim/heads");
			}
			//EXTRA ICONS
			{
				GameObject* extraIcon = new GameObject("extraIcon", Tag::ui);
				prefabs.push_back(extraIcon);
				extraIcon->addRenderable("ui/extra_icons", sf::IntRect(0, 0, 16, 16), Layer::ui, 32, false);
				Animator* extraIconAnim = extraIcon->addComponent<Animator>();
				extraIconAnim->setup(&(extraIcon->renderable().sprite()), 1, { 1, 6 }, "anim/extra_icons");
			}
			//POWERUP ICONS
			{
				GameObject* powerupIcon = new GameObject("powerupIcon", Tag::ui);
				prefabs.push_back(powerupIcon);
				powerupIcon->addRenderable("ui/powerup_icons", sf::IntRect(0, 0, 16, 16), Layer::ui, 32, false);
				Animator* powerupIconAnim = powerupIcon->addComponent<Animator>();
				powerupIconAnim->setup(&(powerupIcon->renderable().sprite()), 1, { 2, 5 }, "anim/powerup_icons");
			}
			
			//BLACK CORNER
			{
				GameObject* blackBg = new GameObject("level_blackbg", Tag::ui);
				prefabs.push_back(blackBg);
				blackBg->addRenderable("ui/corner_black", sf::IntRect(0, 0, 32, 32), Layer::ui, 32, false);
			}

			//TITLES
			{
				{ // hurry up
					GameObject* hurryUp = new GameObject("writing_hurryUp", Tag::ui);
					prefabs.push_back(hurryUp);
					hurryUp->addRenderable("text/writing_hurryup", sf::IntRect(0, 0, 160, 32), Layer::ui, 32, false);
					hurryUp->addComponent<Title>();
				}
				{ // extra game
					GameObject* extraGame = new GameObject("writing_extraGame", Tag::ui);
					prefabs.push_back(extraGame);
					extraGame->addRenderable("text/writing_extragame", sf::IntRect(0, 0, 224, 160), Layer::ui, 32, false);
					extraGame->addComponent<Title>();
				}
				{ // game over
					GameObject* gameOver = new GameObject("writing_gameOver", Tag::ui);
					prefabs.push_back(gameOver);
					gameOver->addRenderable("text/writing_gameover", sf::IntRect(0, 0, 320, 64), Layer::ui, 32, false);
					gameOver->addComponent<Title>();
				}
				
			}

			// ___________________________________ CHARACTERS

			//PlAYER
			{
				GameObject* player = new GameObject("player", Tag::player);
				prefabs.push_back(player);
				player->addComponent<Player>();
				player->addRenderable("player/player_1", sf::IntRect(0, 0, 32, 32), Layer::characters, 32, false);
				sf::Sprite* playerSprite = &(player->renderable().sprite());
				Animator* anim = player->addComponent<Animator>();
				anim->setup(playerSprite, 12, { 5, 8 }, "anim/player");
				player->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			//ENEMY
			{
				GameObject* enemyGo = new GameObject("enemy", Tag::enemy);
				prefabs.push_back(enemyGo);
				enemyGo->addComponent<Enemy>();
				enemyGo->addRenderable("enemies/amoeba", sf::IntRect(0, 0, 32, 32), Layer::characters, 32, false);
				Animator* anim = enemyGo->addComponent<Animator>();
				anim->setup(&(enemyGo->renderable().sprite()), 8, { 5,5 }, "anim/enemy");
				enemyGo->addComponent<CircleCollider>()->setRadius(0.5f);
				/*
				{
					GameObject* sarge = enemyGo->clone();
					prefabs.push_back(sarge);
					sarge->setName("sarge");
					sarge->getComponent<Enemy>()->setup(Enemy::Type::sarge);
				}
				*/
			}

			// ___________________________________ COLLECTIBLES


			// POWERUP
			{
				GameObject* powerup = new GameObject("powerup", Tag::powerup);
				prefabs.push_back(powerup);
				powerup->addComponent<Powerup>();
				powerup->addRenderable("elements/powerup", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* powerupAnim = powerup->addComponent<Animator>();
				powerupAnim->setup(&(powerup->renderable().sprite()), 1, { 1, 9 }, "anim/powerup", false);
				powerup->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// EXTRA 
			{
				GameObject* extra = new GameObject("extra", Tag::extra);
				prefabs.push_back(extra);
				extra->addComponent<Extra>();
				extra->addRenderable("elements/extra", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* extraAnim = extra->addComponent<Animator>();
				extraAnim->setup(&(extra->renderable().sprite()), 12, { 5, 4 }, "anim/extra", false);
				extra->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// COIN
			{
				GameObject* coin = new GameObject("coin", Tag::coin);
				prefabs.push_back(coin);
				coin->addComponent<Coin>();
				coin->addRenderable("elements/coin", sf::IntRect(0, 0, 32, 32), Layer::elements, 32, false);
				Animator* coinAnim = coin->addComponent<Animator>();
				coinAnim->setup(&(coin->renderable().sprite()), 24, { 1, 10 }, "anim/coin");
				coin->addComponent<CircleCollider>()->setRadius(0.5f);
			}

			// POINTS
			{
				GameObject* points = new GameObject("points", Tag::points);
				prefabs.push_back(points);
				points->addComponent<Points>();
				points->addRenderable("text/points_all", sf::IntRect(0, 0, 32, 16), Layer::effects, 32, false);
				Animator* pointsAnim = points->addComponent<Animator>();
				pointsAnim->setup(&(points->renderable().sprite()), 1, { 1, 13 }, "anim/points");
			}


			// ___________________________________ EFFECTS

			// FLASH
			{
				GameObject* flash = new GameObject("flash", Tag::effect);
				prefabs.push_back(flash);
				flash->addRenderable("effects/flash", sf::IntRect(0, 0, 32, 32), Layer::effects, 32, false);
				flash->addComponent<Flash>();
				Animator* anim = flash->addComponent<Animator>();
				anim->setup(&(flash->renderable().sprite()), 12, { 1, 4 }, "anim/flash");
			}
			// SHIELD
			{
				GameObject* shield = new GameObject("shield", Tag::effect);
				prefabs.push_back(shield);
				shield->addRenderable("player/shield", sf::IntRect(0, 0, 32, 32), Layer::effects, 32, false);
				shield->addComponent<Shield>();
				Animator* anim = shield->addComponent<Animator>();
				anim->setup(&(shield->renderable().sprite()), 1, { 1, 4 }, "anim/shield");
			}

			//BULLET
			{
				GameObject* bullet = new GameObject("bullet", Tag::bullet);
				prefabs.push_back(bullet);
				bullet->addComponent<Bullet>();
				bullet->addRenderable("effects/shot", sf::IntRect(0, 0, 8, 8), Layer::effects, 32, false); // don't add the renderable to the drawlist
				bullet->addComponent<CircleCollider>()->setRadius(0.1f);
				//effect = animator
			}

			


			//___________________________________________
			return move(prefabs);
		}
	};
}