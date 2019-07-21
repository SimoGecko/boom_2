// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include <fstream>

// loads resources (Textures, Fonts, Sounds, Data, Images) from files and stores them for easy subsequent access


namespace sxg::engine {
	
	class Resources {
	public:
		//templates must be defined in the header

		template <typename T>
		static const T& Get(const string& resourceName) {
			static unordered_map<string, T> buffer;

			if (buffer.count(resourceName) == 0) {
				Load<T>(resourceName, buffer);
			}
			return buffer.at(resourceName);
		}
		
	private:
		static const string _filepath;
		static string _prefix, _extension; // to avoid passing arguments

		template <typename T>
		static void Load(const string& resourceName, unordered_map<string, T>& buffer) {
			setPrefixAndExtension<T>();
			T resource;
			if (resource.loadFromFile(_filepath + _prefix + resourceName + _extension)) {
				buffer[resourceName] = move(resource);
			}
			else {
				Debug::logError("Could not load resource " + resourceName);
			}
		}

		template <> // load data
		static void Load(const string& resourceName, unordered_map<string, vector<string>>& buffer) {
			ifstream inputFile("Assets/Data/" + resourceName + ".txt");
			if (inputFile.fail()) {
				Debug::logError("Couldn't open file: Assets/Data/" + resourceName + ".txt");
			}
			string line;
			while (getline(inputFile, line)) {
				buffer[resourceName].push_back(line);
			}
		}

		template <typename T>
		static void setPrefixAndExtension() { }
		//specializations
		template <> static void setPrefixAndExtension<sf::Texture>()	 { _prefix = "Images/", _extension = ".png"; }
		template <> static void setPrefixAndExtension<sf::Image>()		 { _prefix = "Images/", _extension = ".png"; }
		template <> static void setPrefixAndExtension<sf::Font>()        { _prefix = "Fonts/" , _extension = ".ttf"; }
		template <> static void setPrefixAndExtension<sf::SoundBuffer>() { _prefix = "Audio/Sounds/" , _extension = ".wav"; }
		
	};

}