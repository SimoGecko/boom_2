// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// base class for characters (player + enemies) that move, have health

namespace sxg::boom {

	class Character : public Component {
		CLONABLE(Character)
	public:

	private:
		// ________________________________ data


		// ________________________________ base
		void start() override {

		}

		void update() override {

		}
		
		// ________________________________ commands
 


		// ________________________________ queries


	};
}