// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// placeable bomb that explodes after some time and destroys blocks/kills enemies

namespace sxg::boom {

	class Bomb : public Component {
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
		Component* clone() { return new Bomb(*this); }
	};

}