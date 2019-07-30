// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// reads the appropriate pixel subsection representing a map and instantiates the prefabs in the correct position.

namespace sxg::boom {


	class MapBuilder : public Component {
		CLONABLE(MapBuilder)
	public:
		static MapBuilder* instance;

		bool isWalkable(sf::Vector2i pos) {
			return isValid(pos) && tagsMap[pos.y][pos.x] == Tag::empty;//(mapObjects[r][c] == nullptr || isWalkableTag(mapObjects[r][c]->tag()));
		}

		int getExplosionDist(sf::Vector2i center, sf::Vector2i delta) { // int maxDist
			int ans = 0;
			//sf::Vector2i delta = vectorFromDir(direction);
			sf::Vector2i pos = center;

			while (isValid(pos)) {
				Tag tag = tagsMap[pos.y][pos.x];
				if (tag == Tag::block) return ans;
				if (tag == Tag::wall)  return ans-1;

				pos += delta;
				ans++;
			}
			return ans-1;
		}

		void blockBroke(sf::Vector2i pos) {
			if (tagsMap[pos.y][pos.x] != Tag::block) Debug::logError("Block is not breakable in MapBuilder.");
			tagsMap[pos.y][pos.x] = Tag::empty;
		}

	private:
		// ________________________________ data
		const int startLevel = 25;

		const size_t W = 15;
		const size_t H = 13;
		const int maxLevel = 80;
		const int numPlayers = 1;

		//unordered_map<int, string> prefabNamesMap;
		vector<vector<Tag>> tagsMap; // only need to know for stuff that doesn't move
		vector<sf::Vector2i> playerStartPos;


		// ________________________________ base
		void awake() override {
			if (instance != nullptr) Debug::logError("Multiple copies of singleton: MapBuilder");
			instance = this;
		}

		void start() override {


			loadLevel(startLevel);
		}

		void update() override {

		}

		void loadLevel(int level) {
			Debug::ensure(1 <= level && level <= maxLevel, "Invalid level index: " + to_string(level));

			setupBackgroundAndBorder();
			sf::Image levelImage = getLevelPixels(level);
			instantiateLevelPrefabs(levelImage);
			instantiatePlayers();
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
					else if (prefabName == "player") {
						playerStartPos.push_back(position);
					}
				}
			}
		}



		void instantiatePlayers() {
			Debug::ensure(playerStartPos.size() >= numPlayers, "Not enough player starting positions");
			for (int i = 0; i < numPlayers; ++i) {
				GameObject::Instantiate("player", to_v2f(playerStartPos[i]));
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

		bool isValid(sf::Vector2i pos) {
			return (0 <= pos.x && pos.x < W && 0 <= pos.y && pos.y < H);
		}

		bool doInstantiate(const string& s) {
			return s == "block" || s == "wall" || s == "coin" || s == "teleporter" || s == "enemy"; // || s == "player"
			// not: empty, border
		}
		bool setupTag(const string& s) { // static elements that don't move
			return s == "block" || s == "wall";// || s == "coin" || s == "teleporter";
		}
	};
}