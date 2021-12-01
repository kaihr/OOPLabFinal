#pragma once

#include <chrono>
using namespace std::chrono;

#define time std::chrono::time_point<std::chrono::high_resolution_clock>

struct FullTime{

    int _hours;
    int _minutes;
    int _seconds;
    int _miliseconds;

    FullTime(int hours, int minutes, int seconds, int miliseconds = 0){
    	_hours = hours;
    	_minutes = minutes;
    	_seconds = seconds;
    	_miliseconds = miliseconds;
    }

    int toMiliseconds(){
        return _hours * 60 * 60 * 1000 +
               _minutes * 60 * 1000 +
               _seconds * 1000 +
               _miliseconds;
    }
};

class Timer{
private:
    int _remainingTime;   // in milisecond
    time _tick;
    bool _isActive;

public:
	void setTimer(int hours, int minutes, int seconds, int miliseconds = 0){
        _remainingTime = hours * 60 * 60 * 1000 +
					     minutes * 60 * 1000 +
					     seconds * 1000 +
					     miliseconds;
    }
	void setTimer(FullTime remainingTime){
        _remainingTime = remainingTime.toMiliseconds();
    }
    bool isActive(){
        return _isActive;
    }
    void start(){
        _tick = high_resolution_clock::now();
        _isActive = true;
    }
    bool update(){
        time temp = high_resolution_clock::now();
        int delta = duration_cast<milliseconds>(temp - _tick).count();
        _remainingTime -= delta;
        _tick = temp;
        return _remainingTime > 0;
    }
    int stop(){
        _isActive = false;
        return update();
    }
    FullTime getRemainingTime(){
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
