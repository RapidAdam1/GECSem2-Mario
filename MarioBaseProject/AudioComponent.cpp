#include "AudioComponent.h"
#include "SDL_mixer.h"



AudioComponent::AudioComponent()
{
}

AudioComponent::~AudioComponent()
{
	FreeAudio();
}

bool AudioComponent::LoadAudioFromFile(std::string path, bool looping, int channel)
{
	//Remove Memory of Previous Sound
	FreeAudio();
	

	//Load Audio
	m_sound = Mix_LoadWAV(path.c_str());
	if (m_sound == nullptr)
	{
		std::cout << "Failed to load sound. Error: " << Mix_GetError() << std::endl;
	}
	else 
	{
	PlayAudio();
	return m_sound != nullptr;
	}
}

void AudioComponent::PlayAudio()
{
	Mix_PlayChannel(m_channel, m_sound, m_looping);
}


void AudioComponent::FreeAudio()
{
	if (m_sound != nullptr) 
	{
		delete m_sound;
		m_sound = nullptr;
	}
}
