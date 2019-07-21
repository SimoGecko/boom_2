// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Component.h"
#include "GameObject.h"
#include "Time.h"
#include "Event.h"

// provides easy interface to animate sprites by swapping the rectange in the original texture

namespace sxg::engine {

	class Animator : public Component {

	public:
		void start() override {
			findSpriteReference();
			startDefaultAnim();
		}
		void update() override {
			updateFrame();
		}

		void setup(sf::Sprite* sprite, int fps, sf::Vector2i rowsCols, const string& animationListFileName);
		//Animator(const Animator& rhs);
		virtual ~Animator();

		void playAnimation(const string& animName);
		const string& currentAnimationName() const;
		//void setDefaultAnimation(const string& animName); // avoid as default animation is called before you have a change to set it

		Event onAnimationFinish;

	private:
		struct FrameSequence {
			string _animName;
			vector<sf::IntRect> _frames;
			bool _loop;
		};

		void loadAnimationsFromFile(const string& fileName);
		void addAnimation(const string& animName, vector<sf::IntRect> frames, bool loop = true);
		void findSpriteReference();
		void startDefaultAnim();
		void updateFrame();
		void setNextFrame();
		bool valid(int row, int col);

		vector<sf::IntRect> buildFrames(const string& animName, sf::Vector2i firstFrame, int nFrames);
		vector<sf::IntRect> buildFrames(const string& animName, sf::Vector2i firstFrame, vector<int> frameOffsets);


		// shared
		unordered_map<string, FrameSequence>* _animFrames; // shared ptr
		int _fps;
		int _width, _height;
		int _rows, _cols;
		string _defaultAnimationName;

		//unique
		sf::Sprite* _spriteRef;
		FrameSequence* _currentAnim;
		int _currentIndex;
		float _timer;
		bool _stopped;



		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Animator(*this); }
	};


}