// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

namespace sxg::engine {

	class GameObject;

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

		//static void pause();


		static void invoke(function<void(void)> func, float delay, GameObject* go);

	private:
		friend class Scene; // todo make only a single function

		static void eraseCallbacksOfDeletedObject(GameObject* go);
		static void eraseCallbacks();
		static void processCallbacks();

		struct callback {
			float time;
			function<void()> func;
			GameObject* go;
		};

		static sf::Clock _clock;

		static const int _desiredFps;

		static float _accumulator;

		static int _frame;
		static float _dt;
		static float _time; // real time vs game time
		static float _timescale; // TODO implement

		static vector<callback> _callbacks; // don't use references as they are usually destroyed
	};
}