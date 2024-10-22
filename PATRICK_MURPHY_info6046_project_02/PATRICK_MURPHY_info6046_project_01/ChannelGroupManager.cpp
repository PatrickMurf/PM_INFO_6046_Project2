#include "ChannelGroupManager.hpp"

#include <iostream>
#include "fmod_errors.h"

namespace audio
{
	ChannelManager::ChannelManager()
	{
	}

	ChannelManager::~ChannelManager()
	{
	}

	void ChannelManager::Initialize()
	{
		if (m_isInitialized)
		{
			return;
		}

		FMOD_RESULT result;
		result = FMOD::System_Create(&m_System);

		if (result != FMOD_OK)
		{
			printf("Failed to create the FMOD System!\n");
			return;
		}

		result = m_System->init(512, FMOD_INIT_NORMAL, nullptr);

		if (result != FMOD_OK)
		{
			printf("Failed to initialize the system!\n");

			//Cleanup
			result = m_System->close();
			if (result != FMOD_OK)
			{
				printf("Failed to close the system!\n");
			}
			return;
		}

		printf("ChannelManager::Initialize() / AudioRecording:  Successful!\n");

		// ~~~ Unused flag ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*for (int i = 0; i < 20; i++)
		{
			m_channelList.push_back(new Channel);
		}*/

		m_isInitialized = true;
	}

	void ChannelManager::Destroy(std::vector<FMOD::Sound*> sounds)
	{
		if (!m_isInitialized)
		{
			return;
		}

		FMOD_RESULT result;

		for (FMOD::Sound* sound : sounds)
		{
			//result = pair.second->Audio->release();		-- OLD	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			result = sound->release();
			FMODCheckError(result);
		}

		//m_audioMap.clear();		-OLD ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		result = m_channelGroup->release();

		result = m_System->close();
		FMODCheckError(result);

		result = m_System->release();
		FMODCheckError(result);

		m_isInitialized = false;
	}

	void ChannelManager::Update()
	{
		if (!m_isInitialized)
		{
			return;
		}

		FMOD_RESULT result = m_System->update();

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			Destroy(m_SoundsList);
		}
	}

	std::vector<FMOD::Sound*> ChannelManager::getSoundsList()
	{
		return m_SoundsList;
	}

	FMOD::ChannelGroup* ChannelManager::getChannelGroup()
	{
		return m_channelGroup;
	}

	void ChannelManager::CreateSound(const char* filename, FMOD::Sound* sound)
	{
		if (!m_isInitialized)
		{
			return;
		}

		FMOD_RESULT result = m_System->createSound(filename, FMOD_DEFAULT, 0, &sound);
		m_SoundsList.push_back(sound);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		std::cout << "Successfully created the sound " << filename << " !\n";
	}

	void ChannelManager::CreateChannelGroup(const char* channelId)
	{
		if (!m_isInitialized)
		{
			return;
		}

		FMOD_RESULT result = m_System->createChannelGroup(channelId, &m_channelGroup);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		std::cout << "The channel grouping " << channelId << " has been created!\n";
	}

	void ChannelManager::ModifyChannelGroupDSP()
	{
		if (!m_isInitialized)
		{
			return;
		}

		// ~~~ Edit flag ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		FMOD::DSP* dspTypeEcho;
		FMOD_RESULT result = m_System->createDSPByType(FMOD_DSP_TYPE_ECHO, &dspTypeEcho);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		result = dspTypeEcho->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.8f);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		m_channelGroup->addDSP(0, dspTypeEcho);
	}

	void ChannelManager::PlayAudioChannel(FMOD::Sound* sound, FMOD::Channel* channel)
	{
		if (!m_isInitialized)
		{
			return;
		}

		FMOD_RESULT result = m_System->playSound(sound, m_channelGroup, false, &channel);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		result = channel->setChannelGroup(m_channelGroup);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		result = channel->setPaused(false);

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		char soundName[256];
		result = sound->getName(soundName, sizeof(soundName));

		if (result != FMOD_OK)
		{
			FMODCheckError(result);
			return;
		}

		std::cout << "Now playing the sound:  " << soundName << " !\n";
	}

	void ChannelManager::DisplayChannelGroupInfo()
	{
		float retriveVolume = GetChannelVolume();
		float retrivePitch = GetChannelPitch();
		//float retrivePan = GetChannelPan(channelId);	<- TODO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		printf("\n\n\n");
		printf("The volume is: %f\n", retriveVolume);
		printf("The pitch is: %f\n", retrivePitch);
		//printf("The pan is: %f\n", retrivePan); < -TODO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}






	void ChannelManager::SetChannelVolume(float value)
	{
		/*float volume;
		FMOD_RESULT result = m_channelGroup->getVolume(&volume);
		FMODCheckError(result);
		return volume;*/

		FMOD_RESULT result = m_channelGroup->setVolume(value);
		FMODCheckError(result);
	}

	void ChannelManager::SetChannelPitch(float value)
	{
		/*float pitch;
		FMOD_RESULT result = m_channelGroup->getPitch(&pitch);
		FMODCheckError(result);
		return pitch;*/

		FMOD_RESULT result = m_channelGroup->setPitch(value);
		FMODCheckError(result);
	}

	// ~~~ Not sure about how to implement this right now ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*float ChannelManager::SetChannelPan(int id, float value)
	{
		float pan;
		pan = m_channelGroup->pan;
		return pan;
	}*/
	/*float ChannelManager::SetChannelPan(int id, float value)
	{
		float pan;
		pan = FMOD_ChannelGroup_SetPan(m_channelGroup->getChannel[id]);
		return pan;
	}*/

	void ChannelManager::SetPause(bool pause)
	{
		

		FMOD_RESULT result = m_channelGroup->setPaused(pause);
		FMODCheckError(result);
	}

	void ChannelManager::SoundStop()
	{
		FMOD_RESULT result = m_channelGroup->stop();
		FMODCheckError(result);
	}

	// ~~~ Not sure about how to implement this right now ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*void ChannelManager::GetChannelPlaybackPosition(int id, unsigned int& value)
	{
		FMOD_RESULT result = m_channelGroup->getChannel()->getPosition(&value, FMOD_TIMEUNIT_MS);
		FMODCheckError(result);
	}*/

	bool ChannelManager::CheckChannelIsPlaying()
	{
		bool isPlaying;
		FMOD_RESULT result = m_channelGroup->isPlaying(&isPlaying);
		FMODCheckError(result);
		return isPlaying;
	}

	float ChannelManager::GetChannelVolume()
	{
		float volume;
		FMOD_RESULT result = m_channelGroup->getVolume(&volume);
		FMODCheckError(result);
		return volume;		
	}

	float ChannelManager::GetChannelPitch()
	{
		float pitch;
		FMOD_RESULT result = m_channelGroup->getPitch(&pitch);
		FMODCheckError(result);
		return pitch;
	}

	// ~~~ Not sure about how to implement this right now ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*float ChannelManager::GetChannelPan(int id)
	{
		float pan;
		pan = m_channelGroup->pan;
		return pan;
	}*/

	void ChannelManager::GetPauseState(bool& pause)
	{
		FMOD_RESULT result = m_channelGroup->getPaused(&pause);
		FMODCheckError(result);
	}
}