// (c) Simone Guggiari 2019
#include "Resources.h"


namespace sxg::engine {
	
	const string Resources::_filepath = "Assets/";
	string Resources::_prefix;
	string Resources::_extension;

	template <typename T>
	const T& Resources::Get(const string resourceName) {
		static unordered_map<string, T> buffer;

		if (buffer.count(resourceName) == 0) {
			Load<T>(resourceName, buffer);
		}
		return buffer.at(resourceName);
	}


	template <typename T>
	void Resources::Load(const string& resourceName, unordered_map<string, T>& buffer){
		T resource;
		if (resource.loadFromFile(_filepath + _prefix + resourceName + _extension)) {
			buffer[resourceName] = resource;
		}
		else {
			Debug::LogError("Could not load resource " + resourceName);
		}
	}
	
	template<>
	void Resources::Load(const string& resourceName, unordered_map<string, sf::Texture>& buffer) {
		_prefix = "Images/", _extension = ".png";
		Load(resourceName, buffer);
	}
	template<>
	void Resources::Load(const string& resourceName, unordered_map<string, sf::Font>& buffer) {
		_prefix = "Fonts/", _extension = ".ttf";
		Load(resourceName, buffer);
	}
	template<>
	void Resources::Load(const string& resourceName, unordered_map<string, sf::SoundBuffer>& buffer) {
		_prefix = "Audio/", _extension = ".wav";
		Load(resourceName, buffer);
	}
	
}