// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

namespace sxg::engine {
	class Time {
	// static class that manages time and timer callbacks
	public:

		static void start();
		static void update();

		static int nLoopRepetitions();

		static int frameNo();
		static float deltaTime();
		static float time();

		static void callback(function<void()>& func, float delay);

	private:
		static void processCallbacks();

		static sf::Clock _clock;

		static const int _desiredFps;

		static float _accumulator;

		static int _frame;
		static float _dt;
		static float _time;

		static vector<pair<float, function<void()>>> _callbacks;
	};
}