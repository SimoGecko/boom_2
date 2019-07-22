// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Block.h"
// reads the appropriate pixel subsection representing a map and instantiates the prefabs in the correct position.

namespace sxg::boom {


	class MapBuilder : public Component {
		CLONABLE(MapBuilder)
	public:
		static MapBuilder* instance;
		void explosionAt(sf::Vector2i position) {
			int r = position.y;
			int c = position.x;
			//destroy block
			if (isValid(position) && mapObjects[r][c] != nullptr && mapObjects[r][c]->tag() == Tag::block) {
				mapObjects[r][c]->getComponent<Block>()->breakBlock();
				mapObjects[r][c] = nullptr;
			}
		}

		bool isValidExplosionPlace(sf::Vector2i pos) {
			int r = pos.y, c = pos.x;
			return isValid(pos) && (mapObjects[r][c] == nullptr || isExplodableTag(mapObjects[r][c]->tag()));
		}

		bool isWalkable(sf::Vector2i pos) {
			int r = pos.y, c = pos.x;
			return isValid(pos) && (mapObjects[r][c] == nullptr || isWalkableTag(mapObjects[r][c]->tag()));
		}

		void removeGo(sf::Vector2i position) {
			mapObjects[position.y][position.x] = nullptr;
		}

	private:
		// ________________________________ data
		const int startLevel = 19;

		const size_t W = 15;
		const size_t H = 13;
		const int maxLevel = 80;
		unordered_map<int, string> prefabNamesMap;
		vector<vector<GameObject*>> mapObjects;


		// ________________________________ base
		void start() override {
			if (instance != nullptr) Debug::logError("Multiple copies of singleton: MapBuilder");
			instance = this;

			buildPrefabMap();
			loadLevel(startLevel);
		}

		void update() override {

		}

		void loadLevel(int level) {
			Debug::ensure(1 <= level && level <= maxLevel, "Invalid level index: " + to_string(level));

			//0. create background and border
			setupBackgroundAndBorder();

			//1. get pixel subsection
			sf::Image levelImage = getLevelPixels(level);

			//2. iterate instantiating right prefabs
			instantiateLevelPrefabs(levelImage);

		}
		

		// ________________________________ commands
		void setupBackgroundAndBorder() {
			//background
			for (int r = 0; r < H; ++r) {
				for (int c = 0; c < W; ++c) {
					GameObject::Instantiate("background", sf::Vector2f(c,r));
				}
			}
			//border
			for (int r = 0; r < H; ++r) {
				GameObject::Instantiate("border", sf::Vector2f(-1,r ))->getComponent<Animator>()->playAnimation("L");
				GameObject::Instantiate("border", sf::Vector2f(W, r ))->getComponent<Animator>()->playAnimation("R");
			}
			for (int c = 0; c < W; ++c) {
				GameObject::Instantiate("border", sf::Vector2f(c, -1 ))->getComponent<Animator>()->playAnimation("U");
				GameObject::Instantiate("border", sf::Vector2f(c,  H ))->getComponent<Animator>()->playAnimation("D");
			}
			GameObject::Instantiate("border", sf::Vector2f(-1, -1))->getComponent<Animator>()->playAnimation("UL");
			GameObject::Instantiate("border", sf::Vector2f(-1, H))->getComponent<Animator>()->playAnimation("DL");
			GameObject::Instantiate("border", sf::Vector2f(W, -1))->getComponent<Animator>()->playAnimation("UR");
			GameObject::Instantiate("border", sf::Vector2f(W, H ))->getComponent<Animator>()->playAnimation("DR");
		}

		void buildPrefabMap() {
			prefabNamesMap[sf::Color(255, 255, 255).toInteger()] = "empty";		// white
			prefabNamesMap[sf::Color(172, 172, 172).toInteger()] = "block";		// light grey
			prefabNamesMap[sf::Color( 68,  68,  68).toInteger()] = "wall";		// dark grey
			prefabNamesMap[sf::Color(  0,   0,   0).toInteger()] = "border";	// black
			prefabNamesMap[sf::Color(207,  61,  61).toInteger()] = "enemy";		// red
			prefabNamesMap[sf::Color( 69, 141, 208).toInteger()] = "player";	// blue
			prefabNamesMap[sf::Color( 61, 207, 126).toInteger()] = "teleporter";// green
			prefabNamesMap[sf::Color(214, 202,  73).toInteger()] = "coin";		// yellow
		}

		bool doInstantiate(const string& s) {
			return s == "block" || s == "wall" || s == "coin" || s == "teleporter";
		}

		void instantiateLevelPrefabs(const sf::Image& levelImage) {
			mapObjects.resize(H);
			for (size_t r = 0; r < H; ++r) {
				mapObjects[r].resize(W);
				for (size_t c = 0; c < W; ++c) {
					sf::Color pxColor = levelImage.getPixel(c, r);
					const string& prefabName = prefabNameFromColor(pxColor);
					sf::Vector2f position((float)c, (float)r);
					//instantiate prefab
					if (doInstantiate(prefabName)) {
						mapObjects[r][c] = GameObject::Instantiate(prefabName, position);
					}
					else {
						mapObjects[r][c] = nullptr;
					}
				}
			}
		}

		// ________________________________ queries
		sf::Image getLevelPixels(int level) {
			//1.load image
			const sf::Image levelsImage = Resources::Get<sf::Image>("levels");

			//2. cutout right portion
			sf::Image levelImage;
			levelImage.create(W, H);
			int startPxLeft = ((level - 1) % 10) * 32 + 9;
			int startPxUp = ((level - 1) / 10) * 32 + 10;

			levelImage.copy(levelsImage, 0, 0, sf::IntRect(startPxLeft, startPxUp, W, H));
			return move(levelImage);
		}



		const string& prefabNameFromColor(const sf::Color color) {
			if (prefabNamesMap.count(color.toInteger()) == 0) {
				Debug::logError("MapBuilder queried prefab name with incorrect color");
				return emptyString;
			}
			return prefabNamesMap[color.toInteger()];
		}

		bool isValid(sf::Vector2i pos) {
			int r = pos.y, c = pos.x;
			return (0 <= c && c < W && 0 <= r && r < H);
		}

		//shouldn't have player or enemy
		bool isWalkableTag(int objectTag) {
			return objectTag == Tag::teleporter || objectTag == Tag::coin || objectTag == Tag::enemy;
		}
		bool isExplodableTag(int objectTag) {
			return objectTag == Tag::block || objectTag == Tag::teleporter || objectTag == Tag::coin || objectTag == Tag::enemy;
		}


	};
}