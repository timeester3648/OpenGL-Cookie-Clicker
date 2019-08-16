#pragma once

namespace EOUL::dependencies {

	#include <AL\al.h>
	#include <AL\alc.h>

}

namespace EOUL {

	namespace OpenAL {

		class InstancedBuffer {

			friend class AudioEntity;
			friend class SoundSystem;
			friend class InstancedAudioEntity;

			private:

				dependencies::ALCuint buffer;

			public:

				InstancedBuffer(unsigned int buffer);
				InstancedBuffer(char* data, const unsigned int size, const unsigned int frequency, const short numChannels);
				~InstancedBuffer();

			private:

				void release();

		};

	}

}