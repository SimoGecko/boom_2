// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// collectable element that provides score

namespace sxg::boom {

	class Coin : public Component {
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
		Component* clone() { return new Coin(*this); }

	};

}