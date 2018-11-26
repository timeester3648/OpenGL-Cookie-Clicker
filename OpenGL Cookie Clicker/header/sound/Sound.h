#pragma once

#include <glm\glm.hpp>
#include <string>
#include <SimpleAudioLib\AudioEntity.h>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;

class Sound {

	public:

		Vec3 position = { 0, 0, 0 }, velocity = { 0, 0, 0 }, direction = { 0, 0, 0 };
		float pitch = 1.0f;
		float gain = 1.0f;
		SimpleAudioLib::AudioEntity* audio = nullptr;

	public:

		Sound(std::string name);
		~Sound();

	public:

		void play(bool loop = false);
		void pause();
		void stop();
		void rewind();

		void setDirection(Vec3 direction);
		void setVelocity(Vec3 velocity);
		void setPosition(Vec3 position);
		void setPitch(float pitch);
		void setGain(float gain);

};