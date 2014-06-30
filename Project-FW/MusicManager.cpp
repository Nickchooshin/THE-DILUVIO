#include "MusicManager.h"

/*#ifndef _DEBUG
#pragma comment (lib, "fmodex_vc.lib")
#else
#pragma comment (lib, "fmodexL_vc.lib")
#endif*/

MusicManager::MusicManager(void)
{
	Sounds.clear();
	for (int i=0; i < 32; i++)
		Channels[i] = NULL;
}

MusicManager::~MusicManager(void)
{
	Terminate() ;
}

bool MusicManager::Initialize()
{
	FMOD_RESULT Result;

	Result = FMOD::System_Create(&System);
	if (Result != FMOD_OK)
		return false;

 
	Result = System->init(320, FMOD_INIT_NORMAL, 0);
	if (Result != FMOD_OK)
		return false;
		
	return true;
}

void MusicManager::Terminate()
{
	unsigned int i;
	for (i=0; i < Sounds.size(); i++)
		Sounds[i]->release();
	Sounds.clear();
	for (int i=0; i < 32; i++)
		Channels[i] = NULL;
	System->close();
	System->release();
}

FMOD::Sound* MusicManager::LoadMusic(char *Filename, bool isStream, bool isLoop)
{
	FMOD::Sound * temp;

	if (isStream)
		System->createStream(Filename, FMOD_SOFTWARE | (isLoop?FMOD_LOOP_NORMAL:0x00) | FMOD_2D, 0, &temp);
	else
		System->createSound(Filename, FMOD_SOFTWARE | (isLoop?FMOD_LOOP_NORMAL:0x00) | FMOD_2D, 0, &temp);

	Sounds.push_back(temp);

	return temp;
}

void MusicManager::PlayMusic(FMOD::Sound* Sound, int Channel)
{
	if (Channel > 32)
		return;

	System->playSound(FMOD_CHANNEL_FREE, Sound, false, &Channels[Channel]);
}

void MusicManager::StopMusic(int Channel)
{
	if (Channel > 32)
		return;

	bool bPlay;
	Channels[Channel]->isPlaying(&bPlay);
	
	if (bPlay)
		Channels[Channel]->stop();
}

void MusicManager::Loop()
{
	System->update();
}

void MusicManager::Reset()
{
	MusicManager::Terminate();
	MusicManager::Initialize();
}
