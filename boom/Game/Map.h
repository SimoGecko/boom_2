// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// provides access to the runtime status of the map

namespace sxg::boom {

	class Map : public Component {
	CLONABLE(Map)
	public:
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
				if (tag == Tag::wall)  return ans - 1;

				pos += delta;
				ans++;
			}
			return ans - 1;
		}

		void blockBroke(sf::Vector2i pos) {
			if (tagsMap[pos.y][pos.x] != Tag::block) Debug::logError("Block is not breakable in MapBuilder.");
			tagsMap[pos.y][pos.x] = Tag::empty;
		}
		static Map* instance() { return _instance; }

	private:
		// ________________________________ data
		vector<vector<Tag>> tagsMap; // only need to know for stuff that doesn't move
		static Map* _instance;
		friend class MapBuilder;


		// ________________________________ base
		void awake() {
			_instance = this;

		}
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
 


		// ________________________________ queries
		bool isValid(sf::Vector2i pos) {
			int H = tagsMap.size();
			int W = tagsMap[0].size();
			return (0 <= pos.x && pos.x < W && 0 <= pos.y && pos.y < H);
		}


	};
}