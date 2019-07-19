// (c) Simone Guggiari 2019
#include "Animator.h"


namespace sxg::engine {

	void Animator::setup(sf::Sprite* sprite, int fps, int rows, int cols) {
		_spriteRef = sprite;
		_fps = fps;
		_rows = rows;
		_cols = cols;
		_width = sprite->getTexture()->getSize().x / rows;
		_height = sprite->getTexture()->getSize().y / cols;
	}

	void Animator::addAnimation(const string& animName, sf::Vector2i firstFrame, int nFrames, bool loop) {
		int row = firstFrame.x, col = firstFrame.y;

		if (_animFrames.count(animName) > 0) {
			Debug::LogError("Animation already exists with name " + animName);
			return;
		}
		if (!valid(row, col)) { // && valid(rend, cend) && (rbeg < rend || (rbeg == rend && cbeg <= cend))
			Debug::LogError("Invalid start frame index for animation " + animName);
			return;
		}

		vector<sf::IntRect> frames;
		while (nFrames--) {
			frames.push_back(sf::IntRect(_width*col, _height*row, _width, _height));
			if (++col == _cols) {
				col = 0;
				if (++row == _rows && nFrames >0) {
					Debug::LogError("Too many frames passed for animation " + animName);
					return;
				}
			}
		}
		_animFrames[animName] = { move(frames), loop };
	}

	void Animator::loadAnimationsFromFile(const string& fileName) {
		//const string& file = Resources::Get<string>(fileName);
		//stringstream ss(file);
		//ifstream inputFile("Assets/")
		const vector<string>& lines = Resources::Get<vector<string>>(fileName);
		for (auto& line : lines) {
			if (line.empty() || line[0] == '#') continue;
			string animName;
			int row, col, numframes;
			stringstream ss(line);
			char loopChar;
			ss >> animName >> row >> col >> numframes >> loopChar;
			bool loop = loopChar == 'T';
			//if valid parsing
			addAnimation(animName, { row, col }, numframes, loop);
		}
	}

	bool Animator::valid(int row, int col) { return 0 <= row && row < _rows && 0 <= col && col < _cols; }

	const string& Animator::currentAnimName() const {
		return _currentAnimName;
	}


	void Animator::play(const string& animName) {
		if (_animFrames.count(animName) == 0) {
			Debug::LogError("Animator doesn't have animation " + animName);
			return;
		}
		_stopped = false;
		_timer = 1.0f / _fps;
		_currentIndex = 0;
		_currentAnim = &_animFrames[animName];
	}

	void Animator::startDefaultAnim() {
		if (!_animFrames.empty()) {
			play(_animFrames.begin()->first);
		}
	}

	

	void Animator::updateFrame() {
		if (_stopped || _currentAnim==nullptr) return;

		_timer -= Time::deltaTime();
		if (_timer <= 0) {
			_timer += 1.0f / _fps;
			setNextFrame();
		}
	}

	void Animator::setNextFrame() {
		++_currentIndex;
		if (_currentIndex == _currentAnim->_frames.size()) {
			if (_currentAnim->_loop) _currentIndex = 0;
			else {
				_stopped = true;
				return;
			}
		}
		_spriteRef->setTextureRect(_currentAnim->_frames[_currentIndex]);
	}
}