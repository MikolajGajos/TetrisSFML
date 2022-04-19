#include "headers/GameApp.h"

class FPS
{
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {}

	/// @brief Update the frame count.
	/// 


	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if (mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}
};

//Returns random number between [0,6].
int random()
{
	std::random_device random_device;
	std::default_random_engine random_engine(random_device());
	std::uniform_int_distribution<unsigned short> distr(0, 6);
	return distr(random_engine);
}

void closingWindowEvent(sf::RenderWindow* window)
{
	sf::Event event;
	(*window).pollEvent(event);
	if (event.type == sf::Event::Closed)
		(*window).close();
}

void prepareVector(std::vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i] += i;
	}
}

void GameApp::pauseManagement()
{
	if (pauseAllowed)
		if (pause->checkForPause())
			pauseAllowed = false;

	if (!pauseAllowed)
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			pauseAllowed = true;
}

GameApp::GameApp(sf::RenderWindow* window,int statringLevel): window(window)
{
	this->pause = new PauseMenu(window);
	this->tileTexture.loadFromFile("resources/images/Tile.png");
	this->gameOverTexture.loadFromFile("resources/images/GameOver.png");
	this->gameOverSprite.setTexture(this->gameOverTexture);

	for (unsigned char i = 0; i < (*windowPosition).size(); i++)
	{
		for (unsigned char j = 0; j < (*windowPosition)[i].size(); j++)
		{
			(*windowPosition)[i][j].setPosition(i * (CELL_SIZE), j * (CELL_SIZE));
		}
	}
	float x = (*windowPosition)[MATRIX_POS_X][MATRIX_POS_X].getPosition().x / CELL_SIZE;
	float y = (*windowPosition)[MATRIX_POS_Y][MATRIX_POS_Y].getPosition().y / CELL_SIZE - 2;
	for (unsigned char i = 0; i < (*matrix).size(); i++)
	{
		for (unsigned char j = 0; j < (*matrix)[i].size(); j++)
		{
			(*matrix)[i][j].setFull(false);
			(*matrix)[i][j].setPosition({ CELL_SIZE * (i + x), CELL_SIZE * (j + y) });
			(*matrix)[i][j].setTexture(this->tileTexture);
		}
	}
	if (this->level > 29)
		this->level = 29;
	else
		this->level = statringLevel;
	setUpSC();
}

GameApp::~GameApp()
{
	delete windowPosition;
	delete matrix;
	delete pause;
}

void GameApp::tetromnoMovement(Tetromino& tetromino)
{	
	if (rotationAllowed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			tetromino.rotate(true);
			rotationAllowed = false;
			SoundManager::getInstance().play(Sounds::rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			tetromino.rotate(false);
			rotationAllowed = false;
			SoundManager::getInstance().play(Sounds::rotation);
		}
	}
	else
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			rotationAllowed = true;
	}

	if (moveTimeCooldown <= 0.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			tetromino.moveLeft();
			moveTimeCooldownReset();
			SoundManager::getInstance().play(Sounds::moveSound);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			tetromino.moveRight();
			moveTimeCooldownReset();
			SoundManager::getInstance().play(Sounds::moveSound);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && softDropCooldown <= 0.f)
	{
		this->dropTime = 0.f;
		softDropCooldownReset();
		SoundManager::getInstance().play(Sounds::softDrop);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hardDropCooldown <= 0.f)
	{
		tetromino.hardDrop();
		hardDropCooldownReset();
		this->dropTime = 0.f;
		SoundManager::getInstance().play(Sounds::hardDrop);
	}
}

bool GameApp::fallingTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino)
{
	if (dropTime > 0.f)
		return false;

	if (tetromino.update()) //true == at the end
	{
		tetromino.updateMatrix();
		tetromino.reset(nextTetromino.getShape());

		if (this->gameOver(tetromino)) //check if tetrmino can spawn
		{
			this->gameOverbool = true;
			return false;
		}

		nextTetromino.reset(getShape(random()));
		ghostTetromino.reset(tetromino);
		dropTimeReset();
		return true;
	}
	dropTimeReset();
	return false;
}

std::vector<int> GameApp::fullLines()
{
	std::vector<int> v;
	//loop begins from bottom
	for (unsigned char y = (*matrix)[0].size() - 1; y > 0; y--)
	{
		bool full = true;
		//loop checks every collumn in one row
		for (unsigned char x = 0; x < COLUMNS; x++)
		{
			//if the tile is not full stops
			if (!(*matrix)[x][y].isFull())
			{
				full = false;
				break;
			}
				
		}
		//if every tile was full
		if (full)
		{
			for (unsigned char x = 0; x < COLUMNS; x++)
			{
				(*matrix)[x][y].setFull(false);
			}

			v.push_back(y);
			inAnimation = true;
			SoundManager::getInstance().play(Sounds::lineCleared);
		}
			
	}
	return v;
}

void GameApp::clearLines(std::vector<int>& linesNumber)
{
	if (linesNumber.empty())
		return;

	//score and level management
	for (int i : linesNumber)
	{
		this->linesUntilTransition -= 1;
		if (this->linesUntilTransition == 0)
		{
			transtionLevel();
			SoundManager::getInstance().play(Sounds::transition);
		}
			
	}	
	this->clearedLines += linesNumber.size();
	this->score += scoreIncrease(linesNumber.size());	
	prepareVector(linesNumber);

	//loop moves every line one row down
	for (int y : linesNumber)
	{
		for (unsigned char _y = y; _y > 0; _y--)
		{
			for (unsigned char x = 0; x < COLUMNS; x++)
			{
				(*matrix)[x][_y].setFull((*matrix)[x][_y - 1].isFull());
				(*matrix)[x][_y].setColor((*matrix)[x][_y - 1].getColor());
			}
		}
	}	
	linesNumber.clear();
	TextManager::getInstance().updateText();
}

void GameApp::animationManager(std::vector<int>& linesNumber)
{
	this->animationTime -= DeltaTime::getInstance().getDT();
	Animation::getInstance().update();
	if (animationTime < 0.f)
	{
		this->inAnimation = false;
		animationTimeReset();
		Animation::getInstance().reset();
		clearLines(linesNumber);
	}
}

void GameApp::drawBoard()
{
	for (unsigned char i = 0; i < (*matrix).size(); i++)
	{
		for (unsigned char j = 0; j < (*matrix)[i].size(); j++)
		{
			if ((*matrix)[i][j].isFull())
			{				
				(*window).draw((*matrix)[i][j]);
			}
		}
	}
}

void GameApp::drawTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino)
{
	if (gameOverbool)
		return;

	tetromino.display(*window);
	ghostTetromino.display(*window);
	nextTetromino.display(*window);
}

bool GameApp::gameOver(Tetromino& tetromino)
{
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		if ((*matrix)[i][1].isFull())
		{
			SoundManager::getInstance().play(Sounds::gameOver);
			SoundManager::getInstance().stopBackgroundMusic();
			return true;
		}
	}

	return false;
}

void GameApp::endGame(sf::Sprite& sprite)
{
	window->clear(sf::Color::Black);
	window->draw(BackgroundManager::getInstance());
	window->draw(TextManager::getInstance());
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		for (unsigned char j = 2; j < matrix[0].size(); j++)
		{
			if ((*matrix)[i][j].isFull())
			{
				(*matrix)[i][j].setTexture(this->tileTexture);
				(*matrix)[i][j].setColor(sf::Color(70, 70, 70, 255));
				window->draw((*matrix)[i][j]);
			}
		}
	}
	window->draw(sprite);
	window->display();

	closingWindowEvent(window);
}

void GameApp::updateGame(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino, std::vector<int>& linesToClear)
{
	if (gameOverbool)
	{
		endGame(gameOverSprite);
		return;
	}

	pauseManagement();

	closingWindowEvent(window);

	if (!inAnimation)
	{
		tetromnoMovement(tetromino);
		ghostTetromino.updateGhost(tetromino);
		if (fallingTetromino(tetromino, ghostTetromino, nextTetromino))
			linesToClear = fullLines();
	}
	else
		animationManager(linesToClear);
}

void GameApp::displayGame(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino, std::vector<int>& linesToClear)
{
	if (gameOverbool)
	{
		return;
	}
	(*window).draw(BackgroundManager::getInstance());
	drawBoard();
	drawTetromino(tetromino, ghostTetromino, nextTetromino);
	(*window).draw(TextManager::getInstance());
	Animation::getInstance().display(*window, linesToClear);
	(*window).display();
}

void GameApp::manageTimers()
{
	if (gameOverbool)
	{
		return;
	}
	dropTime -= DeltaTime::getInstance().getDT();
	hardDropCooldown -= DeltaTime::getInstance().getDT();
	softDropCooldown -= DeltaTime::getInstance().getDT();
	moveTimeCooldown -= DeltaTime::getInstance().getDT();
	DeltaTime::getInstance().update();
}

int GameApp::run()
{
	Tetromino tetromino(getShape(random()), matrix);
	GhostTetromino ghostTetromino(tetromino);
	NextTetromino nextTetromino(getShape(random()), windowPosition);
	TextManager::getInstance().set(*windowPosition, this->clearedLines, this->level, this->score);
	Animation::getInstance().set(*matrix, this->animationTime);
	SoundManager::getInstance().playBackgroundMusic();
	std::vector<int> linesToClear;

	FPS fps;

	while (window->isOpen())
	{
		updateGame(tetromino, ghostTetromino, nextTetromino, linesToClear);
		displayGame(tetromino, ghostTetromino, nextTetromino, linesToClear);		
		manageTimers();	

		fps.update();
		std::cout << fps.getFPS() << std::endl;
	}
	return this->score;
}
