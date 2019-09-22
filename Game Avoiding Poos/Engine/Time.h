#pragma once
#include <chrono>


class TimeFrame
{
private:
	/// Time points of this frame and last frame
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

private:
	TimeFrame() = default;

	/// Get singleton instance
	static TimeFrame& instance()
	{
		static TimeFrame instance;
		return instance;
	}

public:
	/// Call this function at the beginning of a frame
	static void Mark()
	{
		instance().last = instance().now;
		instance().now = std::chrono::steady_clock::now();
	}

	/// Calculate delta-time between this frame and last frame
	static float DeltaTime()
	{
		std::chrono::duration<float> duration = instance().now - instance().last;
		return duration.count();
	}

	/// Calculate fps of last second
	static float Fps()
	{
		static float timePassed = 0.0f;
		static int fps = 0;
		static int nFrame = 0;

		nFrame++;		
		timePassed += DeltaTime();

		if (timePassed >= 1.0f)
		{
			fps = nFrame;
			nFrame = 0;
			timePassed = 0.0f;
		}

		return fps;
	}
};






