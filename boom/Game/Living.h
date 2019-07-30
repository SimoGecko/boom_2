// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "../Engine.h"

// mixin class that provides health, death

namespace sxg::boom {

	class Living {
	public:
		int health() const { return _health; }
		bool dead() const { return _dead; }
		Event onDamage;
		Event onDeath;

		void restoreHealth(int newStartingHealth = 0) {
			if (newStartingHealth > 0) _startingHealth = newStartingHealth;

			_health = _startingHealth;
			_dead = false;
		}
		void takeDamage(int amount) {
			if (_invincible) return;
			_health -= amount;
			if (_health <= 0) die();
			else onDamage();
		}
		void increaseHealth(int amount) {
			_health = clamp(_health + amount, 0, _startingHealth);
		}
		void setInvincible(bool b) { _invincible = b; }

	protected:
		int _startingHealth;

		int _health;
		bool _dead;
		bool _invincible;

		void die() {
			if (_dead) return;
			_health = 0;
			_dead = true;
			onDeath();
		}

	private:

	};
}