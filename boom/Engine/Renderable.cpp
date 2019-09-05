// (c) Simone Guggiari 2019
#include "Renderable.h"


namespace sxg::engine {
	
	Renderable::Renderable(const string& spriteName, sf::IntRect spriteRect, Layer layer, int ppu, bool add) :
		_sprite(Resources::Get<sf::Texture>(spriteName), spriteRect),
		_layerOrder((int)layer), _pxPerUnit(ppu)
	{
		_sprite.setScale((1.0f / ppu), (1.0f/ppu));
		//insertion to renderables is made by the scene
		if (add) addToRenderables();
	}

	Renderable::~Renderable() {
		//remove from collection
		removeFromRenderables();
	}

	void Renderable::addToRenderables()
	{
		//if already present, throw error
		if (find(_renderables.begin(), _renderables.end(), this) != _renderables.end()) {
			Debug::logError("Renderables already contains this renderable");
			return;
		}

		//add it to collection & sort
		_renderables.push_back(this);
		sort(_renderables.begin(), _renderables.end(),
			[](Renderable* r1, Renderable* r2) {return r1->_layerOrder < r2->_layerOrder; });
	}

	void Renderable::removeFromRenderables() {
		auto it = find(_renderables.begin(), _renderables.end(), this);
		if (it != _renderables.end()) {
			_renderables.erase(it);
		}
	}

	void Renderable::draw() const {
		if (_active) {
			Screen::window().draw(_sprite);
		}
	}

	const vector<Renderable*>& Renderable::All(){
		return _renderables;
	}

	void Renderable::setActive(bool active) {
		_active = active;
	}

	sf::Transformable& Renderable::transform() { return _sprite; }
	sf::Sprite& Renderable::sprite() { return _sprite; }
	vector<Renderable*> Renderable::_renderables;

}