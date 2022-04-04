#include "Tetromino.h"

void updateTilesPosition(std::array<sf::Vector2i, 4>& minos, const sf::Vector2i& v0, const sf::Vector2i& v1, const sf::Vector2i& v2, const sf::Vector2i& v3)
{
	minos[0] += v0;
	minos[1] += v1;
	minos[2] += v2;
	minos[3] += v3;
}

bool Tetromino::changeTilesByVector(const sf::Vector2i& v)
{
	tiles[0] += v;
	tiles[1] += v;
	tiles[2] += v;
	tiles[3] += v;
	return this->legalRotation();
}

int changeRotation(bool clockwise, int rotation)
{	
	switch (clockwise)
	{
	case true:
		return(((rotation + 1) % 4 + 4) % 4);
	case false:
		return(((rotation - 1) % 4 + 4) % 4);
	}
	
}

bool Tetromino::legalRotation()
{
	bool legal = true;
	for (auto& mino : this->tiles)
	{
		if (mino.x < COLUMNS && mino.x >= 0 && mino.y < ROWS && mino.y >= 0)
		{
			if ((*matrix)[mino.x][mino.y].isFull())
				return false;
		}
		else
			return false;
	}
	return legal;
}

bool Tetromino::wallKick(unsigned char previousRotation)
{
	std::array<sf::Vector2i, 4> prevoiusPosition = this->tiles;

	if (this->tShape != TetrominoShape::I)
	{
		switch (this->rotation)
		{
		case 0:
			if (previousRotation == 3)
			{
				//test 2
				if (this->changeTilesByVector({ -1,0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1,1 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 0,-2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -2 }))
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->changeTilesByVector({ 1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, 1 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 0, -2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, -2 }))
					return true;

				return false;
			}
		case 1:
		{
			//test 2
			if (this->changeTilesByVector({ -1, 0 }))
				return true;

			//test 3 
			this->tiles = prevoiusPosition;
			if (this->changeTilesByVector({ -1, -1 }))
				return true;

			//test 4
			this->tiles = prevoiusPosition;
			if (this->changeTilesByVector({ 0, 2 }))
				return true;

			//test 5
			this->tiles = prevoiusPosition;
			if (this->changeTilesByVector({ -1, 2 }))
				return true;

			return false;
			break;
		}
		case 2:
			if (previousRotation == 1)
			{
				//test 2
				if (this->changeTilesByVector({ 1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, 1 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 0, -2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, -2 }))
					return true;

				return false;
			}
			else
			{
				//test 2
				if (this->changeTilesByVector({ -1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -1 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 0, -2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -2 }))
					return true;

				return false;
			}
		case 3:
		{
			//test 2
			if (this->changeTilesByVector({ 1, 0 }))
				return true;

			//test 3 
			this->tiles = prevoiusPosition;
			if (this->changeTilesByVector({ 1, -1 }))
				return true;

			//test 4
			this->tiles = prevoiusPosition;
			if (this->changeTilesByVector({ 0, 2 }))
				return true;

			//test 5
			this->tiles = prevoiusPosition;
			if (this->changeTilesByVector({ 1, 2 }))
				return true;

			return false;
		}
		}
	}
	else
	{
		switch (this->rotation)
		{
		case 0:
			if (previousRotation == 3)
			{
				//test 2
				if (this->changeTilesByVector({ 1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -2, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, 2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -2, -1 }))
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->changeTilesByVector({ 2, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 2, 1 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -2 }))
					return true;

				return false;
			}
		case 1:
			if (previousRotation == 0)
			{
				//test 2
				if (this->changeTilesByVector({ -2, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -2, 1 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, -2 }))
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->changeTilesByVector({ 1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -2, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, 2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -2, -1 }))
					return true;

				return false;
			}
		case 2:
			if (previousRotation == 1)
			{
				//test 2
				if (this->changeTilesByVector({ -1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 2, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 2, 1 }))
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->changeTilesByVector({ -2, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -2, -1 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 1, -2 }))
					return true;

				return false;
			}
		case 3:
			if (previousRotation == 2)
			{
				//test 2
				if (this->changeTilesByVector({ 2, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 2, -1 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -2 }))
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->changeTilesByVector({ -1, 0 }))
					return true;

				//test 3 
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 2, 0 }))
					return true;

				//test 4
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ -1, -2 }))
					return true;

				//test 5
				this->tiles = prevoiusPosition;
				if (this->changeTilesByVector({ 2, 1 }))
					return true;

				return false;
			}
		}
	}
	return false;
}

void Tetromino::rotate(bool clockwise)
{
	if (this->tShape == TetrominoShape::O)
		return;

	std::array<sf::Vector2i, 4> prevoiusPosition = this->tiles;
	unsigned char previousRotation = this->rotation;
	bool legalRotation;

	this->rotation = changeRotation(clockwise, this->rotation);
	if (this->getShape() == TetrominoShape::I)
		legalRotation = IrotationAlgorithm(clockwise);
	else
		legalRotation = rotationAlgorithm(clockwise);

	if (!legalRotation)
	{
		if (wallKick(previousRotation))
			return;
		else
		{
			this->tiles = prevoiusPosition;
			this->rotation = previousRotation;
		}		
	}
}

bool Tetromino::rotationAlgorithm(bool clockwise)
{
	sf::Vector2i position = this->tiles[0];
	int temp;

	for (unsigned char i = 0; i < tiles.size(); i++)
	{
		tiles[i] -= position;
		temp = tiles[i].x;

		if (clockwise)
		{			
			tiles[i].x = -tiles[i].y;
			tiles[i].y = temp;
		}
		else
		{
			tiles[i].x = tiles[i].y;
			tiles[i].y = -temp;
		}
		tiles[i] += position;
	}
	return this->legalRotation();
}

bool Tetromino::IrotationAlgorithm(bool clockwise)
{	
	switch (this->rotation)
	{
	case 0:
		if (clockwise)
		{
			updateTilesPosition(this->tiles, { -1,-2 }, { 0, -1 }, { 1, 0 }, { 2, 1 });
		}
		else
		{
			updateTilesPosition(this->tiles, { -2, 1 }, { -1, 0 }, { 0, -1 }, { 1, -2 });
		}
		break;
	case 1:
		if (clockwise)
		{
			updateTilesPosition(this->tiles, { 2, -1 }, { 1, 0 }, { 0, 1 }, { -1, 2 });
		}
		else
		{
			updateTilesPosition(this->tiles, { -1, -2 }, { 0, -1 }, { 1, 0 }, { 2, 1 });
		}
		break;
	case 2:
		if (clockwise)
		{
			updateTilesPosition(this->tiles, { 1, 2 }, { 0, 1 }, { -1, 0 }, { -2, -1 });
		}
		else
		{
			updateTilesPosition(this->tiles, { 2, -1 }, { 1, 0 }, { 0, 1 }, { -1, 2 });
		}
		break;
	case 3:
		if (clockwise)
		{
			updateTilesPosition(this->tiles, { -2, 1 }, { -1, 0 }, { 0, -1 }, { 1, -2 });
		}
		else
		{
			updateTilesPosition(this->tiles, { 1, 2 }, { 0, 1 }, { -1, 0 }, { -2, -1 });
		}
		break;
	}
	return this->legalRotation();
}
