#include "AudioTimer.hpp"

namespace TimeManagement
{
    Timer* Timer::sTimerInstance = nullptr;

    Timer* Timer::Instance()
    {
        if (sTimerInstance == nullptr)
        {
            sTimerInstance = new Timer();
        }

        return sTimerInstance;
    }

    void Timer::Release()
    {
        delete sTimerInstance;
        sTimerInstance = nullptr;
    }

    Timer::Timer()
    {
        TimerReset();
        mTimeScale = 1.0f;
        mDeltaTime = std::chrono::duration<float>(0.0f);
    }

    Timer::~Timer() {}



    void Timer::TimerReset()
    {
        m_timeWaypoint = std::chrono::system_clock::now();
    }

    float Timer::getDeltaTime()
    {
        return mDeltaTime.count();
    }

    void Timer::SetTimeScale(float newTimeScale)
    {
        mTimeScale = newTimeScale;
    }

    float Timer::GetTimeScale()
    {
        return mTimeScale;
    }

    void Timer::TimerTick()
    {
        mDeltaTime = std::chrono::system_clock::now() - m_timeWaypoint;
    }
}