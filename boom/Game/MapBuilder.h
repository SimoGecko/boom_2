// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

#include "Map.h"
#include "Spawner.h"

// reads the appropriate pixel subsection representing a map and instantiates the prefabs in the correct position.

namespace sxg::boom {


	class MapBuilder : public Component {
		CLONABLE(MapBuilder)
	public:
		static MapBuilder* instance() { return _instance; };

		void buildLevel(int level) {
			loadLevel(level);
		}
		

	private:
		// ________________________________ data

		const size_t W = 15;
		const size_t H = 13;
		const int maxLevel = 80;
		static MapBuilder* _instance;

		


		// ________________________________ base
		void awake() override {
			if (_instance != nullptr) Debug::logError("Multiple copies of singleton: MapBuilder");
			_instance = this;
		}

		void start() override {


		}

		void update() override {

		}

		void loadLevel(int level) {
			Debug::ensure(1 <= level && level <= maxLevel, "Invalid level index: " + to_string(level));

			setupBackgroundAndBorder();
			sf::Image levelImage = getLevelPixels(level);
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
				addBorder(r, -1, "L");
				addBorder(r, W, "R");
			}
			for (int c = 0; c < W; ++c) {
				addBorder(-1, c, "U");
				addBorder(H, c, "D");
			}
			addBorder(-1, -1, "UL");
			addBorder(H, -1, "DL");
			addBorder(-1, W, "UR");
			addBorder(H, W, "DR");
		}

		void addBorder(int r, int c, const string& anim) {
			GameObject* borderPiece = GameObject::Instantiate("border", sf::Vector2f(c, r));
			borderPiece->getComponent<Animator>()->playAnimation(anim);
		}


		void instantiateLevelPrefabs(const sf::Image& levelImage) {
			auto& tagsMap = Map::instance()->tagsMap;
			auto& startPos = Spawner::instance()->startPos;

			tagsMap.resize(H);
			for (size_t r = 0; r < H; ++r) {
				tagsMap[r].resize(W);
				for (size_t c = 0; c < W; ++c) {

					sf::Color pxColor = levelImage.getPixel(c, r);
					const string& prefabName = prefabNameFromColor(pxColor);
					sf::Vector2i position(c, r);

					tagsMap[r][c] = Tag::empty; // default

					//instantiate prefab
					if (doInstantiate(prefabName)) {

						GameObject* newGO = GameObject::Instantiate(prefabName, to_v2f(position));

						//setup tag
						if (setupTag(prefabName)) {
							tagsMap[r][c] = newGO->tag();
						}
					}
					if (addToStartPos(prefabName)) {
						startPos[prefabName].push_back(position);
					}
				}
			}
		}



		

		// ________________________________ queries
		sf::Image getLevelPixels(int level) {
			const sf::Image levelsImage = Resources::Get<sf::Image>("levels");

			sf::Image levelImage;
			levelImage.create(W, H);
			int startX = ((level - 1) % 10) * 32 + 9;
			int startY = ((level - 1) / 10) * 32 + 10;

			levelImage.copy(levelsImage, 0, 0, sf::IntRect(startX, startY, W, H));
			return move(levelImage);
		}


		const string prefabNameFromColor(const sf::Color color) {
			if (color == sf::Color(255, 255, 255)) return "empty";		// white
			if (color == sf::Color(172, 172, 172)) return "block";		// light grey
			if (color == sf::Color( 68,  68,  68)) return "wall";		// dark grey
			if (color == sf::Color(  0,   0,   0)) return "border";		// black
			if (color == sf::Color(207,  61,  61)) return "enemy";		// red
			if (color == sf::Color( 69, 141, 208)) return "player";		// blue
			if (color == sf::Color( 61, 207, 126)) return "teleporter";	// green
			if (color == sf::Color(214, 202,  73)) return "coin";		// yellow

			Debug::logError("MapBuilder queried prefab name with incorrect color");
			return "";
		}



		bool doInstantiate(const string& s) {
			return s == "block" || s == "wall" || s == "coin" || s == "teleporter"; // || s == "player"
			// not: empty, border
		}
		bool setupTag(const string& s) { // static elements that don't move
			return s == "block" || s == "wall";// || s == "coin" || s == "teleporter";
		}
		bool addToStartPos(const string& s) {
			return s == "player" || s == "enemy";
		}
	};
}