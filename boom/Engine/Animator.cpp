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
		int row = firstFrame.x, col = firstFrame.x;

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
			if (++row == _rows) {
				row = 0;
				if (++col == _cols) {
					Debug::LogError("Too many frames passed for animation");
					return;
				}
			}
		}
		_animFrames[animName] = { move(frames), loop };
	}

	bool Animator::valid(int row, int col) { return 0 <= row && row < _rows && 0 <= col && col < _cols; }


	void Animator::startAnimation(const string& animName) {
		if (_animFrames.count(animName) == 0) {
			Debug::LogError("animator doesn't have animation " + animName);
			return;
		}
		_stopped = false;
		_timer = 1.0f / _fps;
		_currentIndex = 0;
		_currentAnim = &_animFrames[animName];
	}

	void Animator::startDefaultAnim() {
		if (!_animFrames.empty()) {
			startAnimation(_animFrames.begin()->first);
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