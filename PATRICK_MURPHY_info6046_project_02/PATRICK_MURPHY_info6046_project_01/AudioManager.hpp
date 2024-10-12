#pragma once

#include <fmod.hpp>
#include "AudioUtils.hpp"

#include <map>
#include <vector>

namespace audio
{
	struct Audio
	{
		FMOD::Sound* Audio;
		unsigned int length;
	};

	struct Channel
	{
		const char* name;
		FMOD::Channel* fmodChannel;
		float volume;
		float pitch;
		float pan;
		bool playing;
	};

	class AudioManager
	{
	private:
		bool m_isInitialized = false;
		int m_nextChannelId = 0;

		std::vector<Channel*> m_channelList;

		FMOD::System* m_System = nullptr;

	public:
		AudioManager();

		~AudioManager();

		std::map<const char*, Audio*> m_audioMap;
		const char* soundIndex = "";

		//Basic system functions
		void Initialize();
		void Destroy();
		void Update();

		//Loading related
		void LoadAudioStream(const char* source);
		void LoadAudio(const char* file);

		//Play sounds related
		int PlayAudio(const char* audioName);

		//Modification of sound channels
		void SetChannelVolume(int id, float value);
		void SetChannelPitch(int id, float value);
		void SetChannelPan(int id, float value);

		//Pause and other controls
		void SetPause(int id, bool pause);
		void SoudStop(int id);

		//Get information
		void GetChannelPlaybackPosition(int id, unsigned int& value);
		bool CheckChannelIsPlaying(int id);

		float GetChannelVolume(int id);
		float GetChannelPitch(int id);
		float GetChannelPan(int id);

		void GetPauseState(int id, bool& pause);
		void GetAudioLength(int id);
	};
}