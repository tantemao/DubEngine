#include "Precompiled.h"
#include "../Inc/TimeUtil.h"

float DubEngine::Core::TimeUtil::GetTime()
{
	// gets the difference since the start time
	static const auto startTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
	return milliseconds / 1000.0f;
}

float DubEngine::Core::TimeUtil::GetDeltaTime()
{
	// gets the difference since the last time we checked
	static auto lastCallTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
	lastCallTime = currentTime;
	return milliseconds / 1000.0f;
}