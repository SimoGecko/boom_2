// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// pickup that represents a letter in the word EXTRA, which when completed rewards an additional life

namespace sxg::boom {

	class ExtraPickup : public Component {
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
		CLONABLE(ExtraPickup)
	};

}