// File - time.h
// Description - Manages the tracking of time in the engine. 

#pragma once

#include <chrono>

class NTimer 
{
public:
	NTimer() = default;

	// calculate the timing information for rendering on screen. (TODO - Change the tick function to call update a minimum amount of times each second.)
	void tick(); 

	// Called every fixed amount of time. (TODO - Consider if this needs to be implemented. 
	void Tick();

	// Rtrieve the time since the last tick. 
	float getDeltaTime() const;

private:

	float  deltaTime = 0.0f;
	std::chrono::steady_clock::time_point prevTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
};