#pragma once

#include <sstream>
#include <string>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace std::chrono;
#define time std::chrono::time_point<std::chrono::high_resolution_clock>

const float TIMER_WIDTH = 200;
const float TIMER_HEIGHT = CELL_LENGTH / 2;
const sf::Color BLACK_INACTIVE(80, 80, 80);
const sf::Color WHITE_INACTIVE(175, 175, 175);
const int FONT_SIZE = 28;
const int OUTLINE_THICKNESS = 2;

struct FullTime {
	int _hours;
	int _minutes;
	int _seconds;
	int _miliseconds;

	FullTime(int hours, int minutes, int seconds, int miliseconds = 0) {
		_hours = hours;
		_minutes = minutes;
		_seconds = seconds;
		_miliseconds = miliseconds;
	}

	int toMiliseconds() {
		return _hours * 60 * 60 * 1000 +
			_minutes * 60 * 1000 +
			_seconds * 1000 +
			_miliseconds;
	}


	std::string toString() const {
		std::string res = "";
		if (_hours){
			if (_hours < 10) res += "0";
			res += std::to_string(_hours);
			res += ":";
		}
		else if (_minutes)
			res += "0:";
		if (_hours || _minutes){
			if (_minutes < 10) res += "0";
			res += std::to_string(_minutes);
			res += ":";
		}
		else
			res += "0:";
		if (_seconds < 10) res += "0";
		res += std::to_string(_seconds);
		if (!_hours && !_minutes){
			res += ".";
			res += std::to_string(_miliseconds / 10);
		}
		return res;
	}
};

class Timer: public sf::Drawable, public sf::Transformable {
private:
	int _remainingTime;   // in milisecond
	time _tick;
	bool _isActive;
	float _left;
	float _top;
protected:
	sf::Text _text;
	sf::Font _font;
	sf::RectangleShape _rect;

public:
	Timer(int remainingTime, bool isActive, float left, float top) : Timer() {
		std::cerr << "In";
		setPosition(left, top);

		_remainingTime = remainingTime;
		_text.setString(getRemainingTime().toString());

		_isActive = isActive;
	};

	std::string toString() const {
		std::stringstream ss;

		ss << _remainingTime;

		return ss.str();
	}

	Timer() {
		_tick = high_resolution_clock::now();
		_text.setCharacterSize(FONT_SIZE);
		_font.loadFromFile("Assets\\arial.ttf");
		_text.setFont(_font);
		_text.setStyle(sf::Text::Bold);
		_text.setString("0");

		_isActive = false;
		_left = _top = _remainingTime = 0;
	}

	void setPosition(int left, int top){
		_left = left;
		_top = top;
		_text.setPosition(_left + 50, _top + TIMER_HEIGHT / 2);
		// Center text
		sf::FloatRect textRect = _text.getLocalBounds();
		_text.setOrigin(textRect.left , textRect.top + textRect.height/2.0f);

		_rect.setSize(sf::Vector2f(TIMER_WIDTH - OUTLINE_THICKNESS * 2, TIMER_HEIGHT - OUTLINE_THICKNESS * 2));
		_rect.setOutlineThickness(OUTLINE_THICKNESS);
		_rect.setPosition(_left + OUTLINE_THICKNESS, _top + OUTLINE_THICKNESS);
		if (_top > 0)
			_rect.setOutlineColor(sf::Color::Black);
		else
			_rect.setOutlineColor(sf::Color::White);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(_rect);
		target.draw(_text, states);
	}

	void setTimer(int hours, int minutes, int seconds, int miliseconds = 0) {
		_remainingTime = hours * 60 * 60 * 1000 +
			minutes * 60 * 1000 +
			seconds * 1000 +
			miliseconds;

		_text.setString(getRemainingTime().toString());
	}

	void setTimer(FullTime remainingTime) {
		_remainingTime = remainingTime.toMiliseconds();

		_text.setString(getRemainingTime().toString());
	}

	bool isActive() {
		return _isActive;
	}

	void start() {
		_tick = high_resolution_clock::now();
		_isActive = true;
		if (_top > 0) {
			_rect.setFillColor(sf::Color::White);
			_rect.setOutlineColor(sf::Color::Black);
			_text.setFillColor(sf::Color::Black);
		}
		else {
			_rect.setFillColor(sf::Color::Black);
			_rect.setOutlineColor(sf::Color::Black);
			_text.setFillColor(sf::Color::White);
		}
		_text.setString(getRemainingTime().toString());
	}


	bool update() {
		if (_isActive)
		{
			time temp = high_resolution_clock::now();
			int delta = duration_cast<milliseconds>(temp - _tick).count();

			if (delta >= 1000 || (_remainingTime <= 60 * 1000 && delta >= 10)) {
				_remainingTime -= delta;
				_tick = temp;
				_text.setString(getRemainingTime().toString());
			}
		}

		return _remainingTime > 0;
	}

	int stop() {
		_isActive = false;
		if (_top > 0) {
			_rect.setFillColor(WHITE_INACTIVE);
			_rect.setOutlineColor(BLACK_INACTIVE);
			_text.setFillColor(BLACK_INACTIVE);
		}
		else {
			_rect.setFillColor(BLACK_INACTIVE);
			_rect.setOutlineColor(BLACK_INACTIVE);
			_text.setFillColor(WHITE_INACTIVE);
		}
		return update();
	}

	FullTime getRemainingTime() const {
		int temp = _remainingTime;
		int miliseconds = temp % 1000;
		temp /= 1000;
		int seconds = temp % 60;
		temp /= 60;
		int minutes = temp % 60;
		temp /= 60;
		int hours = temp % 1000;
		return FullTime(hours, minutes, seconds, miliseconds);
	}
};
