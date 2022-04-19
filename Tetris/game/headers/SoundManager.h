#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Sounds
{
	rotation, hardDrop, lineCleared, moveSound, softDrop, transition, gameOver
};

class SoundManager
{
	sf::SoundBuffer rotation;
	sf::SoundBuffer move;
	sf::SoundBuffer softDrop;
	sf::SoundBuffer hardDrop;
	sf::SoundBuffer lineCleared;
	sf::SoundBuffer transition;
	sf::SoundBuffer gameOver;
	sf::Sound sound;
	sf::Sound transitionSound;
	sf::Music backgroundMusic;

	SoundManager();

public:
	static SoundManager& getInstance()
	{
		static SoundManager instance;
		return instance;
	}

	void play(Sounds sound);
	void playBackgroundMusic();
	void stopBackgroundMusic();
};
