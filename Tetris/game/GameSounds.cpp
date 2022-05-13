#include "headers/GameSounds.h"

GameSound::GameSound()
{
	rotation.loadFromFile("resources/sounds/Rotate.wav");
	move.loadFromFile("resources/sounds/MoveSound.wav");
	softDrop.loadFromFile("resources/sounds/SoftDrop.wav");
	hardDrop.loadFromFile("resources/sounds/HardDrop.wav");
	lineCleared.loadFromFile("resources/sounds/LineCleared.wav");
	transition.loadFromFile("resources/sounds/Transition.wav");
	gameOver.loadFromFile("resources/sounds/GameOver.wav");
	transitionSound.setBuffer(transition);

	backgroundMusic.openFromFile("resources/sounds/BackgroundMusic.ogg");
	backgroundMusic.setLoop(true);
}

void GameSound::setVolume()
{
	sound.setVolume(SoundVolume::getInstance().getVolume(Volume::effects));
	transitionSound.setVolume(SoundVolume::getInstance().getVolume(Volume::effects));
	backgroundMusic.setVolume(SoundVolume::getInstance().getVolume(Volume::music));
}

void GameSound::play(Sounds sound)
{
	switch (sound)
	{
	case Sounds::rotation:
		this->sound.setBuffer(rotation);
		this->sound.play();
		break;
	case Sounds::hardDrop:
		this->sound.setBuffer(hardDrop);
		this->sound.play();
		break;
	case Sounds::lineCleared:
		this->sound.setBuffer(lineCleared);
		this->sound.play();
		break;
	case Sounds::moveSound:
		this->sound.setBuffer(move);
		this->sound.play();
		break;
	case Sounds::softDrop:
		this->sound.setBuffer(softDrop);
		this->sound.play();
		break;
	case Sounds::transition:
		this->transitionSound.play();
		break;
	case Sounds::gameOver:
		this->sound.setBuffer(gameOver);
		this->sound.play();
		break;
	}	
}

void GameSound::playBackgroundMusic()
{
	backgroundMusic.play();
}

void GameSound::stopBackgroundMusic()
{
	backgroundMusic.stop();
}
