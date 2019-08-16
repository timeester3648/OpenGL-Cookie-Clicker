#include "../../header/handler/AudioHandler.h"

#include <EOUL-OpenAL.h>

void AudioHandler::init() {

	EOUL::OpenAL::SoundSystem::init();

}

void AudioHandler::cleanUp() {

	EOUL::OpenAL::SoundSystem::release();

}