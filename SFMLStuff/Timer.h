#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std::chrono;

#define time std::chrono::time_point<std::chrono::high_resolution_clock>

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
		if (_minutes){
			if (_minutes < 10) res += "0";
			res += std::to_string(_minutes);
			res += ":";
		}
		if (_seconds < 10) res += "0";
		res += std::to_string(_seconds);
		if (!_hours && !_minutes){
			res += ".";
			res += std::to_string(_miliseconds / 10);
		}
		std::cout << res << '\n';
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

public:
	Timer() {
		_text.setCharacterSize(50);
		_text.setFillColor(sf::Color::Red);
		_font.loadFromFile("Assets\\arial.ttf");
		_text.setFont(_font);
	}
	void setPosition(int left, int top){
		_left = left;
		_top = top;
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(_text, states);
	}
	void setTimer(int hours, int minutes, int seconds, int miliseconds = 0) {
		_remainingTime = hours * 60 * 60 * 1000 +
			minutes * 60 * 1000 +
			seconds * 1000 +
			miliseconds;
	}
	void setTimer(FullTime remainingTime) {
		_remainingTime = remainingTime.toMiliseconds();
	}
	bool isActive() {
		return _isActive;
	}
	void start() {
		_tick = high_resolution_clock::now();
		_isActive = true;
	}
	bool update() {
		time temp = high_resolution_clock::now();
		int delta = duration_cast<milliseconds>(temp - _tick).count();
		_remainingTime -= delta;
		_tick = temp;

		_text.setString(getRemainingTime().toString());
		//_text.setPosition(300, 300);


		return _remainingTime > 0;
	}
	int stop() {
		_isActive = false;
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
