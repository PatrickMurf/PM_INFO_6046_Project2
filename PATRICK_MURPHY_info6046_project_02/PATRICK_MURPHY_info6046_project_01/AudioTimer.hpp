#pragma once

#include <chrono>

// Note:  For help with learning how to use Chrono, I referenced this video:	https://www.youtube.com/watch?v=Vyt-dM8gTRQ

namespace TimeManagement
{
	class Timer
	{
	private:
		static Timer* sTimerInstance;

		std::chrono::system_clock::time_point m_timeWaypoint;  // Where the timer was last set to reference from
		std::chrono::duration<float> mDeltaTime;
		float mTimeScale;

		Timer();
		~Timer();

	public:
		static Timer* Instance();
		static void Release();

		void TimerReset();
		float getDeltaTime();
		void SetTimeScale(float newTimeScale = 1.0f);
		float GetTimeScale();
		void TimerTick();
	};
}