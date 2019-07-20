// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// doesn't do much..

namespace sxg::boom {

	class Background : public Component {
	public:
		// ______________ base
		void start() override {

		}

		void update() override {

		}
	private:
		// ______________ commands


		// ______________ queries



		// ______________ members

		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Background(*this); }
	};

}