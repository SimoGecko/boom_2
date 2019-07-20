// (c) Simone Guggiari 2019
#include "Time.h"


namespace sxg::engine {
	const int Time::_desiredFps = 60;

	void Time::start() {
		_clock.restart();
		_accumulator = 0;

		_frame = 0;
		_dt = 1.0f / _desiredFps;
		_time = 0;
	}

	void Time::update() {
		_frame++;
		_time += deltaTime();
		_accumulator -= _dt; // should remain the same, right?

		processCallbacks();
	}

	void Time::processCallbacks() {
		//check callbacks
		if (!_callbacks.empty()) {
			size_t i;
			for (i = 0; i < _callbacks.size(); ++i) {
				if (_callbacks[i].first > _time) break; // not time yet
				//invoke
				_callbacks[i].second();
			}
			//delete up to i-1
			if (i > 0) {
				_callbacks.erase(_callbacks.begin(), _callbacks.begin() + i);
			}
		}
	}

	int Time::nLoopRepetitions() {
		_accumulator += _clock.restart().asSeconds();
		if (_accumulator > 0.25) _accumulator = 0.25; // clamp
		int reps = (int)floor(_accumulator / _dt);
		return reps;
	}

	void Time::callback(function<void()>& func, float delay) {
		_callbacks.push_back({ _time + delay, func });
		//sort by increasing time
		sort(_callbacks.begin(), _callbacks.end(), [](auto& l, auto& r) {return l.first < r.first; });
	}


	//queries
	int   Time::frameNo() { return _frame; }
	float Time::deltaTime() { return _dt * _timescale; }
	float Time::time() { return _time; }
	float& Time::timescale() { return _timescale; }


	//static decl
	sf::Clock Time::_clock;
	float Time::_accumulator;
	int Time::_frame;
	float Time::_dt;
	float Time::_time;
	float Time::_timescale = 1;

	vector<pair<float, function<void()>>> Time::_callbacks;

}