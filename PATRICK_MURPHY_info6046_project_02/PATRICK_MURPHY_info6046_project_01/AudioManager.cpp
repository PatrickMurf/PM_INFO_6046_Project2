#include "AudioManager.hpp"

#include <iostream>
#include "fmod_errors.h"

audio::AudioManager::AudioManager()
{
}

audio::AudioManager::~AudioManager()
{
}

void audio::AudioManager::Initialize()
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

	result = m_System->init(30, FMOD_INIT_NORMAL, nullptr);

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

	printf("AudioManager::Initialize():  Successful!\n");

	for (int i = 0; i < 20; i++)
	{
		m_channelList.push_back(new Channel);
	}

	m_isInitialized = true;
}

void audio::AudioManager::Destroy()
{
	if (!m_isInitialized)
	{
		return;
	}

	FMOD_RESULT result;

	for (std::pair<const char*, Audio*> pair : m_audioMap)
	{
		result = pair.second->Audio->release();
	}

	m_audioMap.clear();

	result = m_System->close();
	FMODCheckError(result);

	result = m_System->release();
	FMODCheckError(result);

	m_isInitialized = false;
}

void audio::AudioManager::Update()
{
	if (!m_isInitialized)
	{
		return;
	}

	FMOD_RESULT result = m_System->update();

	if (result != FMOD_OK)
	{
		FMODCheckError(result);
		Destroy();
	}
}

void audio::AudioManager::LoadAudioStream(const char* source)
{
	if (!m_isInitialized)
		return;

	if (m_audioMap.find(source) != m_audioMap.end())
	{
		printf("AudioManager::LoadAudio() the audio is already loaded!\n");
		return;
	}

	m_audioMap.insert(std::pair<const char*, Audio*>(source, new Audio()));

	FMOD_RESULT result;
	result = m_System->createStream(source, FMOD_DEFAULT, 0, &m_audioMap[source]->Audio);

	if (result != FMOD_OK)
	{
		printf("AudioManager::LoadAudio() Failed to load the Audio stream: $s\n", source);
	}

	printf("AudioManager::LoadAudio($s):  Loaded successfully!\n", source);
}

void audio::AudioManager::LoadAudio(const char* file)
{
	if (!m_isInitialized)
		return;

	if (m_audioMap.find(file) != m_audioMap.end())
	{
		printf("AudioManager::LoadAudio() the audio is already loaded!\n", file);
		return;
	}

	m_audioMap.insert(std::pair<const char*, Audio*>(file, new Audio()));

	FMOD_RESULT result;
	result = m_System->createSound(file, FMOD_DEFAULT, 0, &m_audioMap[file]->Audio);

	unsigned int localLength = 0;
	m_audioMap[file]->Audio->getLength(&localLength, FMOD_TIMEUNIT_MS);
	m_audioMap[file]->length = localLength;

	if (result != FMOD_OK)
	{
		printf("AudioManager::LoadAudio() Failed to load the Audio stream: $s\n", file);
	}

	printf("AudioManager::LoadAudio($s):  Loaded successfully!\n");
}

int audio::AudioManager::PlayAudio(const char* audioName)
{
	if (!m_isInitialized)
	{
		printf("This has not been Initialized!\n");
		return m_nextChannelId;
	}

	std::map<const char*, Audio*>::iterator iter = m_audioMap.find(audioName);

	if (iter == m_audioMap.end())
	{
		printf("Audio not found!\n");
		return m_nextChannelId;
	}

	int channelId = m_nextChannelId;
	m_nextChannelId = (m_nextChannelId + 1) % 20;
	Channel* channel = m_channelList[channelId];

	FMOD_RESULT result = m_System->playSound(iter->second->Audio, 0, false, &channel->fmodChannel);
	FMODCheckError(result);
		
	return channelId;
}

void audio::AudioManager::SetChannelVolume(int id, float value)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->setVolume(value);
	//std::cout << FMOD_ErrorString(result);
	FMODCheckError(result);
}

void audio::AudioManager::SetChannelPitch(int id, float value)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->setPitch(value);
	FMODCheckError(result);
}

void audio::AudioManager::SetChannelPan(int id, float value)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->setPan(value);
	m_channelList[id]->pan = value;
	FMODCheckError(result);
}

void audio::AudioManager::SetPause(int id, bool pause)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->setPaused(pause);
	FMODCheckError(result);
}

void audio::AudioManager::SoudStop(int id)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->stop();
	FMODCheckError(result);
}

void audio::AudioManager::GetChannelPlaybackPosition(int id, unsigned int& value)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->getPosition(&value, FMOD_TIMEUNIT_MS);
	FMODCheckError(result);
}

bool audio::AudioManager::CheckChannelIsPlaying(int id)
{
	bool isPlaying;
	FMOD_RESULT result = m_channelList[id]->fmodChannel->isPlaying(&isPlaying);
	FMODCheckError(result);
	return isPlaying;
}

float audio::AudioManager::GetChannelVolume(int id)
{
	float volume;
	FMOD_RESULT result = m_channelList[id]->fmodChannel->getVolume(&volume);
	FMODCheckError(result);
	return volume;
}

float audio::AudioManager::GetChannelPitch(int id)
{
	float pitch;
	FMOD_RESULT result = m_channelList[id]->fmodChannel->getPitch(&pitch);
	FMODCheckError(result);
	return pitch;
}

float audio::AudioManager::GetChannelPan(int id)
{
	float pan;
	pan = m_channelList[id]->pan;
	return pan;
}

void audio::AudioManager::GetPauseState(int id, bool& pause)
{
	FMOD_RESULT result = m_channelList[id]->fmodChannel->getPaused(&pause);
	FMODCheckError(result);
}

void audio::AudioManager::GetAudioLength(int id)
{
	//FMOD_RESULT Studio::EventDescription::getLength( int* length );
	//FMOD_RESULT result = m_channelList[id]->fmodChannel->getLength(); // Do this in milliseconds?

	//FMODCheckError(result);

	//m_channelList[id]->fmodChannel->getCurrentSound()
}
