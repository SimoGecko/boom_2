// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

namespace sxg::engine {
	class Time {
	// static class that manages time and timer callbacks
	public:

		static void start();
		static void update();

		static int nLoopRepetitions(); // only game can call this

		static int frameNo();
		static float deltaTime();
		static float time();
		static float& timescale();

		static void callback(function<void(void)> func, float delay);

	private:
		static void processCallbacks();

		static sf::Clock _clock;

		static const int _desiredFps;

		static float _accumulator;

		static int _frame;
		static float _dt;
		static float _time; // real time vs game time
		static float _timescale; // TODO implement

		static vector<pair<float, function<void()>>> _callbacks; // don't use references as they are usually destroyed
	};
}