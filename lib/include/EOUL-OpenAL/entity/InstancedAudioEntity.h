#pragma once

#include <EOUL-OpenAL\entity\Audio.h>
#include <EOUL-OpenAL\InstancedBuffer.h>

namespace EOUL {

	namespace OpenAL {

		class InstancedAudioEntity : public Audio {

			friend class SoundSystem;

			private:

				const InstancedBuffer& buffer;

			private:

				InstancedAudioEntity(const InstancedBuffer& buffer);

		};

	}

}