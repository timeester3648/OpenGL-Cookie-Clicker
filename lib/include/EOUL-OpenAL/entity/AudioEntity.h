#pragma once

#include <EOUL-OpenAL\entity\Audio.h>

namespace EOUL {

	namespace OpenAL {

		class AudioEntity : public Audio {

			friend class SoundSystem;

			private:

				AudioEntity(char* data, const unsigned int size, const unsigned int frequency, const short numChannels);

		};

	}

}