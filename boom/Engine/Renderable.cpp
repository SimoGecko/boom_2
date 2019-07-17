// (c) Simone Guggiari 2019
#include "Renderable.h"


namespace sxg::engine {
	
	vector<Renderable*> Renderable::_renderables;

	
	Renderable::Renderable(const sf::Sprite& sprite, int layer, int ppu) :
		_sprite(sprite), _layerOrder(layer), _pxPerUnit(ppu)
	{
		//add it to collection & sort
		_renderables.push_back(this);
		sort(_renderables.begin(), _renderables.end(),
			[](Renderable* r1, Renderable* r2) {return r1->_layerOrder < r2->_layerOrder; });

		_sprite.setScale((1.0f / ppu), (1.0f/ppu));
	}

	Renderable::~Renderable() {
		//remove from collection
		auto it = find(_renderables.begin(), _renderables.end(), this);
		_renderables.erase(it);
	}

	void Renderable::draw() const {
		Screen::window().draw(_sprite);
	}

	const vector<Renderable*>& Renderable::All(){
		return _renderables;
	}

	sf::Transformable& Renderable::transform() { return _sprite; }

}