// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include <fstream>

// loads resources (Textures, Fonts, Sounds, Data, Images) from files and stores them for easy subsequent access


namespace sxg::engine {

	
	class Resources {
	public:
		// make it template
		template <typename T>
		static const T& Get(const string resourceName);
		
	private:
		static const string _filepath;
		static string _prefix, _extension; // to avoid passing arguments

		template <typename T>
		static void Load(const string& resourceName, unordered_map<string, T>& buffer);

		//specializations
		template <> static void Load(const string& resourceName, unordered_map<string, sf::Texture>& buffer);
		template <> static void Load(const string& resourceName, unordered_map<string, sf::Font>& buffer);
		template <> static void Load(const string& resourceName, unordered_map<string, sf::SoundBuffer>& buffer);
		//static void Load(const string& resourceName, unordered_map<string, string>& buffer);
		
	};
	

}