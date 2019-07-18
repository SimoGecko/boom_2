// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "GameObject.h"
#include "Time.h"

// provides easy interface to animate sprites by swapping the rectange in the original texture

namespace sxg::engine {

	class Animator : public Component {

	public:
		void start() override { startDefaultAnim(); }
		void update() override { updateFrame(); }

		void setup(sf::Sprite* sprite, int fps, int rows, int cols);
		void addAnimation(const string& animName, sf::Vector2i firstFrame, int nFrames, bool loop = true);
		void startAnimation(const string& animName);

	private:
		struct FrameSequence {
			vector<sf::IntRect> _frames;
			bool _loop;
		};

		void startDefaultAnim();
		void updateFrame();
		void setNextFrame();
		bool valid(int row, int col);

		map<string, FrameSequence> _animFrames;
		sf::Sprite* _spriteRef;

		FrameSequence* _currentAnim;
		int _currentIndex;
		float _timer;

		int _fps;
		int _width, _height;
		int _rows, _cols;
		bool _stopped;

		// ______________ cloning
		using Component::Component;
		Animator* clone(GameObject& go) override { return new Animator(go); }

		
	};


}