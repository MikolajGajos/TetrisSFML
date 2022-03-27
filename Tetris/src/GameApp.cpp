#include "GameApp.h"

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

GameApp::GameApp(int statringLevel)
	: window({ WINDOW_SIZE_X, WINDOW_SIZE_Y }, "Tetris", sf::Style::Close | sf::Style::Resize)
{
	this->tileTexture.loadFromFile("src/rsrc/Tile.png");
	this->ghostTexture.loadFromFile("src/rsrc/GhostTile.png");
	this->gameBackgroundTexture.loadFromFile("src/rsrc/GameBackground.png");

	for (unsigned char i = 0; i < 23; i++)
	{
		for (unsigned char j = 0; j < 22; j++)
		{
			windowPosition[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			windowPosition[i][j].setFillColor(sf::Color(150, 150, 150));
			windowPosition[i][j].setPosition(i * (CELL), j * (CELL));
		}
	}
	float x = windowPosition[1][1].getPosition().x / CELL;
	float y = windowPosition[1][1].getPosition().y / CELL;
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		for (unsigned char j = 0; j < ROWS; j++)
		{
			matrix[i][j].setFull(false);
			matrix[i][j].setPosition({ CELL * (i + x), CELL * (j + y) });
		}
	}
	if(this->level <= 29)
		this->level = statringLevel;
	else
		this->level = 29;
	setUpSC();
}

void GameApp::tetromnoMovement(Tetromino& tetromino, sf::Event& event)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		rotationAllowed = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && rotationAllowed)
	{
		tetromino.rotate(true);
		rotationAllowed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && rotationAllowed)
	{
		tetromino.rotate(false);
		rotationAllowed = false;
	}

	if (moveTimeCooldown <= 0.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
		{
			tetromino.moveLeft();
			moveTimeCooldownReset();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
		{
			tetromino.moveRight();
			moveTimeCooldownReset();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true && softDropCooldown <= 0.f)
	{
		this->dropTime = 0.f;
		softDropCooldownReset();
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true && hardDropCooldown <= 0.f)
	{
		tetromino.hardDrop();
		hardDropCooldownReset();
		this->dropTime = 0.f;
	}
}

void GameApp::fallingTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino, NextTetromino& nextTetromino)
{
	if (dropTime <= 0.f)
	{
		this->update = false;
		if (tetromino.update() == true) //true == at the end
		{
			tetromino.updateMatrix();
			tetromino.reset(nextTetromino.getShape());
			nextTetromino.reset(getShape(random()));
			ghostTetromino.reset(tetromino);
		}
		dropTimeReset();
	}
}

void GameApp::fullLines()
{
	unsigned char lines = this->clearedLines;
	//loop begins from bottom
	for (unsigned char y = 19; y > 0; y--)
	{
		unsigned char fullCollumn = 0;
		//loop checks every collumn in one row
		for (unsigned char x = 0; x < COLUMNS; x++)
		{
			//if the tile is full it increases the value
			if (matrix[x][y].isFull() == true)
			{
				fullCollumn++;
			}
		}
		//if every tile was full it cleares a row
		if (fullCollumn == COLUMNS)
		{
			//score and level manage
			this->clearedLines++;
			this->linesUntilTransition--;
			if (this->linesUntilTransition == 0)
				transtionLevel();

			//loop moves every line one row down
			for (unsigned char _y = y; _y > 0; _y--)
			{
				for (unsigned char x = 0; x < COLUMNS; x++)
				{
					matrix[x][_y].setFull(matrix[x][_y - 1].isFull());
					matrix[x][_y].setColor(matrix[x][_y - 1].getColor());
				}
			}
			y = ROWS;
		}
	}
	this->score += scoreIncrease(this->clearedLines - lines);
}

void GameApp::drawBackGround(BackgroundManager background)
{
	this->window.draw(background);
}

void GameApp::drawBoard()
{
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		for (unsigned char j = 0; j < ROWS; j++)
		{
			if (!matrix[i][j].isFull())
			{
				matrix[i][j].setTexture(this->gameBackgroundTexture);
				matrix[i][j].setColor(sf::Color(70, 70, 70, 255));
				window.draw(matrix[i][j]);
			}
			else
			{
				matrix[i][j].setTexture(this->tileTexture);
				window.draw(matrix[i][j]);
			}
		}
	}
}

void GameApp::drawTetromino(Tetromino& tetromino, GhostTetromino& ghostTetromino)
{
	sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(tetromino.getColor());
	cellShape.setTexture(&this->ghostTexture);
	//ghost
	for (auto& mino : ghostTetromino.getPosition())
	{
		cellShape.setPosition(CELL * mino.x + matrix[0][0].getPosition().x, mino.y * CELL + matrix[0][0].getPosition().y);
		window.draw(cellShape);
	}

	cellShape.setTexture(&this->tileTexture);
	//tetromino
	for (auto& mino : tetromino.getPosition())
	{
		cellShape.setPosition(CELL * mino.x + matrix[0][0].getPosition().x, mino.y * CELL + matrix[0][0].getPosition().y);
		window.draw(cellShape);
	}
}

void GameApp::drawNextTetromino(NextTetromino& nextTetromino)
{
	//rysowanie nastepnego
	sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(nextTetromino.getColor());
	cellShape.setTexture(&this->tileTexture);
	cellShape.setFillColor(nextTetromino.getColor());
	if (nextTetromino.getShape() != TetrominoShape::I && nextTetromino.getShape() != TetrominoShape::O)
	{
		for (auto& mino : nextTetromino.getPosition())
		{
			cellShape.setPosition((mino.x + 0.5f) * CELL, mino.y * CELL);
			window.draw(cellShape);
		}
	}
	else if (nextTetromino.getShape() == TetrominoShape::I)
	{
		for (auto& mino : nextTetromino.getPosition())
		{
			cellShape.setPosition(mino.x * (CELL), (mino.y + 0.5) * CELL);
			window.draw(cellShape);
		}
	}
	else
	{
		for (auto& mino : nextTetromino.getPosition())
		{
			cellShape.setPosition(mino.x * (CELL), mino.y * CELL);
			window.draw(cellShape);
		}
	}
}

bool GameApp::gameOver()
{
	bool gameOver = false;
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		if (matrix[i][0].isFull() == true)
		{
			return true;
		}		
	}
	return false;
}

int GameApp::run()
{
	sf::Event event;
	sf::Clock clock;
	float deltaTime = 0.f;

	BackgroundManager background;
	TextMenager textManager(&this->windowPosition, &this->clearedLines, &this->level, &this->score);
	Tetromino tetromino(getShape(random()), &matrix);
	GhostTetromino ghostTetromino(tetromino);
	NextTetromino nextTetromino(getShape(random()), &this->windowPosition);

	FPS fps;

	while (window.isOpen())
	{
		window.pollEvent(event);
		if (event.type == sf::Event::Closed)
			this->window.close();
		window.clear(sf::Color::Black);	

		//UPDATE
		tetromnoMovement(tetromino, event);
		ghostTetromino.update(tetromino);
		textManager.updateText();
		fallingTetromino(tetromino, ghostTetromino, nextTetromino);
		fullLines();
		if (gameOver() == true)
			return this->score;

		//DISPLAY
		drawBackGround(background);
		drawBoard();
		drawTetromino(tetromino, ghostTetromino);
		drawNextTetromino(nextTetromino);
		window.draw(textManager);
		window.display();

		//TIME
		dropTime -= deltaTime;
		hardDropCooldown -= deltaTime;
		softDropCooldown -= deltaTime;
		moveTimeCooldown -= deltaTime;
		deltaTime = clock.restart().asSeconds();

		fps.update();
		std::ostringstream ss;
		ss << fps.getFPS();
		window.setTitle(ss.str());
	}
	return 0;
}