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

void prepareVector(std::vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i] += i;
	}
}

void closingWindowEvent(sf::RenderWindow* window)
{
	sf::Event event;
	(*window).pollEvent(event);
	if (event.type == sf::Event::Closed)
		(*window).close();
}

PauseOutput GameApp::pauseManagement()
{
	if (!pauseAllowed)
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pauseAllowed = true;
			return PauseOutput::noPause;
		}

	return pause->checkForPause();
}

GameApp::GameApp(sf::RenderWindow* window) : window(window)
{
	for (unsigned char i = 0; i < (*windowPosition).size(); i++)
	{
		for (unsigned char j = 0; j < (*windowPosition)[i].size(); j++)
		{
			(*windowPosition)[i][j].setPosition(i * (CELL_SIZE), j * (CELL_SIZE));
		}
	}
	float offsetX = (*windowPosition)[MATRIX_POS_X][MATRIX_POS_X].getPosition().x / CELL_SIZE;
	float offsetY = (*windowPosition)[MATRIX_POS_Y][MATRIX_POS_Y].getPosition().y / CELL_SIZE - 2;
	for (unsigned char i = 0; i < (*gameBoard).size(); i++)
	{
		for (unsigned char j = 0; j < (*gameBoard)[i].size(); j++)
		{
			(*gameBoard)[i][j].setFull(false);
			(*gameBoard)[i][j].setPosition({ CELL_SIZE * (i + offsetX), CELL_SIZE * (j + offsetY) });
		}
	}
	setUpSC();
	this->pause = new PauseMenu(window, &score, &level, &clearedLines);
	this->gameText.set(*windowPosition, this->clearedLines, this->level, this->score);
	this->gameAnimation = new Animation(*gameBoard, this->animationTime);

	this->nextTetromino = new NextTetromino(getRandomShape(random()), windowPosition);
	this->tetromino = new Tetromino(gameBoard);
	this->tetromino->reset(nextTetromino->getShape());
	this->ghostTetromino = new GhostTetromino(gameBoard);
	this->ghostTetromino->reset(*tetromino);
}

GameApp::~GameApp()
{
	delete windowPosition;
	delete gameBoard;
	delete pause;
	delete gameAnimation;
	delete tetromino;
	delete ghostTetromino;
	delete nextTetromino;
}

void GameApp::wait(float time)
{
	sf::Font font;
	sf::Text text;
	font.loadFromFile("resources/images/slkscr.ttf");
	text.setCharacterSize(600);
	text.setFont(font);
	text.setPosition((*windowPosition)[5][0].getPosition());
	text.setStyle(sf::Text::Bold);

	while (window->isOpen())
	{
		DeltaTime::getInstance().update();		
		window->clear(sf::Color::Black);
		closingWindowEvent(window);
		drawGame();

 		text.setString(std::to_string((int)std::round(time)));
		window->draw(text);
		window->display();

		time -= DeltaTime::getInstance().getDT();
		if (time <= 0.f)
			return;
	}
}

void GameApp::tetromnoMovement()
{	
	if (rotationAllowed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			tetromino->rotate(true);
			rotationAllowed = false;
			gameSound.play(Sounds::rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			tetromino->rotate(false);
			rotationAllowed = false;
			gameSound.play(Sounds::rotation);
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
			tetromino->moveLeft();
			moveTimeCooldownReset();
			gameSound.play(Sounds::moveSound);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			tetromino->moveRight();
			moveTimeCooldownReset();
			gameSound.play(Sounds::moveSound);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && softDropCooldown <= 0.f)
	{
		this->dropTime = 0.f;
		softDropCooldownReset();
		gameSound.play(Sounds::softDrop);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hardDropCooldown <= 0.f)
	{
		tetromino->hardDrop();
		hardDropCooldownReset();
		this->dropTime = 0.f;
		gameSound.play(Sounds::hardDrop);
	}
}

bool GameApp::fallingTetromino()
{
	if (dropTime > 0.f)
		return false;

	if (tetromino->update()) //true == at the end
	{
		tetromino->updateMatrix();
		tetromino->reset(nextTetromino->getShape());

		if (this->gameOver()) //check if tetrmino can spawn
		{
			this->gameOverbool = true;
			return false;
		}

		nextTetromino->reset(getRandomShape(random()));
		ghostTetromino->reset(*tetromino);
		dropTimeReset();
		return true;
	}
	dropTimeReset();
	return false;
}

void GameApp::fullLines()
{
	std::vector<int> v;
	//loop begins from bottom
	for (unsigned char y = (*gameBoard)[0].size() - 1; y > 0; y--)
	{
		bool full = true;
		//loop checks every collumn in one row
		for (unsigned char x = 0; x < COLUMNS; x++)
		{
			//if the tile is not full stops
			if (!(*gameBoard)[x][y].isFull())
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
				(*gameBoard)[x][y].setFull(false);
			}

			v.push_back(y);
			gameSound.play(Sounds::lineCleared);
		}
			
	}
	if (!v.empty())
	{
		gameAnimation->display(window, v);
		clearLines(v);
	}	
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
			gameSound.play(Sounds::transition);
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
				(*gameBoard)[x][_y].setFull((*gameBoard)[x][_y - 1].isFull());
				(*gameBoard)[x][_y].setColor((*gameBoard)[x][_y - 1].getColor());
			}
		}
	}	
	linesNumber.clear();
	gameText.updateText();
}

void GameApp::drawBoard()
{
	for (unsigned char i = 0; i < (*gameBoard).size(); i++)
	{
		for (unsigned char j = 2; j < (*gameBoard)[i].size(); j++)
		{
			if ((*gameBoard)[i][j].isFull())
			{				
				(*window).draw((*gameBoard)[i][j]);
			}
		}
	}
}

void GameApp::drawTetromino()
{
	if (gameOverbool)
		return;

	tetromino->display(*window);
	ghostTetromino->display(*window);
	nextTetromino->display(*window);
}

bool GameApp::gameOver()
{
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		if ((*gameBoard)[i][1].isFull())
		{
			gameSound.play(Sounds::gameOver);
			gameSound.stopBackgroundMusic();
			for (unsigned char i = 0; i < (*gameBoard).size(); i++)
			{
				for (unsigned char j = 2; j < (*gameBoard)[i].size(); j++)
				{
					if ((*gameBoard)[i][j].isFull())
					{
						(*gameBoard)[i][j].setColor(sf::Color(70, 70, 70));
					}
				}
			}
			return true;
		}
	}

	return false;
}

void GameApp::endGame()
{
	window->clear(sf::Color::Black);
	background.displayBackground(window);
	window->draw(gameText);
	drawBoard();
	background.displayGameOver(window);
	closingWindowEvent(window);
}

bool GameApp::updateGame()
{
	if (gameOverbool)
	{
		endGame();
		return true;
	}

	switch (pauseManagement())
	{
	case PauseOutput::resume:
		wait(3.5f);
		break;
	case PauseOutput::exit:
		gameSound.stopBackgroundMusic();
		return false;
	}

	closingWindowEvent(window);

	tetromnoMovement();
	ghostTetromino->updateGhost(*tetromino);
	if (fallingTetromino())
		fullLines();

	return true;
}

void GameApp::drawGame()
{
	if (gameOverbool)
	{
		return;
	}
	//window->clear(sf::Color::Black);
	background.displayBackground(window);
	drawBoard();
	drawTetromino();
	window->draw(gameText);
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
	FPS fps;
	gameSound.playBackgroundMusic();

	while (window->isOpen())
	{
		if(!updateGame())
			return this->score;

		drawGame();		
		manageTimers();	

		window->display();
		fps.update();
		std::cout << fps.getFPS() << std::endl;
	}
	return this->score;
}
