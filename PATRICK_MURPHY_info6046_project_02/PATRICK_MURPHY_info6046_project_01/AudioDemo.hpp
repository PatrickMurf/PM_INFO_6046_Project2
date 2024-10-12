#pragma once

#include "AudioManager.hpp"
#include "AudioTimer.hpp"

class AudioDemo
{
private:
	void StopDemo();

	audio::AudioManager* m_AudioManager;
	bool m_isRunning;

public:
	AudioDemo() = default;
	~AudioDemo() {}

	void Prepare();
	void ShutDown();

	void RunDemo();

	void RepeatControls();
	void InitiatePlayAudio();

	bool checkPlaystateAction(int id, bool desireActive);
	bool checkAdjustmentLimiter(float modifyVar, float modifyVal);
};