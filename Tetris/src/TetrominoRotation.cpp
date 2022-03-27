#include "Tetromino.h"

void updateMinosPosition(std::array<sf::Vector2i, 4>& minos, const sf::Vector2i& v0, const sf::Vector2i& v1, const sf::Vector2i& v2, const sf::Vector2i& v3)
{
	minos[0] += v0;
	minos[1] += v1;
	minos[2] += v2;
	minos[3] += v3;
}

bool Tetromino::updateMinosWallkick(const sf::Vector2i& v)
{
	minos[0] += v;
	minos[1] += v;
	minos[2] += v;
	minos[3] += v;
	return this->legalRotation();
}

int changeRotation(int clockwise, int rotation)
{
	return(((rotation + clockwise) % 4 + 4) % 4);
}

bool Tetromino::legalRotation()
{
	bool legal = true;
	for (auto& mino : this->minos)
	{
		//jesli nie wychodzi poza tablice sprawdzam czy miejsce jest zajete
		if (mino.x < COLUMNS && mino.x >= 0 && mino.y < ROWS && mino.y >= 0)
		{
			if ((*matrix)[mino.x][mino.y].isFull() == true)
				legal = false;
		}
		else
			legal = false;
	}

	return legal;
}

bool Tetromino::wallKick(unsigned char previousRotation)
{
	//WSZYSTKIE Y ZAMIENIC ZNAKAMI BO NA STRONCE INACZEJ
	//u mnie: x++ -> prawo y++ -> w dul
	//na stronce: x++ -> w prawo y++ w gure


	std::array<sf::Vector2i, 4> prevoiusPosition = this->minos;

	if (this->tShape != TetrominoShape::I)
	{
		switch (this->rotation)
		{
		case 0:
			if (previousRotation == 3)
			{
				//test 2
				if (this->updateMinosWallkick({ -1,0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1,1 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 0,-2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -2 }) == true)
					return true;

				//jesli zaden test nie spelnil wymagan to nie mozna zrobic kicka
				return false;

			}
			else
			{
				//test 2
				if (this->updateMinosWallkick({ 1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, 1 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 0, -2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, -2 }) == true)
					return true;

				return false;
			}
			break;
		case 1:
		{
			//dla jedynki testy sa jednakowe w obydwu przypadkach

			//test 2
			if (this->updateMinosWallkick({ -1, 0 }) == true)
				return true;

			//test 3 
			this->minos = prevoiusPosition;
			if (this->updateMinosWallkick({ -1, -1 }) == true)
				return true;

			//test 4
			this->minos = prevoiusPosition;
			if (this->updateMinosWallkick({ 0, 2 }) == true)
				return true;

			//test 5
			this->minos = prevoiusPosition;
			if (this->updateMinosWallkick({ -1, 2 }) == true)
				return true;

			return false;
			break;
		}		
		case 2:
			if (previousRotation == 1)
			{
				//test 2
				if (this->updateMinosWallkick({ 1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, 1 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 0, -2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, -2 }) == true)
					return true;

				return false;
			}
			else
			{
				//test 2
				if (this->updateMinosWallkick({ -1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -1 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 0, -2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -2 }) == true)
					return true;

				return false;
			}
			break;
		case 3:
		{
			//dla trojki obie takie same
			//test 2
			if (this->updateMinosWallkick({ 1, 0 }) == true)
				return true;

			//test 3 
			this->minos = prevoiusPosition;
			if (this->updateMinosWallkick({ 1, -1 }) == true)
				return true;

			//test 4
			this->minos = prevoiusPosition;
			if (this->updateMinosWallkick({ 0, 2 }) == true)
				return true;

			//test 5
			this->minos = prevoiusPosition;
			if (this->updateMinosWallkick({ 1, 2 }) == true)
				return true;

			return false;
			break;
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
				if (this->updateMinosWallkick({ 1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -2, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, 2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -2, -1 }) == true)
					return true;

				//jesli zaden test nie spelnil wymagan to nie mozna zrobic kicka
				return false;

			}
			else
			{
				//test 2
				if (this->updateMinosWallkick({ 2, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 2, 1 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -2 }) == true)
					return true;

				return false;
			}
			break;
		case 1:
			if (previousRotation == 0)
			{
				//test 2
				if (this->updateMinosWallkick({ -2, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -2, 1 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, -2 }) == true)
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->updateMinosWallkick({ 1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -2, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, 2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -2, -1 }) == true)
					return true;

				return false;
			}
			break;
		case 2:
			if (previousRotation == 1)
			{
				//test 2
				if (this->updateMinosWallkick({ -1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 2, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 2, 1 }) == true)
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->updateMinosWallkick({ -2, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -2, -1 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 1, -2 }) == true)
					return true;

				return false;
			}
			break;
		case 3:
			if (previousRotation == 2)
			{
				//test 2
				if (this->updateMinosWallkick({ 2, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 2, -1 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -2 }) == true)
					return true;

				return false;

			}
			else
			{
				//test 2
				if (this->updateMinosWallkick({ -1, 0 }) == true)
					return true;

				//test 3 
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 2, 0 }) == true)
					return true;

				//test 4
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ -1, -2 }) == true)
					return true;

				//test 5
				this->minos = prevoiusPosition;
				if (this->updateMinosWallkick({ 2, 1 }) == true)
					return true;

				return false;
			}
			break;
		}
	}
	return false;
}

bool Tetromino::rotate(bool clockwise)
{
	if (this->tShape == TetrominoShape::O)
		return false;

	//zapamietanie wczesniejszego polozenia na wypadek jakby rotacja byla niemozliwa
	std::array<sf::Vector2i, 4> prevoiusPosition = this->minos;
	unsigned char previousRotation = this->rotation;
	bool legalRotation = true;

	if (clockwise)
		this->rotation = changeRotation(1, this->rotation);
	else
		this->rotation = changeRotation(-1, this->rotation);

	if (this->tShape == TetrominoShape::I)
	{
		switch (this->rotation)
		{
		case 0:
			if (clockwise)
			{
				updateMinosPosition(this->minos, { -1,-2 }, { 0, -1 }, { 1, 0 }, { 2, 1 });
			}
			else
			{
				updateMinosPosition(this->minos, { -2, 1 }, { -1, 0 }, { 0, -1 }, { 1, -2 });
			}
			break;
		case 1:
			if (clockwise)
			{
				updateMinosPosition(this->minos, { 2, -1 }, { 1, 0 }, { 0, 1 }, { -1, 2 });
			}
			else
			{
				updateMinosPosition(this->minos, { -1, -2 }, { 0, -1 }, { 1, 0 }, { 2, 1 });
			}
			break;
		case 2:
			if (clockwise)
			{
				updateMinosPosition(this->minos, { 1, 2 }, { 0, 1 }, { -1, 0 }, { -2, -1 });
			}
			else
			{
				updateMinosPosition(this->minos, { 2, -1 }, { 1, 0 }, { 0, 1 }, { -1, 2 });
			}
			break;
		case 3:
			if (clockwise)
			{
				updateMinosPosition(this->minos, { -2, 1 }, { -1, 0 }, { 0, -1 }, { 1, -2 });
			}
			else
			{
				updateMinosPosition(this->minos, { 1, 2 }, { 0, 1 }, { -1, 0 }, { -2, -1 });
			}
			break;			
		}
		for (unsigned char i = 0; i < minos.size(); i++)
		{
			if (minos[i].x >= COLUMNS || minos[i].x < 0)
				legalRotation = false;
			if (minos[i].y >= ROWS || minos[i].y < 0)
				legalRotation = false;
		}
	}
	else
	{
		//wyznaczenie pozycji sorodka
		sf::Vector2i position = this->minos[0];

		//odjecie pozycji srodka od kazdego klocka 
		for (unsigned char i = 0; i < minos.size(); i++)
		{
			minos[i] -= position;

			//wyznaczenie nowej pozycji klocka (9 mozliwosci na jedna strone)
			switch (minos[i].x)
			{
			case -1:
				switch (minos[i].y)
				{
				case -1:
					if (clockwise)
						minos[i] = { 1,-1 };
					else
						minos[i] = { -1,1 };
					break;
				case 0:
					if (clockwise)
						minos[i] = { 0,-1 };
					else
						minos[i] = { 0,1 };
					break;
				case 1:
					if (clockwise)
						minos[i] = { -1,-1 };
					else
						minos[i] = { 1,1 };
					break;
				}
				break;
			case 0:
				switch (minos[i].y)
				{
				case -1:
					if (clockwise)
						minos[i] = { 1,0 };
					else
						minos[i] = { -1,0 };
					break;
				case 0:
					minos[i] = { 0,0 };
					break;
				case 1:
					if (clockwise)
						minos[i] = { -1,0 };
					else
						minos[i] = { 1,0 };
					break;
				}
				break;
			case 1:
				switch (minos[i].y)
				{
				case -1:
					if (clockwise)
						minos[i] = { 1,1 };
					else
						minos[i] = { -1,-1 };
					break;
				case 0:
					if (clockwise)
						minos[i] = { 0,1 };
					else
						minos[i] = { 0,-1 };
					break;
				case 1:
					if (clockwise)
						minos[i] = { -1,1 };
					else
						minos[i] = { 1,-1 };
					break;
				}
				break;
			}

			//dodanie wczesniej odjetej pozycji
			minos[i] += position;

			if (minos[i].x >= COLUMNS || minos[i].x < 0)
				legalRotation = false;
			if (minos[i].y >= ROWS || minos[i].y < 0)
				legalRotation = false;
		}
	}

	if (!legalRotation)
	{
		if (wallKick(previousRotation))
			return true;
	}
		

	//sprawdzenie czy jest miejce na macierzy planszy 
	for (unsigned char i = 0; i < 4; i++)
	{
		if ((*matrix)[minos[i].x][minos[i].y].isFull())
		{
			legalRotation = false;
		}
	}

	if (!legalRotation)
	{
		if (wallKick(previousRotation))
			return true;
	}

	//jesli nie to nie da sie obrocic
	if (!legalRotation)
		this->minos = prevoiusPosition;

	if (!legalRotation)
		this->rotation = previousRotation;

	return legalRotation;
}
