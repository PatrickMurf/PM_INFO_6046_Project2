#pragma once
#include "ChannelGroupManager.hpp"
#include <conio.h>
#include <iostream>
#include "AudioTimer.hpp"

void RepeatControls();
void InitiatePlayAudio(bool soundInProgress, TimeManagement::Timer* timerAudio);

bool checkPlaystateAction(bool desireActive, bool soundInProgress);
bool checkAdjustmentLimiter(float modifyVar, float modifyVal);