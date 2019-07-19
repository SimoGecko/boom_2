// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Screen.h"
#include "Resources.h"

// Represents a sprite that can be rendered in game, with additional layeroder and container

namespace sxg::engine {
	
	class Renderable {
	public:
		//Renderable() {}
		Renderable(const string& spriteName, sf::IntRect spriteRect, int layer=0, int ppu=100, bool add=true);
		virtual ~Renderable();


		bool operator<(const Renderable& rhs) const { return _layerOrder < rhs._layerOrder; }
		static const vector<Renderable*>& All();

		void draw() const;
		sf::Transformable& transform();
		sf::Sprite& sprite();

		void addToRenderables();
		void removeFromRenderables();


	private:
		sf::Sprite _sprite;
		int _layerOrder;
		int _pxPerUnit;

		static vector<Renderable*> _renderables;
	};
	

}