#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../game/headers/Button.h"
#include "../game/headers/GameApp.h"
#include "../game/headers/Global.h"

class HighscoreManager
{
	struct highscores
	{
		std::array < std::pair<int, std::string>, 5> arr;
		void saveSocore(std::pair<int, std::string>);
		int getLowest();
	} highScores;
	sf::Font font;
	std::array < sf::Text, 5> nameTexts;
	std::array < sf::Text, 5> scoreTexts;
	sf::Texture backTexture;
	sf::Sprite backSprite;
	sf::Texture nameTexture;
	sf::Sprite nameSprite;

	void loadFromFile();
	void setTexts();
	void setTextString();
	std::string getName(sf::RenderWindow* window, int score);

public:
	HighscoreManager();
	~HighscoreManager();

	void update(int score, sf::RenderWindow* window);
	void display(sf::RenderWindow* window);
};

class Menu
{
	sf::RenderWindow* window;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	GameApp* game;
	Button* play;
	Button* highscores;
	Button* options;
	Button* exit;
	ButtonManager* buttons;

	class LvlSelector
	{
	public:
		int level = 0;
		Button* up;
		Button* down;
		sf::Text text;
		sf::Font font;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Sprite sprite;
		sf::Texture texture;
		float cooldown = 0.1f;
		bool enterUnpressed = false;

		LvlSelector();
		~LvlSelector();
		void incrementLevel();
		void decrementLevel();
		void userInput(sf::RenderWindow* window);
		void display(sf::RenderWindow* window);
	} lvlSelector;
	class OptionsMenu
	{
	public:
		sf::RenderWindow* window;
		Button* menuUp; void incrementMenu() { changeVolumeOpt(Volume::menu, 10); }
		Button* menuDown; void decrementMenu() { changeVolumeOpt(Volume::menu, -10); }
		Button* effectsUp; void incrementEffects() { changeVolumeOpt(Volume::effects, 10); }
		Button* effectsDown; void decrementEffects() { changeVolumeOpt(Volume::effects, -10); }
		Button* musicUp; void incrementMusic() { changeVolumeOpt(Volume::music, 10); }
		Button* musicDown; void decrementMusic() { changeVolumeOpt(Volume::music, -10); }
		Button* Controls; 
		ButtonManager* buttons; 
		float clickCooldown = -0.5f;
		sf::Font font;
		sf::Text menuText;
		sf::Text musicText;
		sf::Text effectsText;
		sf::Texture textureOptions;
		sf::Sprite optionsSprite;
		sf::Texture textureControls;
		sf::Sprite controlsSprite;

		OptionsMenu();
		~OptionsMenu();
		void updateText();
		void changeVolumeOpt(Volume vol, int val);
		void displayControls();
		void display(sf::RenderWindow* window);
	} optionsMenu;
	HighscoreManager highscoresMan;

private:
	bool checkIfButtonPressed(ButtonManager* buttons);
	void runGame();
	int levelSelector();
	void optionsMenuScene();
	void highscoresScene();
	void display();
	void close();
	void wait(float time);

public:
	Menu();
	~Menu();
	int exitGame();
	void update();
};
