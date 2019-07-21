// (c) Simone Guggiari 2019
#include "Animator.h"


namespace sxg::engine {

	void Animator::setup(sf::Sprite* sprite, int fps, sf::Vector2i rowsCols, const string& animationListFileName) {
		_spriteRef = sprite;
		_fps = fps;
		_rows = rowsCols.x;
		_cols = rowsCols.y;
		_width  = sprite->getTexture()->getSize().x / _cols;
		_height = sprite->getTexture()->getSize().y / _rows;
		_animFrames = new unordered_map<string, FrameSequence>();
		_defaultAnimationName = "";

		_currentAnim = nullptr;
		_currentIndex = 0;
		_timer = 0;
		_stopped = true;

		loadAnimationsFromFile(animationListFileName);
	}

	/*
	Animator::Animator(const Animator& rhs) {

	}
	*/

	Animator::~Animator() {
		//delete shared_ptr
	}

	void Animator::playAnimation(const string& animName) {
		if (_animFrames->count(animName) == 0) {
			Debug::logError("Animator doesn't have animation " + animName);
			return;
		}
		_stopped = false;
		_timer = 1.0f / _fps;
		_currentIndex = 0;
		_currentAnim = &(_animFrames->at(animName));
		//set initial frame
		_spriteRef->setTextureRect(_currentAnim->_frames[0]);
	}

	const string& Animator::currentAnimationName() const {
		if (_currentAnim == nullptr) return emptyString;
		return _currentAnim->_animName;
	}

	void Animator::loadAnimationsFromFile(const string& fileName) {
		//const string& file = Resources::Get<string>(fileName);
		//stringstream ss(file);
		//ifstream inputFile("Assets/")
		const vector<string>& lines = Resources::Get<vector<string>>(fileName);
		for (auto& line : lines) {
			if (line.empty() || line[0] == '#') continue;
			stringstream ss(line);
			string animName;
			int row, col, numframes;
			char loopChar;
			ss >> animName >> row >> col >> numframes >> loopChar;
			bool loop = loopChar == 'T';
			//if valid parsing
			addAnimation(animName, { row, col }, numframes, loop);
		}
	}

	void Animator::addAnimation(const string& animName, sf::Vector2i firstFrame, int nFrames, bool loop) {
		int row = firstFrame.x, col = firstFrame.y;

		if (_animFrames->count(animName) > 0) {
			Debug::logError("Animation already exists with name " + animName);
			return;
		}
		if (!valid(row, col)) {
			Debug::logError("Invalid start frame index for animation " + animName);
			return;
		}

		vector<sf::IntRect> frames;
		while (nFrames--) {
			frames.push_back(sf::IntRect(_width*col, _height*row, _width, _height));
			if (++col == _cols) {
				col = 0;
				if (++row == _rows && nFrames >0) {
					Debug::logError("Too many frames passed for animation " + animName);
					return;
				}
			}
		}
		(*_animFrames)[animName] = { animName, move(frames), loop };
		if (_defaultAnimationName.empty()) _defaultAnimationName = animName;
	}

	void Animator::findSpriteReference() {
		//ensure it has sprite (gameobject does this already);
		_spriteRef = &(gameobject().renderable().sprite());
		_currentAnim = nullptr;
	}

	void Animator::startDefaultAnim() {
		if (_animFrames == nullptr) {
			Debug::logError("Animator has nullptr frames: " + gameobject().name());
			return;
		}
		if (_animFrames->empty()) {
			Debug::logError("Animator has no animations.");
			return;
		}
		playAnimation(_defaultAnimationName);
	}

	/*
	void Animator::setDefaultAnimation(const string& animName) {
		_defaultAnimationName = animName;
	}
	*/


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

	bool Animator::valid(int row, int col) {
		return 0 <= row && row < _rows && 0 <= col && col < _cols;
	}
}