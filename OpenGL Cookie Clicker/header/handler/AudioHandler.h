#pragma once

#include <SimpleAudioLib\CoreSystem.h>

class AudioHandler {

	public:

		static void init();
		static void cleanUp();

		static SimpleAudioLib::CoreSystem& getSystem();

};