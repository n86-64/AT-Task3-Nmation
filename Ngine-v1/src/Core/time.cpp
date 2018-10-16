#include "time.h"

void Time::Tick()
{
	prevTime = currentTime;
	currentTime = std::chrono::system_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(prevTime - currentTime);
}

std::chrono::milliseconds Time::getDeltaTime() const
{
	return deltaTime;
}
