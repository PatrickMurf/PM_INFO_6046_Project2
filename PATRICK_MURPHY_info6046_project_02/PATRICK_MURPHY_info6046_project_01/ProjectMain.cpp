#include <iostream>
#include "fmod.hpp"
#include "conio.h"
#include "ChannelGroupManager.hpp"
#include "AdditionalFunctions.hpp"

int main()
{
	// Create / Start the main channel manager
	audio::ChannelManager channelManager;
	channelManager.Initialize();

	std::vector<FMOD::ChannelGroup*> listChannelGroups;

	// Creating a channel
	channelManager.CreateChannelGroup("ChannelGroup_Cave");
	FMOD::Sound* caveWalk = nullptr;
	FMOD::Sound* caveDrip = nullptr;
	FMOD::Channel* caveChannel = nullptr;
	channelManager.CreateSound("audio/P2_CaveWalk.wav", caveWalk);
	channelManager.CreateSound("audio/P2_WaterDrip.wav", caveDrip);
	std::vector<FMOD::Sound*> caveSounds = channelManager.getSoundsList();
	listChannelGroups.push_back(channelManager.getChannelGroup());

	channelManager.CreateChannelGroup("ChannelGroup_Radio");
	FMOD::Sound* radioChatter = nullptr;
	FMOD::Sound* radioDrive = nullptr;
	FMOD::Channel* radioChannel = nullptr;
	channelManager.CreateSound("audio/P2_Chatter.wav", radioChatter);
	channelManager.CreateSound("audio/P2_CarDrive.wav", radioDrive);
	std::vector<FMOD::Sound*> radioSounds = channelManager.getSoundsList();
	listChannelGroups.push_back(channelManager.getChannelGroup());

	channelManager.CreateChannelGroup("ChannelGroup_Popcorn");
	FMOD::Sound* popcornPopcorn = nullptr;
	FMOD::Sound* popcornMicrowave = nullptr;
	FMOD::Channel* popcornChannel = nullptr;
	channelManager.CreateSound("audio/P2_PopCorn.wav", popcornPopcorn);
	channelManager.CreateSound("audio/P2_Microwave.wav", popcornMicrowave);
	std::vector<FMOD::Sound*> popcornSounds = channelManager.getSoundsList();
	listChannelGroups.push_back(channelManager.getChannelGroup());



	int currentChannel = NULL;

	channelManager.DisplayChannelGroupInfo(listChannelGroups[currentChannel]);

	// Setting up the variables used while running the program
	bool m_isRunning = true;
	bool m_isPaused = false;
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
				channelManager.Destroy(caveSounds);
				channelManager.Destroy(radioSounds);
				channelManager.Destroy(popcornSounds);
				m_isRunning = false;
			}

			if (keyPress == 'p')
			{
				RepeatControls();
			}

			if (keyPress == 'o')
			{
				{
					channelManager.DisplayChannelGroupInfo(listChannelGroups[currentChannel]);
				}
			}


			if (keyPress == '1')
			{
				{
					currentChannel = 0;
					listChannelGroups[currentChannel]->setVolume(initialVolume);
					listChannelGroups[currentChannel]->setPitch(initialPitch);
					channelManager.PlayAudioChannel(caveSounds[0], caveChannel);
					channelManager.PlayAudioChannel(caveSounds[1], caveChannel);
					channelManager.ModifyChannelGroupDSP(0);
				}
			}

			if (keyPress == '2')
			{
				{
					currentChannel = 1;
					channelManager.setChannelGroup(listChannelGroups[currentChannel]);
					listChannelGroups[currentChannel]->setVolume(initialVolume);
					listChannelGroups[currentChannel]->setPitch(initialPitch);
					channelManager.PlayAudioChannel(radioSounds[2], radioChannel);
					channelManager.PlayAudioChannel(radioSounds[3], radioChannel);
					channelManager.ModifyChannelGroupDSP(1);
				}
			}

			if (keyPress == '3')
			{
				{
					currentChannel = 2;
					listChannelGroups[currentChannel]->setVolume(initialVolume);
					listChannelGroups[currentChannel]->setPitch(initialPitch);
					channelManager.PlayAudioChannel(popcornSounds[4], caveChannel);
					channelManager.PlayAudioChannel(popcornSounds[5], caveChannel);
					channelManager.ModifyChannelGroupDSP(2);
				}
			}



			if (keyPress == 'q')
			{
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
				{
					channelManager.SoundStop();
					soundInProgress = false;
					currentChannel = NULL;
					printf("\n* Audio stopped.\n");
				}
			}



			//For adjust volume
			if (keyPress == 'z')
			{
				{
					if (checkAdjustmentLimiter(initialVolume, 0.01f))
					{
						initialVolume = initialVolume + 0.1f;
						channelManager.SetChannelVolume(initialVolume, listChannelGroups[currentChannel]);
						float retriveVolume = channelManager.GetChannelVolume(listChannelGroups[currentChannel]);
						printf("Z: The volume of %i increased to: %f\n", currentChannel, retriveVolume);
					}
				}
			}

			if (keyPress == 'x')
			{
				{
					if (checkAdjustmentLimiter(initialVolume, -0.01f))
					{
						initialVolume = initialVolume - 0.1f;
						channelManager.SetChannelVolume(initialVolume, listChannelGroups[currentChannel]);
						float retriveVolume = channelManager.GetChannelVolume(listChannelGroups[currentChannel]);
						printf("X: The volume of %i decreased to: %f\n", currentChannel, retriveVolume);
					}
				}
			}

			//For adjust pitch
			if (keyPress == 'c')
			{
				{
					if (checkAdjustmentLimiter(initialPitch, 0.01f))
					{
						initialPitch = initialPitch + 0.1f;
						channelManager.SetChannelPitch(initialPitch, listChannelGroups[currentChannel]);
						float retrivePitch = channelManager.GetChannelPitch(listChannelGroups[currentChannel]);
						printf("Z: The pitch increased to: %f\n", retrivePitch);
					}
				}
			}

			if (keyPress == 'v')
			{
				{
					if (checkAdjustmentLimiter(initialPitch, -0.01f))
					{
						initialPitch = initialPitch - 0.1f;
						channelManager.SetChannelPitch(initialPitch, listChannelGroups[currentChannel]);
						float retrivePitch = channelManager.GetChannelPitch(listChannelGroups[currentChannel]);
						printf("Z: The pitch decreased to: %f\n", retrivePitch);
					}
				}
			}

			if (keyPress == 'm')
			{
				initialVolume = 1.0f;
				initialPitch = 1.0f;
				initialPan = 1.0f;

				{
					channelManager.SetChannelVolume(initialVolume, listChannelGroups[currentChannel]);
					channelManager.SetChannelPitch(initialPitch, listChannelGroups[currentChannel]);
				}

				printf("\nM: Volume, Pitch, and Pan, have been reset to 1.0\n");
			}
		}
	}
}



