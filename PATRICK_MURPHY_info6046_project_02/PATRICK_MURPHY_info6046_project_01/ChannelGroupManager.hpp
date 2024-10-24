#pragma once

#include <fmod.hpp>
#include "AudioUtils.hpp"

#include <map>
#include <vector>

namespace audio
{
	struct Channel
	{
		const char* name;
		FMOD::Channel* fmodChannel;
		float volume;
		float pitch;
		float pan;
		bool playing;
	};

	class ChannelManager
	{
	private:
		bool m_isInitialized = false;
		int m_nextChannelId = 0;

		//std::vector<Channel*> m_channelList;	-OLD	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		FMOD::ChannelGroup* m_channelGroup = nullptr;
		std::vector<FMOD::Sound*> m_SoundsList;

		FMOD::System* m_System = nullptr;

	public:
		ChannelManager();
		~ChannelManager();

		//Basic system functions
		void Initialize();
		void Destroy(std::vector<FMOD::Sound*> sounds);
		void Update();

		//Channelgroup creation & playsound related
		void CreateSound(const char* filename, FMOD::Sound* sound);
		void CreateChannelGroup(const char* channelId);

		void PlayAudioChannel(FMOD::Sound* sound, FMOD::Channel* channel);
		void DisplayChannelGroupInfo(FMOD::ChannelGroup* channelGroup);
		std::vector<FMOD::Sound*> getSoundsList();
		FMOD::ChannelGroup* getChannelGroup();
		void setChannelGroup(FMOD::ChannelGroup* channel);

		void ModifyChannelGroupDSP(int dspType);

		//Modification of sound channels
		void SetChannelVolume(float value, FMOD::ChannelGroup* channelGroup);
		void SetChannelPitch(float value, FMOD::ChannelGroup* channelGroup);

		//Pause and other controls
		void SetPause(bool pause);
		void SoundStop();

		//Get information
		bool CheckChannelIsPlaying();

		float GetChannelVolume(FMOD::ChannelGroup* channelGroup);
		float GetChannelPitch(FMOD::ChannelGroup* channelGroup);

		void GetPauseState(bool& pause);
	};




	// === Old code past here: Some may be required, other might need scrapped =========================================================================================

	struct Audio
	{
		FMOD::Sound* Audio;
		unsigned int length;
	};

}