// File - time.h
// Description - Manages the tracking of time in the engine. 

#pragma once

#include <chrono>

class Time 
{
public:
	Time() = default;

	// calculate the timing information for rendering on screen. 
	void Tick(); 

	// Rtrieve the time since the last tick. 
	std::chrono::milliseconds getDeltaTime() const;

private:

	std::chrono::milliseconds  deltaTime;
	std::chrono::system_clock::time_point prevTime = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
};