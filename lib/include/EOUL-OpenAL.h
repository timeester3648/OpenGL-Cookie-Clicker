#pragma once

#include <EOUL-OpenAL\SoundSystem.h>
#include <EOUL-OpenAL\entity\Audio.h>
#include <EOUL-OpenAL\InstancedBuffer.h>
#include <EOUL-OpenAL\entity\AudioEntity.h>
#include <EOUL-OpenAL\entity\InstancedAudioEntity.h>

#if !defined(_HAS_CXX17) || !_HAS_CXX17
	#error C++17 support is needed!
#endif

#define EOUL_OPENAL_MAKE_VERSION(major, minor, patch) (unsigned int((major << 16) | (minor << 8) | (patch << 0)))
#define EOUL_OPENAL_VERSION_MAJOR 1
#define EOUL_OPENAL_VERSION_MINOR 1
#define EOUL_OPENAL_VERSION_PATCH 0
#define EOUL_OPENAL_GET_VERSION_MAJOR(version) (((version) >> 16) & 0xff)
#define EOUL_OPENAL_GET_VERSION_MINOR(version) (((version) >> 8) & 0xff)
#define EOUL_OPENAL_GET_VERSION_PATCH(version) (((version) >> 0) & 0xff)
#define EOUL_OPENAL_VERSION EOUL_OPENAL_MAKE_VERSION(EOUL_OPENAL_VERSION_MAJOR, EOUL_OPENAL_VERSION_MINOR, EOUL_OPENAL_VERSION_PATCH)

#if defined(EOUL_OPENAL_USE_ALL) || defined(EOUL_USE_ALL)
	using namespace EOUL;
	using namespace OpenAL;
#endif
