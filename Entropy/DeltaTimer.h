#pragma once
#include <chrono>

// NOTES on Chrono Library
//duration
//Holds the amount of time between two points in time
//Can be stored as any time unit(seconds, millisconds, years, fortnights, ..)
//Can use both double and int

//time_point
//Holds a point in time
//Subtracting a time_point from another returns a duration

//Clock
//Three kinds : steady_clock, system_clock, high_resolution_clock
//Used to get current time as a time_point




class DeltaTimer
{
public:
	// Init timePrev to the current point in time
	DeltaTimer() : timePrev(std::chrono::high_resolution_clock::now())
	{
	}


	//~DeltaTimer();

	// Returns time since last time this function was called 
	// in seconds with nanosecond precision
	double GetDelta()
	{
		// 1. Get current time as a std::chrono::time_point
		auto timeCurrent = std::chrono::high_resolution_clock::now();

		// 2. Get the time difference as seconds 
		// ...represented as a double
		std::chrono::duration< double > delta(timeCurrent - timePrev);

		// 3. Reset the timePrev to the current point in time
		timePrev = std::chrono::high_resolution_clock::now();

		// 4. Returns the number of ticks in delta
		return delta.count();
	}

private:
	// For delta time calculation, updated every frame
	// We use high_resolution_clock 
	// ...because we want the highest possible accuracy
	std::chrono::time_point<std::chrono::high_resolution_clock> timePrev;
};

