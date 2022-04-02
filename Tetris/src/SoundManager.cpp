#include "SoundManager.h"

SoundManager::SoundManager()
{
	rotation.loadFromFile("src/sounds/Rotate.wav");
	move.loadFromFile("src/sounds/MoveSound.wav");
	softDrop.loadFromFile("src/sounds/SoftDrop.wav");
	hardDrop.loadFromFile("src/sounds/HardDrop.wav");
	lineCleared.loadFromFile("src/sounds/LineCleared.wav");
	transition.loadFromFile("src/sounds/Transition.wav");
	gameOver.loadFromFile("src/sounds/GameOver.wav");
	transitionSound.setBuffer(transition);

	backgroundMusic.openFromFile("src/sounds/BackgroundMusic.ogg");
	backgroundMusic.setLoop(true);
}

void SoundManager::play(Sounds sound)
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

void SoundManager::playBackgroundMusic()
{
	backgroundMusic.play();
}
