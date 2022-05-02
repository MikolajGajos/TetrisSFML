#include "headers/Tetromino.h"

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

void updateTilesPosition(std::array<sf::Vector2i, 4>& minos, const sf::Vector2i& v0, const sf::Vector2i& v1, const sf::Vector2i& v2, const sf::Vector2i& v3)
{
	minos[0] += v0;
	minos[1] += v1;
	minos[2] += v2;
	minos[3] += v3;
}

bool Tetromino::legalKick(const sf::Vector2i& v)
{
	tiles[0] += v;
	tiles[1] += v;
	tiles[2] += v;
	tiles[3] += v;
	return this->legalRotation();
}

bool Tetromino::legalRotation()
{
	bool legal = true;
	for (auto& tile : tiles)
	{
		if (tile.x < COLUMNS && tile.x >= 0 && tile.y < ROWS && tile.y >= 0)
		{
			if ((*gameBoard)[tile.x][tile.y].isFull())
				return false;
		}
		else
			return false;
	}
	return legal;
}

bool Tetromino::wallKick(unsigned char previousRotation)
{
	std::array<sf::Vector2i, 4> prevoiusPosition = tiles;
	switch (this->rotation)
	{
	case 0:
		if (previousRotation == 3)
		{
			//test 2
			if (legalKick({ -1,0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ -1,1 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 0,-2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ -1, -2 }))
				return true;

			return false;

		}
		else
		{
			//test 2
			if (legalKick({ 1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ 1, 1 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 0, -2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ 1, -2 }))
				return true;

			return false;
		}
	case 1:
	{
		//test 2
		if (legalKick({ -1, 0 }))
			return true;

		//test 3 
		tiles = prevoiusPosition;
		if (legalKick({ -1, -1 }))
			return true;

		//test 4
		tiles = prevoiusPosition;
		if (legalKick({ 0, 2 }))
			return true;

		//test 5
		tiles = prevoiusPosition;
		if (legalKick({ -1, 2 }))
			return true;

		return false;
		break;
	}
	case 2:
		if (previousRotation == 1)
		{
			//test 2
			if (legalKick({ 1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ 1, 1 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 0, -2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ 1, -2 }))
				return true;

			return false;
		}
		else
		{
			//test 2
			if (legalKick({ -1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ -1, -1 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 0, -2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ -1, -2 }))
				return true;

			return false;
		}
	case 3:
	{
		//test 2
		if (legalKick({ 1, 0 }))
			return true;

		//test 3 
		tiles = prevoiusPosition;
		if (legalKick({ 1, -1 }))
			return true;

		//test 4
		tiles = prevoiusPosition;
		if (legalKick({ 0, 2 }))
			return true;

		//test 5
		tiles = prevoiusPosition;
		if (legalKick({ 1, 2 }))
			return true;

		return false;
	}
	return false;
	}
}

void Tetromino::rotate(bool clockwise)
{
	std::array<sf::Vector2i, 4> prevoiusPosition = this->tiles;
	unsigned char previousRotation = this->rotation;
	bool legalRotation;

	this->rotation = changeRotation(clockwise, this->rotation);
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
	legalRotation = this->legalRotation();

	if (!legalRotation)
	{
		if (wallKick(previousRotation))
		{
			updateGhost();
			return;
		}
		else
		{
			this->tiles = prevoiusPosition;
			this->rotation = previousRotation;
		}
	}
	updateGhost();
}

bool IShape::wallKick(unsigned char previousRotation)
{
	std::array<sf::Vector2i, 4> prevoiusPosition = tiles;
	switch (this->rotation)
	{
	case 0:
		if (previousRotation == 3)
		{
			//test 2
			if (legalKick({ 1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ -2, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 1, 2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ -2, -1 }))
				return true;

			return false;

		}
		else
		{
			//test 2
			if (legalKick({ 2, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ -1, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 2, 1 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ -1, -2 }))
				return true;

			return false;
		}
	case 1:
		if (previousRotation == 0)
		{
			//test 2
			if (legalKick({ -2, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ 1, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ -2, 1 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ 1, -2 }))
				return true;

			return false;

		}
		else
		{
			//test 2
			if (legalKick({ 1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ -2, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 1, 2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ -2, -1 }))
				return true;

			return false;
		}
	case 2:
		if (previousRotation == 1)
		{
			//test 2
			if (legalKick({ -1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ 2, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ -1, -2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ 2, 1 }))
				return true;

			return false;

		}
		else
		{
			//test 2
			if (legalKick({ -2, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ 1, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ -2, -1 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ 1, -2 }))
				return true;

			return false;
		}
	case 3:
		if (previousRotation == 2)
		{
			//test 2
			if (legalKick({ 2, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ -1, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ 2, -1 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ -1, -2 }))
				return true;

			return false;

		}
		else
		{
			//test 2
			if (legalKick({ -1, 0 }))
				return true;

			//test 3 
			tiles = prevoiusPosition;
			if (legalKick({ 2, 0 }))
				return true;

			//test 4
			tiles = prevoiusPosition;
			if (legalKick({ -1, -2 }))
				return true;

			//test 5
			tiles = prevoiusPosition;
			if (legalKick({ 2, 1 }))
				return true;

			return false;
		}
	}
	return false;
}

void IShape::rotate(bool clockwise)
{
	std::array<sf::Vector2i, 4> prevoiusPosition = this->tiles;
	unsigned char previousRotation = this->rotation;
	bool legalRotation;

	this->rotation = changeRotation(clockwise, this->rotation);
	sf::Vector2i position = this->tiles[0];
	int temp;

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
	legalRotation = this->legalRotation();

	if (!legalRotation)
	{
		if (wallKick(previousRotation))
		{
			updateGhost();
			return;
		}
		else
		{
			this->tiles = prevoiusPosition;
			this->rotation = previousRotation;
		}
	}
	updateGhost();
}