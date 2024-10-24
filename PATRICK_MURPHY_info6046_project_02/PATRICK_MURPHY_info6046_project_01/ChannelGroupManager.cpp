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
			result = sound->release();
			FMODCheckError(result);
		}

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

	void ChannelManager::setChannelGroup(FMOD::ChannelGroup* channel)
	{
		m_channelGroup = channel;
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

	void ChannelManager::ModifyChannelGroupDSP(int dspType)
	{
		if (!m_isInitialized)
		{
			return;
		}

		if (dspType == 0)
		{
			// Echo
			FMOD::DSP* dspTypeEcho;
			FMOD_RESULT resultEcho = m_System->createDSPByType(FMOD_DSP_TYPE_ECHO, &dspTypeEcho);

			if (resultEcho != FMOD_OK)
			{
				FMODCheckError(resultEcho);
				return;
			}

			resultEcho = dspTypeEcho->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.8f);

			if (resultEcho != FMOD_OK)
			{
				FMODCheckError(resultEcho);
				return;
			}

			m_channelGroup->addDSP(0, dspTypeEcho);
		}

		if (dspType == 1)
		{
			// Distortion
			FMOD::DSP* dspTypeDistortion;
			FMOD_RESULT resultDistortion = m_System->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &dspTypeDistortion);

			if (resultDistortion != FMOD_OK)
			{
				FMODCheckError(resultDistortion);
				return;
			}

			resultDistortion = dspTypeDistortion->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.8f);

			if (resultDistortion != FMOD_OK)
			{
				FMODCheckError(resultDistortion);
				return;
			}

			m_channelGroup->addDSP(1, dspTypeDistortion);
		}

		if (dspType == 2)
		{
			// Chorus
			FMOD::DSP* dspTypeChorus;
			FMOD_RESULT resultChorus = m_System->createDSPByType(FMOD_DSP_TYPE_CHORUS, &dspTypeChorus);

			if (resultChorus != FMOD_OK)
			{
				FMODCheckError(resultChorus);
				return;
			}

			resultChorus = dspTypeChorus->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.8f);

			if (resultChorus != FMOD_OK)
			{
				FMODCheckError(resultChorus);
				return;
			}

			m_channelGroup->addDSP(2, dspTypeChorus);
		}
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

	void ChannelManager::DisplayChannelGroupInfo(FMOD::ChannelGroup* channelGroup)
	{
		float retriveVolume = GetChannelVolume(channelGroup);
		float retrivePitch = GetChannelPitch(channelGroup);
		printf("\n\n\n");
		printf("The volume is: %f\n", retriveVolume);
		printf("The pitch is: %f\n", retrivePitch);
	}






	void ChannelManager::SetChannelVolume(float value, FMOD::ChannelGroup* channelGroup)
	{
		FMOD_RESULT result = channelGroup->setVolume(value);
		FMODCheckError(result);
	}

	void ChannelManager::SetChannelPitch(float value, FMOD::ChannelGroup* channelGroup)
	{
		FMOD_RESULT result = channelGroup->setPitch(value);
		FMODCheckError(result);
	}

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

	bool ChannelManager::CheckChannelIsPlaying()
	{
		bool isPlaying;
		FMOD_RESULT result = m_channelGroup->isPlaying(&isPlaying);
		FMODCheckError(result);
		return isPlaying;
	}

	float ChannelManager::GetChannelVolume(FMOD::ChannelGroup* channelGroup)
	{
		float volume;
		FMOD_RESULT result = channelGroup->getVolume(&volume);
		FMODCheckError(result);
		return volume;		
	}

	float ChannelManager::GetChannelPitch(FMOD::ChannelGroup* channelGroup)
	{
		float pitch;
		FMOD_RESULT result = channelGroup->getPitch(&pitch);
		FMODCheckError(result);
		return pitch;
	}

	void ChannelManager::GetPauseState(bool& pause)
	{
		FMOD_RESULT result = m_channelGroup->getPaused(&pause);
		FMODCheckError(result);
	}
}