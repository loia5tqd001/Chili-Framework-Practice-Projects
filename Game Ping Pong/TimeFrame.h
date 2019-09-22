#pragma once
#include <chrono>


class TimeFrame
{
private:
	/// Time points of this frame and last frame
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float deltaTime = 0;

private:
	TimeFrame() = default;

	/// Get singleton instance
	static TimeFrame& frmTimer()
	{
		static TimeFrame instance;
		return instance;
	}

public:
	/// Call this function at the beginning of a frame
	static void Mark()
	{
		frmTimer().last = frmTimer().now;
		frmTimer().now = std::chrono::steady_clock::now();

		std::chrono::duration<float> duration = frmTimer().now - frmTimer().last;
		frmTimer().deltaTime = duration.count();
	}

	/// Calculate delta-time between this frame and last frame
	static float DeltaTime()
	{
		return frmTimer().deltaTime;
	}

	/// Calculate fps of last second
	static int Fps()
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






