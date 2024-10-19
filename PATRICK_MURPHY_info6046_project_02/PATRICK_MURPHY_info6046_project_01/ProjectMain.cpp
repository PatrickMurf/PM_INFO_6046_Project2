#include <iostream>
#include "fmod.hpp"
#include "conio.h"
//#include "AudioDemo.hpp"	<- Old ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "ChannelGroupManager.hpp"
#include "AdditionalFunctions.hpp"

// ~~~ Old main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//int main()
//{
//    AudioDemo demo;
//    demo.Prepare();
//    demo.RunDemo();
//    demo.ShutDown();
//    return 0;
//}

int main()
{
	// Create / Start the main channel manager
	audio::ChannelManager channelManager;
	channelManager.Initialize();

	// Creating a channel
	channelManager.CreateChannelGroup("ChannelGroup_Cave");
	FMOD::Sound* caveWalk = nullptr;
	FMOD::Sound* caveDrip = nullptr;
	FMOD::Channel* caveChannel = nullptr;
	channelManager.CreateSound("audio/P2_CaveWalk.wav", caveWalk);
	channelManager.CreateSound("audio/P2_WaterDrip.wav", caveWalk);

	std::vector<FMOD::Sound*> sounds = channelManager.getSoundsList();
	FMOD::ChannelGroup* channelGroup = channelManager.getChannelGroup();

	channelManager.DisplayChannelGroupInfo();

	// Setting up the variables used while running the program
	bool m_isRunning = true;
	bool m_isPaused = false;
	// Old unsure if still needed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*int channel = 0;
	unsigned int initialPosition = 0;
	unsigned int& position = initialPosition;*/
	bool initialPauseState = false;
	bool& pauseState = initialPauseState;
	float initialVolume = 1.0f;
	float initialPitch = 1.0f;
	float initialPan = 1.0f;

	bool soundInProgress = false;
	TimeManagement::Timer* timerAudio = TimeManagement::Timer::Instance();

	// Running loop for interaction
	RepeatControls();
	while (m_isRunning)
	{
		channelManager.Update();
		if (_kbhit())
		{
			int keyPress = _getch();

			if (keyPress == 27) //Escape
			{
				channelManager.Destroy(sounds);
				m_isRunning = false;
			}

			if (keyPress == 'p')
			{
				RepeatControls();
			}

			if (keyPress == 'o')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					channelManager.DisplayChannelGroupInfo();
				}
			}


			if (keyPress == '1')
			{
				//if (checkPlaystateAction(false, soundInProgress))
				{
					////channel = m_AudioManager->PlayAudio("audio/jaguar.wav");
					//channel = m_AudioManager->PlayAudio("audio/P2_CaveWalk.wav");

					//m_AudioManager->SetChannelVolume(channel, initialVolume);
					//m_AudioManager->SetChannelPitch(channel, initialPitch);
					//m_AudioManager->SetChannelPan(channel, initialPan);

					//m_AudioManager->soundIndex = "audio/P2_CaveWalk.wav";
					//InitiatePlayAudio();


					/*channelGroup->setVolume(1.0f);
					channelGroup->setPitch(1.0f);
					audioGrouping.PrintChannelGroupInfo();
					audioGrouping.PlaySound(sounds[0], channel1);
					audioGrouping.PlaySound(sounds[1], channel2);
					audioGrouping.SetChannelGroupDSP();*/

					channelGroup->setVolume(initialVolume);
					channelGroup->setPitch(initialPitch);
					channelManager.PlayAudioChannel(sounds[0], caveChannel);
					channelManager.PlayAudioChannel(sounds[1], caveChannel);
					channelManager.ModifyChannelGroupDSP();
				}
			}

			if (keyPress == 'q')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					channelManager.GetPauseState(pauseState);
					if (pauseState == false)
					{
						channelManager.SetPause(true);
						m_isPaused = true;
						printf("\n* Paused\n");
					}
					else
					{
						channelManager.SetPause(false);
						m_isPaused = false;
						printf("\n* Un-Paused\n");
					}
				}
			}

			if (keyPress == 'w')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					channelManager.SoundStop();
					soundInProgress = false;
					printf("\n* Audio stopped.\n");
				}
			}



			//For adjust volume
			if (keyPress == 'z')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					if (checkAdjustmentLimiter(initialVolume, 0.01f))
					{
						initialVolume = initialVolume + 0.1f;
						channelManager.SetChannelVolume(initialVolume);
						float retriveVolume = channelManager.GetChannelVolume();
						printf("Z: The volume increased to: %f\n", retriveVolume);
					}
				}
			}

			if (keyPress == 'x')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					if (checkAdjustmentLimiter(initialVolume, -0.01f))
					{
						initialVolume = initialVolume - 0.1f;
						channelManager.SetChannelVolume(initialVolume);
						float retriveVolume = channelManager.GetChannelVolume();
						printf("X: The volume decreased to: %f\n", retriveVolume);
					}
				}
			}

			//For adjust pitch
			if (keyPress == 'c')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					if (checkAdjustmentLimiter(initialPitch, 0.01f))
					{
						initialPitch = initialPitch + 0.1f;
						channelManager.SetChannelPitch(initialPitch);
						float retrivePitch = channelManager.GetChannelPitch();
						printf("Z: The pitch increased to: %f\n", retrivePitch);
					}
				}
			}

			if (keyPress == 'v')
			{
				//if (checkPlaystateAction(true, soundInProgress))
				{
					if (checkAdjustmentLimiter(initialPitch, -0.01f))
					{
						initialPitch = initialPitch - 0.1f;
						channelManager.SetChannelPitch(initialPitch);
						float retrivePitch = channelManager.GetChannelPitch();
						printf("Z: The pitch decreased to: %f\n", retrivePitch);
					}
				}
			}

			//For adjust pan
			/*	<-To do ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (keyPress == 'b')
			{
				if (checkPlaystateAction(true, soundInProgress))
				{
					if (checkAdjustmentLimiter(initialPan, 0.01f))
					{
						initialPan = initialPan + 0.1f;
						channelManager.SetChannelPan(channel, initialPan);
						float retrivePan = m_AudioManager->GetChannelPan(channel);
						printf("Z: The pan increased to: %f\n", retrivePan);
					}
				}
			}

			if (keyPress == 'n')
			{
				if (checkPlaystateAction(true, soundInProgress))
				{
					if (checkAdjustmentLimiter(initialPan, -0.01f))
					{
						initialPan = initialPan - 0.1f;
						channelManager.SetChannelPan(channel, initialPan);
						float retrivePan = channelManager.GetChannelPan();
						printf("Z: The pan decreased to: %f\n", retrivePan);
					}
				}
			}
			*/

			if (keyPress == 'm')
			{
				initialVolume = 1.0f;
				initialPitch = 1.0f;
				initialPan = 1.0f;

				//if (checkPlaystateAction(true, soundInProgress))
				{
					channelManager.SetChannelVolume(initialVolume);
					channelManager.SetChannelPitch(initialPitch);
					//channelManager.SetChannelPan(initialPan);	<- To do ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				}

				printf("\nM: Volume, Pitch, and Pan, have been reset to 1.0\n");
			}
		}
	}
}



