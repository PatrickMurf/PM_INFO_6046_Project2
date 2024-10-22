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


		//	//Loading related
		//	void LoadAudioStream(const char* source);
		//	void LoadAudio(const char* file);

		//Play sounds related	// OLD
		//	int PlayAudio(const char* audioName);	// OLD

		//Channelgroup creation & playsound related
		void CreateSound(const char* filename, FMOD::Sound* sound);
		void CreateChannelGroup(const char* channelId);

		void PlayAudioChannel(FMOD::Sound* sound, FMOD::Channel* channel);
		void DisplayChannelGroupInfo();
		std::vector<FMOD::Sound*> getSoundsList();
		FMOD::ChannelGroup* getChannelGroup();

		void ModifyChannelGroupDSP();

		//Modification of sound channels
		void SetChannelVolume(float value);
		void SetChannelPitch(float value);
		//float SetChannelPan(int id, float value);	//<- TODO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//Pause and other controls
		void SetPause(bool pause);
		void SoundStop();

		//Get information
		//void GetChannelPlaybackPosition(int id, unsigned int& value);	<- TODO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		bool CheckChannelIsPlaying();

		float GetChannelVolume();
		float GetChannelPitch();
		//float GetChannelPan(int id);	<- TODO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void GetPauseState(bool& pause);
		//void GetAudioLength(int id);		<- This one might not be needed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	};




	// === Old code past here: Some may be required, other might need scrapped =========================================================================================

	struct Audio
	{
		FMOD::Sound* Audio;
		unsigned int length;
	};

	////class ChannelManager
	////{
	////private:
	////	bool m_isInitialized = false;
	////	int m_nextChannelId = 0;

	////	std::vector<Channel*> m_channelList;

	////	FMOD::System* m_System = nullptr;

	////public:
	////	ChannelManager();

	////	~ChannelManager();

	//	std::map<const char*, Audio*> m_audioMap;
	//	const char* soundIndex = "";

	////	//Basic system functions
	////	void Initialize();
	////	void Destroy();
	////	void Update();

	//	//Loading related
	//	void LoadAudioStream(const char* source);
	//	void LoadAudio(const char* file);

	//	//Play sounds related
	//	int PlayAudio(const char* audioName);

	////	//Modification of sound channels
	////	void SetChannelVolume(int id, float value);
	////	void SetChannelPitch(int id, float value);
	////	void SetChannelPan(int id, float value);

	////	//Pause and other controls
	////	void SetPause(int id, bool pause);
	////	void SoudStop(int id);

	////	//Get information
	////	void GetChannelPlaybackPosition(int id, unsigned int& value);
	////	bool CheckChannelIsPlaying(int id);

	////	float GetChannelVolume(int id);
	////	float GetChannelPitch(int id);
	////	float GetChannelPan(int id);

	////	void GetPauseState(int id, bool& pause);
	////	void GetAudioLength(int id);
	////};
}