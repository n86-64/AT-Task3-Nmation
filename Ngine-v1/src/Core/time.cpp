#include "time.h"

// Used for aquiring the delta time.
constexpr float NTIME_NS_TO_MS = 1000000.0f;
constexpr float NTIME_MS_TO_S = 1000.0f;

void NTimer::tick()
{
	currentTime = std::chrono::steady_clock::now();
	deltaTime = (currentTime - prevTime).count() / NTIME_NS_TO_MS;
	prevTime = currentTime;
}

float NTimer::getDeltaTime() const
{
	return deltaTime;
}

float NTimer::getDeltaTimeInSeconds() const
{
	return deltaTime / NTIME_MS_TO_S;
}
