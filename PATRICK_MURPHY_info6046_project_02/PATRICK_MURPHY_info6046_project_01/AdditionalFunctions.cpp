#include "AdditionalFunctions.hpp"

void RepeatControls()
{
	// Old print statement
	//printf("\nThe controls are:\n P to show controls again\n O to show sound settings\n\n Number keys for sounds\n Q for play/pause\n W for stop\n\n Z/X for volume\n C/V for pitch\n B/N for pan\n M to reset defaults\n");
	std::cout << "\n\n"
		<< "\nThe controls are:"
		<< "\n P to show controls again"
		<< "\n O to show sound settings"
		<< "\n\n Number keys for sounds"
		<< "\n Q for play/pause"
		<< "\n W for stop"
		<< "\n\n Z/X for volume"
		<< "\n C/V for pitch"
		<< "\n B/N for pan   *Currently out of order"
		<< "\n M to reset defaults"
		<< "\n";
}

bool checkPlaystateAction(bool desireActive, bool soundInProgress)
{

	bool testpassed = false;

	if (desireActive == true)
	{
		//if (channelPlayingStatus == true) { testpassed = true; }
		if (soundInProgress == true) { testpassed = true; }
	}
	else
	{
		//if (channelPlayingStatus == false) { testpassed = true; }
		if (soundInProgress == false) { testpassed = true; }
	}

	return testpassed;
}

bool checkAdjustmentLimiter(float modifyVar, float modifyVal)
{
	bool passTest = true;

	if (modifyVar + modifyVal < 0.1)
	{
		passTest = false;
	}
	else if (modifyVar + modifyVal > 2.7)
	{
		passTest = false;
	}

	return passTest;
}

void InitiatePlayAudio(bool soundInProgress, TimeManagement::Timer* timerAudio)
{
	soundInProgress = true;
	timerAudio->TimerReset();
}
