#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Sounds
{
	rotation, hardDrop, lineCleared, moveSound, softDrop, transition, gameOver
};

class GameSound
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


public:
	GameSound();

	void play(Sounds sound);
	void playBackgroundMusic();
	void stopBackgroundMusic();
};
