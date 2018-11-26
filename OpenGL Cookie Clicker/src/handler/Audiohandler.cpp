#include "../../header/handler/AudioHandler.h"

void AudioHandler::init() {

	getSystem().initWithDefaultDevice();

}

SimpleAudioLib::CoreSystem& AudioHandler::getSystem() {

	static SimpleAudioLib::CoreSystem& system = SimpleAudioLib::CoreSystem::getInstance();

	return system;

}

void AudioHandler::cleanUp() {

	SimpleAudioLib::CoreSystem::release();

}