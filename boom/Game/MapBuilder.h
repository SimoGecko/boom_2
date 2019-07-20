// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// reads the appropriate pixel subsection representing a map and instantiates the prefabs in the correct position.

namespace sxg::boom {

	class MapBuilder : public Component {
	private:
		// ______________ members
		const size_t width  = 15;
		const size_t height = 13;
		const int maxLevel = 80;
		unordered_map<int, string> prefabNamesMap;
		vector<vector<GameObject*>> mapObjects;

	public:
		// ______________ base
		void start() override {
			buildPrefabMap();
			loadLevel(35);
		}

		void update() override {

		}

		void loadLevel(int level) {
			Debug::ensure(1 <= level && level <= maxLevel, "Invalid level index: " + to_string(level));

			//0. create background and border

			//1. get pixel subsection
			sf::Image levelImage = getLevelPixels(level);

			//2. iterate instantiating right prefabs
			mapObjects.resize(width); mapObjects[0].resize(height);

			for (size_t r = 0; r < height; ++r) {
				for (size_t c = 0; c < width; ++c) {
					//get color
					sf::Color pxColor = levelImage.getPixel(c, r);
					//find name of prefab
					const string& prefabName = prefabNameFromColor(pxColor);
					//compute position
					vector2 position((float)c, (float)r);

					//instantiate prefab
					if (doInstantiate(prefabName)) {
						/*mapObjects[c][r] =*/ GameObject::Instantiate(prefabName, position);
					}
				}
			}
		}
		
	private:
		// ______________ commands
		void buildPrefabMap() {
			prefabNamesMap[sf::Color(255, 255, 255).toInteger()] = "empty";		// white
			prefabNamesMap[sf::Color(172, 172, 172).toInteger()] = "block";		// light grey
			prefabNamesMap[sf::Color( 68,  68,  68).toInteger()] = "wall";		// dark grey
			prefabNamesMap[sf::Color(  0,   0,   0).toInteger()] = "border";	// black
			prefabNamesMap[sf::Color(207,  61,  61).toInteger()] = "enemy";		// red
			prefabNamesMap[sf::Color( 69, 141, 208).toInteger()] = "player";	// blue
			prefabNamesMap[sf::Color( 61, 207, 126).toInteger()] = "teleporter";	// green
			prefabNamesMap[sf::Color(214, 202,  73).toInteger()] = "coin";		// yellow
		}

		bool doInstantiate(const string& s) {
			return s == "block" || s == "wall" || s=="coin" || s=="teleporter";
		}


		// ______________ queries
		sf::Image getLevelPixels(int level) {
			//1.load image
			const sf::Image levelsImage = Resources::Get<sf::Image>("levels");

			//2. cutout right portion
			sf::Image levelImage;
			levelImage.create(width, height);
			int startPxLeft = ((level-1) % 10) * 32 + 9;
			int startPxUp   = ((level-1) / 10) * 32 + 10;

			levelImage.copy(levelsImage, 0, 0, sf::IntRect(startPxLeft, startPxUp, width, height));
			return move(levelImage);
		}

		const string& prefabNameFromColor(const sf::Color color) {
			if (prefabNamesMap.count(color.toInteger()) == 0) {
				Debug::logError("MapBuilder queried prefab name with incorrect color");
				return emptyString;
			}
			return prefabNamesMap[color.toInteger()];
		}


		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new MapBuilder(*this); }

	};

}