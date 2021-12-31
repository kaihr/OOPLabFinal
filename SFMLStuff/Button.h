#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Button: public sf::Drawable, public sf::Transformable {
private:
	sf::RectangleShape _rect;
	sf::Text _text;
	sf::Font _font;
	float _left;
	float _top;

	sf::Color _color;
	sf::Color _textColor;
	sf::Color _onHoverColor;
	sf::Color _onHoverTextColor;

	float _currentScale;
	bool _isMouseOver;

public:
	// Button() {}
	Button(sf::Vector2f size, sf::Color color, std::string text, float textSize, sf::Color textColor, float left, float top): _left(left), _top(top), _color(color), _textColor(textColor), _onHoverColor(color), _onHoverTextColor(textColor), _isMouseOver(false) {
			_font.loadFromFile("Assets\\arial.ttf");
			_text.setFont(_font);
			_text.setCharacterSize(textSize);
			_text.setString(text);
			_text.setFillColor(textColor);
			//center text
			sf::FloatRect textRect = _text.getLocalBounds();
			_text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f + textSize / 4);
			_text.setPosition(left, top);


			_rect.setSize(size);
			_rect.setOrigin(size.x / 2, size.y / 2);
			_rect.setPosition(left, top);
			_rect.setFillColor(color);
			_rect.setOutlineColor(color);
			_rect.setOutlineThickness(0);

			_currentScale = 1;
		}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(_rect, states);
		target.draw(_text, states);
	}

	void setOnHoverColor(sf::Color color, sf::Color textColor) {
		_onHoverColor = color;
		_onHoverTextColor = textColor;
		_rect.setOutlineColor(_onHoverColor);
	}

	void update(sf::Vector2i mousePos){
		// Make effect on mouse over
		sf::Vector2f size = _rect.getSize();
		if (mousePos.x >= _left - size.x / 2 && mousePos.y >= _top - size.y / 2 &&
			mousePos.x <= _left + size.x / 2 && mousePos.y <= _top + size.y / 2) {
				//_rect.setOutlineThickness(5);
				if (_currentScale < 1.1)
					_currentScale += 0.005;
				_text.setScale(sf::Vector2f(_currentScale, _currentScale));
				_rect.setScale(sf::Vector2f(_currentScale, _currentScale));
				_rect.setFillColor(_onHoverColor);
				_text.setFillColor(_onHoverTextColor);
				_isMouseOver = true;
		}
		else {
			if (_currentScale > 1)
				_currentScale -= 0.005;
			_text.setScale(sf::Vector2f(_currentScale, _currentScale));
			_rect.setScale(sf::Vector2f(_currentScale, _currentScale));
			_rect.setFillColor(_color);
			_text.setFillColor(_textColor);
			_isMouseOver = false;
		}
	}

	bool isMouseOver(){
		return _isMouseOver;
	}
};
