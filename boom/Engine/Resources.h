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
				Debug::LogError("Could not load resource " + resourceName);
			}
		}

		//specializations
		template <typename T>
		static void setPrefixAndExtension() { }

		template <> static void setPrefixAndExtension<sf::Texture>()     { _prefix = "Images/", _extension = ".png"; }
		template <> static void setPrefixAndExtension<sf::Font>()        { _prefix = "Fonts/" , _extension = ".ttf"; }
		template <> static void setPrefixAndExtension<sf::SoundBuffer>() { _prefix = "Audio/" , _extension = ".wav"; }


		//specializations
		/*
		template <> static void Load(const string& resourceName, unordered_map<string, sf::Texture>& buffer) {
			_prefix = "Images/", _extension = ".png";
			Load(resourceName, buffer);
		}
		template <> static void Load(const string& resourceName, unordered_map<string, sf::Font>& buffer) {
			_prefix = "Fonts/", _extension = ".ttf";
			Load(resourceName, buffer);
		}
		template <> static void Load(const string& resourceName, unordered_map<string, sf::SoundBuffer>& buffer) {
			_prefix = "Audio/", _extension = ".wav";
			Load(resourceName, buffer);
		}
		*/


		//static void Load(const string& resourceName, unordered_map<string, string>& buffer);
		
	};

	//explicit instantiation
	/*
	template const sf::Texture& Resources::Get(const string resourceName);
	template <> static void Resources::Load(const string& resourceName, unordered_map<string, sf::Texture>& buffer) {
		_prefix = "Images/", _extension = ".png";
		Load(resourceName, buffer);
	}
	*/

}