// (c) Simone Guggiari 2019
#include "Audio.h"


namespace sxg::engine {
	void Audio::start() {
		//create sound players
		for (size_t i = 0; i < _nConcurrentSounds; ++i) {
			_soundPlayers.push_back(sf::Sound());
		}
		_currentIndex = 0;
	}

	void Audio::play(const string& soundName, float volume, float pitch, bool loop) {
		const sf::SoundBuffer& buffer = Resources::Get<sf::SoundBuffer>(soundName);
		sf::Sound& sound = _soundPlayers[_currentIndex];

		sound.setBuffer(buffer);
		sound.setVolume(100 * volume);
		sound.setPitch(pitch);
		sound.setLoop(loop);
		sound.play();
		if (++_currentIndex == _nConcurrentSounds) _currentIndex = 0;
	}

	void Audio::playMusic(const string& musicName) {
		/*
		sf::Music music;
		music.openFromFile("filepath");
		music.play();
		*/
	}

	//static definitions
	const size_t Audio::_nConcurrentSounds = 8;
	int Audio::_currentIndex;
	vector<sf::Sound> Audio::_soundPlayers;
}