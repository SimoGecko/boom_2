// (c) Simone Guggiari 2019
#include "Event.h"


namespace sxg::engine {
	Event& Event::operator+=(function<void(void)> f) {
		_listeners.push_back(f);
		return *this;
	}
	Event& Event::operator-=(function<void(void)> f) {
		//sure that can find it?
		//cannot compare
		/*
		auto it = find(_listeners.begin(), _listeners.end(), f);
		if (it != _listeners.end()) {
			_listeners.erase(it);
		}
		else {
			Debug::logError("Event doesn't have function to be removed: ");
		}
		*/
		return *this;
	}
	void Event::operator()() {
		for (size_t i = 0; i < _listeners.size(); ++i) {
			_listeners[i]();
		}
	}
}