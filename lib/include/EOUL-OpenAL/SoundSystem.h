#pragma once

namespace EOUL::dependencies {

	#include <AL\al.h>
	#include <AL\alc.h>

}

#include <string>
#include <filesystem>
#include <EOUL-OpenAL\entity\AudioEntity.h>
#include <EOUL-OpenAL\entity\InstancedAudioEntity.h>

namespace EOUL {

	namespace OpenAL {

		class SoundSystem {

			private:

				struct WavData {

					short formatTag = 0;
					short channels = 0;
					int samplesPerSec = 0;
					int averageBytesPerSec = 0;
					short blockAlign = 0;
					short bitsPerSample = 0;
					std::unique_ptr<char[]> data;
					size_t size;

				};

			public:

				enum class FileType {

					WavFile

				};

			private:

				static dependencies::ALCdevice* device;
				static dependencies::ALCcontext* context;

			private:

				SoundSystem() = delete;
				SoundSystem(const SoundSystem& other) = delete;
				SoundSystem(SoundSystem&&) = delete;

			public:

				static std::vector<std::string> enumerateDevices();

				static AudioEntity* loadToAudioEntity(const short* samples, unsigned int sampleCount, unsigned int channelCount = 1u, unsigned int sampleRate = 44100u);
				static AudioEntity* loadToAudioEntity(const std::filesystem::path&, FileType type);

				static InstancedBuffer loadInstancedBuffer(const short* samples, unsigned int sampleCount, unsigned int channelCount = 1u, unsigned int sampleRate = 44100u);
				static InstancedBuffer loadInstancedBuffer(const std::filesystem::path&, FileType type);

				static InstancedAudioEntity* loadToInstancedAudioEntity(const InstancedBuffer& buffer);

				static void setListenerPosition(float x, float y, float z);
				static void setListenerVelocity(float x, float y, float z);
				static void setListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ);

				static void init(const std::string& deviceName = "default");
				static void release();

			private:

				static WavData loadWavFile(const std::filesystem::path& path);

		};

	}

}