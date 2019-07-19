// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Resources.h"

// provides simple facility to play audio and music

namespace sxg::engine {

	class Audio {
	public:
		static void start();
		//static void update();

		static void play(const string& soundName, float volume = 1, float pitch = 1, bool loop = false);

		static void playMusic(const string& musicName);

	private:
		static const int _nConcurrentSounds;
		static int _currentIndex;
		static vector<sf::Sound> _soundPlayers;
	};

}