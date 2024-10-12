#include "AudioDemo.hpp"
#include <conio.h>
#include <iostream>

void AudioDemo::StopDemo()
{
	m_isRunning = false;
}

void AudioDemo::Prepare()
{
	m_AudioManager = new audio::AudioManager();
	m_AudioManager->Initialize();
	m_AudioManager->LoadAudio("audio/jaguar.wav");
	m_AudioManager->LoadAudio("audio/singing.wav");
	m_AudioManager->LoadAudio("audio/swish.wav");
	m_AudioManager->LoadAudio("audio/awesomeness.wav");

	// Project 2 sounds
	m_AudioManager->LoadAudio("audio/P2_CaveWalk.wav");
}

void AudioDemo::ShutDown()
{
	m_AudioManager->Destroy();
	delete m_AudioManager;
}

bool soundInProgress = false;
TimeManagement::Timer* timerAudio = TimeManagement::Timer::Instance();

void AudioDemo::RunDemo()
{
	bool m_isRunning = true;
	bool m_isPaused = false;
	int channel = 0;
	unsigned int initialPosition = 0;
	unsigned int& position = initialPosition;

	float initialVolume = 1.0f;
	float initialPitch = 1.0f;
	float initialPan = 1.0f;

	bool initialPauseState = false;
	bool& pauseState = initialPauseState;
	RepeatControls();

	while (m_isRunning)
	{
		m_AudioManager->Update();

		if (_kbhit())
		{
			int keyPress = _getch();

			if (keyPress == 'p')
			{
				RepeatControls();
			}

			if (keyPress == 'o')
			{
				if (checkPlaystateAction(channel, true))
				{
					float retriveVolume = m_AudioManager->GetChannelVolume(channel);
					float retrivePitch = m_AudioManager->GetChannelPitch(channel);
					float retrivePan = m_AudioManager->GetChannelPan(channel);
					printf("\n");
					printf("The volume is: %f\n", retriveVolume);
					printf("The pitch is: %f\n", retrivePitch);
					printf("The pan is: %f\n", retrivePan);
				}
			}

			//For playing / setting a sound
			if (keyPress == '1')
			{
				if (checkPlaystateAction(channel, false))
				{
					//channel = m_AudioManager->PlayAudio("audio/jaguar.wav");
					channel = m_AudioManager->PlayAudio("audio/P2_CaveWalk.wav");

					m_AudioManager->SetChannelVolume(channel, initialVolume);
					m_AudioManager->SetChannelPitch(channel, initialPitch);
					m_AudioManager->SetChannelPan(channel, initialPan);

					m_AudioManager->soundIndex = "audio/P2_CaveWalk.wav";
					InitiatePlayAudio();
				}
			}

			if (keyPress == '2')
			{
				if (checkPlaystateAction(channel, false))
				{
					channel = m_AudioManager->PlayAudio("audio/singing.wav");

					m_AudioManager->SetChannelVolume(channel, initialVolume);
					m_AudioManager->SetChannelPitch(channel, initialPitch);
					m_AudioManager->SetChannelPan(channel, initialPan);

					m_AudioManager->soundIndex = "audio/singing.wav";
					InitiatePlayAudio();
				}
			}

			if (keyPress == '3')
			{
				if (checkPlaystateAction(channel, false))
				{
					channel = m_AudioManager->PlayAudio("audio/swish.wav");

					m_AudioManager->SetChannelVolume(channel, initialVolume);
					m_AudioManager->SetChannelPitch(channel, initialPitch);
					m_AudioManager->SetChannelPan(channel, initialPan);

					m_AudioManager->soundIndex = "audio/swish.wav";
					InitiatePlayAudio();
				}
			}

			if (keyPress == '4')
			{
				if (checkPlaystateAction(channel, false))
				{
					channel = m_AudioManager->PlayAudio("audio/awesomeness.wav");

					m_AudioManager->SetChannelVolume(channel, initialVolume);
					m_AudioManager->SetChannelPitch(channel, initialPitch);
					m_AudioManager->SetChannelPan(channel, initialPan);

					m_AudioManager->soundIndex = "audio/awesomeness.wav";
					InitiatePlayAudio();
				}
			}

			//Use q,w,e for play/pause/stop contorls?
			if (keyPress == 'q')
			{
				if (checkPlaystateAction(channel, true))
				{
					m_AudioManager->GetPauseState(channel, pauseState);
					if (pauseState == false)
					{
						m_AudioManager->SetPause(channel, true);
						m_isPaused = true;
						printf("\n* Paused\n");
					}
					else
					{
						m_AudioManager->SetPause(channel, false);
						m_isPaused = false;
						printf("\n* Un-Paused\n");
					}
				}
			}

			if (keyPress == 'w')
			{
				if (checkPlaystateAction(channel, true))
				{
					m_AudioManager->SoudStop(channel);
					soundInProgress = false;
					printf("\n* Audio stopped.\n");
				}
			}

			//For adjust volume
			if (keyPress == 'z')
			{
				if (checkPlaystateAction(channel, true))
				{
					if (checkAdjustmentLimiter(initialVolume, 0.01f))
					{
						initialVolume = initialVolume + 0.1f;
						m_AudioManager->SetChannelVolume(channel, initialVolume);
						float retriveVolume = m_AudioManager->GetChannelVolume(channel);
						printf("Z: The volume increased to: %f\n", retriveVolume);
					}
				}
			}

			if (keyPress == 'x')
			{
				if (checkPlaystateAction(channel, true))
				{
					if (checkAdjustmentLimiter(initialVolume, -0.01f))
					{
						initialVolume = initialVolume - 0.1f;
						m_AudioManager->SetChannelVolume(channel, initialVolume);
						float retriveVolume = m_AudioManager->GetChannelVolume(channel);
						printf("X: The volume decreased to: %f\n", retriveVolume);
					}
				}
			}

			//For adjust pitch
			if (keyPress == 'c')
			{
				if (checkPlaystateAction(channel, true))
				{
					if (checkAdjustmentLimiter(initialPitch, 0.01f))
					{
						initialPitch = initialPitch + 0.1f;
						m_AudioManager->SetChannelPitch(channel, initialPitch);
						float retrivePitch = m_AudioManager->GetChannelPitch(channel);
						printf("Z: The pitch increased to: %f\n", retrivePitch);
					}
				}
			}

			if (keyPress == 'v')
			{
				if (checkPlaystateAction(channel, true))
				{
					if (checkAdjustmentLimiter(initialPitch, -0.01f))
					{
						initialPitch = initialPitch - 0.1f;
						m_AudioManager->SetChannelPitch(channel, initialPitch);
						float retrivePitch = m_AudioManager->GetChannelPitch(channel);
						printf("Z: The pitch decreased to: %f\n", retrivePitch);
					}
				}
			}

			//For adjust pan
			if (keyPress == 'b')
			{
				if (checkPlaystateAction(channel, true))
				{
					if (checkAdjustmentLimiter(initialPan, 0.01f))
					{
						initialPan = initialPan + 0.1f;
						m_AudioManager->SetChannelPan(channel, initialPan);
						float retrivePan = m_AudioManager->GetChannelPan(channel);
						printf("Z: The pan increased to: %f\n", retrivePan);
					}
				}
			}

			if (keyPress == 'n')
			{
				if (checkPlaystateAction(channel, true))
				{
					if (checkAdjustmentLimiter(initialPan, -0.01f))
					{
						initialPan = initialPan - 0.1f;
						m_AudioManager->SetChannelPan(channel, initialPan);
						float retrivePan = m_AudioManager->GetChannelPan(channel);
						printf("Z: The pan decreased to: %f\n", retrivePan);
					}
				}
			}

			if (keyPress == 'm')
			{
				initialVolume = 1.0f;
				initialPitch = 1.0f;
				initialPan = 1.0f;

				if (checkPlaystateAction(channel, true))
				{
					m_AudioManager->SetChannelVolume(channel, initialVolume);
					m_AudioManager->SetChannelPitch(channel, initialPitch);
					m_AudioManager->SetChannelPan(channel, initialPan);
				}

				printf("\nM: Volume, Pitch, and Pan, have been reset to 1.0\n");
			}
		}



		if (checkPlaystateAction(channel, true))
		{
			timerAudio->TimerTick();
			if(timerAudio->getDeltaTime() >= 0.4f)
			{
				timerAudio->TimerReset();

				if (m_AudioManager->CheckChannelIsPlaying(channel) && m_isPaused == false)
				{
					float audioLength;
					float playPosition;
					float lengthBarSize = 50;

					audioLength = m_AudioManager->m_audioMap[m_AudioManager->soundIndex]->length;
					m_AudioManager->GetChannelPlaybackPosition(channel, position);
					playPosition = position;
					printf("\n\n\n\n\n\n\n\n\n\n\n", position);					// This just adds blankspace to make it more pretty.

					float sizeOfBarChar = (audioLength / lengthBarSize);	// This represents how much "time" a single character in the bar represents.
					float currentBarPos = (playPosition / sizeOfBarChar);	// This represents where nthe 'O' of the bar should be; where we're at in the audio.

					for (int i = 0; i <= lengthBarSize - 1; i++)
					{
						// This one has to go first, because the 'O' takes priority.
						// Since the characters of the bar don't match up well with the actual audio position; this tests for if the next character would be further than our current playback position.
						if (i < currentBarPos && (i + 1) > currentBarPos)
						{
							printf("O");
						}
						// If we're not at the O's position, then check if we're displaying a part of the bar we've already listened to.
						else if (i < currentBarPos)
						{
							printf("=");
						}
						// If we're niether of the above, then we're probably displaying a part of the bar that hasn't been listened to yet.
						// We're using an else-if, instead of an else, to avoid a bug were it was printing the bar as: =-=-=-=- ...etc.
						else if (i > currentBarPos)
						{
							printf("-");
						}
					}

					printf("  |  Playback: %d / %.1f\n", position, audioLength);
				}
			}
		}



		//Check still playing, but about to end
		if (soundInProgress == true)
		{
			m_AudioManager->GetChannelPlaybackPosition(channel, position);
			if (m_AudioManager->m_audioMap[m_AudioManager->soundIndex]->length <= position)
			{
				m_AudioManager->soundIndex = "";
				soundInProgress = false;
				//dirtyDelay = 0;
				printf("\n* SoundCompleted\n");
			}
		}
	}
}

void AudioDemo::RepeatControls()
{
	printf("\nThe controls are:\n P to show controls again\n O to show sound settings\n\n Number keys for sounds\n Q for play/pause\n W for stop\n\n Z/X for volume\n C/V for pitch\n B/N for pan\n M to reset defaults\n");
}

bool AudioDemo::checkPlaystateAction(int id, bool desireActive)
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

bool AudioDemo::checkAdjustmentLimiter(float modifyVar, float modifyVal)
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

void AudioDemo::InitiatePlayAudio()
{
	soundInProgress = true;
	timerAudio->TimerReset();
}
