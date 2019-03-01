#pragma once
#include <chrono>

using HighResolution = std::chrono::high_resolution_clock;

template<class TimeType = std::chrono::milliseconds> 
class Clock final
{
public:
	Clock() = delete;
	~Clock() = delete;

	static double GetElapsedTime()
	{
		prevTime = currentTime;
		currentTime = HighResolution::now();

		const double elapsedTime = std::chrono::duration_cast<TimeType>(currentTime - prevTime);

		return elapsedTime;
	}
	
private:
	static HighResolution::time_point prevTime;
	static HighResolution::time_point currentTime;
};