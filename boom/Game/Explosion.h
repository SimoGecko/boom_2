// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// the graphic effect of an explosion

namespace sxg::boom {

	class Explosion : public Component {
	private:
		// ______________ members


	public:
		// ______________ base
		void start() override {

		}

		void update() override {

		}
		
	private:
		// ______________ commands


		// ______________ queries



		// ______________ cloning
		//using Component::Component;
		Component* clone() { return new Explosion(*this); }

	};

}