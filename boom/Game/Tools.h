// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// code used offline for various tools, not needed in the game

namespace sxg::boom {

	class Tools {

	public:


		static void modifyAllEnemies() {
			string filePath = "Assets/Images/originalboom/characters/modified/";
			vector<string> files = { "Alien Frames", "Ghost", "Giggler", "Gunner", "Lizzy", "Sarge", "Skully", "Smoulder", "Soldier", "Taur", "Thing" };
			//vector<string> files = { "Ghost" };

			for (string file : files) {
				//load
				sf::Image enemyImage;
				enemyImage.loadFromFile(filePath + file + ".png");
				//call
				sf::Image modified = makeRightEnemy(enemyImage);
				//save
				modified.saveToFile(filePath + "modified_" + file + ".png");
			}
		}

		static sf::Image makeRightEnemy(sf::Image original) {
			//352x64
			sf::Image result;
			result.create(5 * 32, 5 * 32, sf::Color::Transparent);
			//4x4 move
			//rxc format
			copy(original, result, { 0, 0 }, { 0, 0 }, { 1, 4 });
			copy(original, result, { 1, 0 }, { 0, 4 }, { 1, 4 });
			copy(original, result, { 2, 0 }, { 0, 8 }, { 1, 3 });
			copy(original, result, { 2, 3 }, { 1, 0 }, { 1, 1 });
			copy(original, result, { 3, 0 }, { 1, 1 }, { 1, 4 });


			//4 attack
			copy(original, result, { 0, 4 }, { 1, 5 }, { 1, 1 });
			copy(original, result, { 1, 4 }, { 1, 6 }, { 1, 1 });
			copy(original, result, { 2, 4 }, { 1, 7 }, { 1, 1 });
			copy(original, result, { 3, 4 }, { 1, 8 }, { 1, 1 });

			//die
			copy(original, result, { 4, 0 }, { 1, 9 }, { 1, 2 });

			return result;
		}

		static void copy(sf::Image& src, sf::Image& dest, sf::Vector2i pos, sf::Vector2i org, sf::Vector2i size) {
			dest.copy(src, pos.y*32, pos.x*32, sf::IntRect(org.y * 32, org.x * 32, size.y * 32, size.x * 32));
		}

	};
}