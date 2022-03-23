#include "GameApp.h"

void GameApp::setUpSC()
{
	switch (this->level)
	{
	case 0:
		this->linesUntilTransition = 10;
		break;
	case 1:
		this->linesUntilTransition = 20;
		break;
	case 2:
		this->linesUntilTransition = 30;
		break;
	case 3:
		this->linesUntilTransition = 40;
		break;
	case 4:
		this->linesUntilTransition = 50;
		break;
	case 5:
		this->linesUntilTransition = 60;
		break;
	case 6:
		this->linesUntilTransition = 70;
		break;
	case 7:
		this->linesUntilTransition = 80;
		break;
	case 8:
		this->linesUntilTransition = 90;
		break;
	case 9:
		this->linesUntilTransition = 100;
		break;
	case 10:
		this->linesUntilTransition = 100;
		break;
	case 11:
		this->linesUntilTransition = 100;
		break;
	case 12:
		this->linesUntilTransition = 100;
		break;
	case 13:
		this->linesUntilTransition = 100;
		break;
	case 14:
		this->linesUntilTransition = 100;
		break;
	case 15:
		this->linesUntilTransition = 100;
		break;
	case 16:
		this->linesUntilTransition = 110;
		break;
	case 17:
		this->linesUntilTransition = 120;
		break;
	case 18:
		this->linesUntilTransition = 130;
		break;
	case 19:
		this->linesUntilTransition = 140;
		break;
	case 20:
		this->linesUntilTransition = 150;
		break;
	case 21:
		this->linesUntilTransition = 160;
		break;
	case 22:
		this->linesUntilTransition = 170;
		break;
	case 23:
		this->linesUntilTransition = 180;
		break;
	case 24:
		this->linesUntilTransition = 190;
		break;
	default:
		this->linesUntilTransition = 200;
		break;
	}
}

void GameApp::transtionLevel()
{
	this->linesUntilTransition = 10;
	this->level++;
}

void GameApp::dropTimeReset()
{
	switch (this->level)
	{
	case 0:
		this->dropTime = 0.8f;
		break;
	case 1:
		this->dropTime = 0.75f;
		break;
	case 2:
		this->dropTime = 0.7f;
		break;
	case 3:
		this->dropTime = 0.63f;
		break;
	case 4:
		this->dropTime = 0.54f;
		break;
	case 5:
		this->dropTime = 0.46f;
		break;
	case 6:
		this->dropTime = 0.4f;
		break;
	case 7:
		this->dropTime = 0.33f;
		break;
	case 8:
		this->dropTime = 0.27f;
		break;
	case 9:
		this->dropTime = 0.23f;
		break;
	case 10:
		this->dropTime = 0.2f;
		break;
	case 11:
		this->dropTime = 0.2f;
		break;
	case 12:
		this->dropTime = 0.2f;
		break;
	case 13:
		this->dropTime = 0.2f;
		break;
	case 14:
		this->dropTime = 0.16f;
		break;
	case 15:
		this->dropTime = 0.16f;
		break;
	case 16:
		this->dropTime = 0.11f;
		break;
	case 17:
		this->dropTime = 0.11f;
		break;
	case 18:
		this->dropTime = 0.11f;
		break;
	case 19:
		this->dropTime = 0.11f;
		break;
	case 20:
		this->dropTime = 0.75f;
		break;
	case 21:
		this->dropTime = 0.75f;
		break;
	case 22:
		this->dropTime = 0.75f;
		break;
	case 23:
		this->dropTime = 0.75f;
		break;
	case 24:
		this->dropTime = 0.75f;
		break;
	case 25:
		this->dropTime = 0.75f;
		break;
	case 26:
		this->dropTime = 0.75f;
		break;
	case 27:
		this->dropTime = 0.75f;
		break;
	case 28:
		this->dropTime = 0.75f;
		break;
	default:
		this->dropTime = 0.0375f;
		break;
	}
}

int GameApp::scoreIncrease(unsigned char lines)
{
	//n	  40 * (n + 1)	100 * (n + 1)	300 * (n + 1)	1200 * (n + 1)

	switch (lines)
	{
	case 1:
		return (40 * (this->level + 1));
		break;
	case 2:
		return (100 * (this->level + 1));
		break;
	case 3:
		return (300 * (this->level + 1));
		break;
	case 4:
		return (1200 * (this->level + 1));
		break;
	default:
		return 0;
	}
}