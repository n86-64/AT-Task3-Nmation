#include "time.h"

// Used for aquiring the delta time.
constexpr float NTIME_NS_IN_MS = 1000000.0f;

void NTimer::tick()
{
	currentTime = std::chrono::steady_clock::now();
	deltaTime = (currentTime - prevTime).count() / NTIME_NS_IN_MS;
	prevTime = currentTime;
}

float NTimer::getDeltaTime() const
{
	return deltaTime;
}
