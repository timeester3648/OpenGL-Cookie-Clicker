#include "../../header/sound/Sound.h"
#include "../../header/handler/AudioHandler.h"

Sound::Sound(std::string name) {

	this->audio = AudioHandler::getSystem().createAudioEntityFromFile("res/sounds/" + name + ".wav");

}

Sound::~Sound() {

	this->audio->release();

}

void Sound::play(bool loop) {

	this->audio->play(loop);

}

void Sound::pause() {

	this->audio->pause();

}

void Sound::stop() {

	this->audio->stop();

}

void Sound::rewind() {

	this->audio->rewind();

}

void Sound::setDirection(Vec3 direction) {

	this->direction = direction;
	this->audio->setDirection(this->direction.x, this->direction.y, this->direction.z);

}

void Sound::setVelocity(Vec3 velocity) {

	this->velocity = velocity;
	this->audio->setVelocity(this->velocity.x, this->velocity.y, this->velocity.z);

}

void Sound::setPosition(Vec3 position) {

	this->position = position;
	this->audio->setPosition(this->position.x, this->position.y, this->position.z);

}

void Sound::setPitch(float pitch) {

	this->pitch = pitch;
	this->audio->setPitch(this->pitch);

}

void Sound::setGain(float gain) {

	this->gain = gain;
	this->audio->setGain(this->gain);

}