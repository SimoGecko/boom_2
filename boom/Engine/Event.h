// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// simple class to implement C# style events, with subscription and callbacks of provided functions

namespace sxg::engine {

	class Event {
	public:
		Event& operator+=(function<void(void)> f);
		Event& operator-=(function<void(void)> f);
		void operator()();
	private:
		vector<function<void(void)>> _listeners;
	};

}