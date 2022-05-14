#include "MenuClass.h"
#include <filesystem>
#include <fstream>

void HighscoreManager::highscores::saveSocore(std::pair<int, std::string> score)
{
	std::array < std::pair<int, std::string>, 5> temp = arr;
	for (unsigned char i = 0; i < arr.size(); i++)
	{
		if (score.first > arr[i].first)
		{
			for (unsigned char j = i + 1; j < arr.size(); j++)
			{
				temp[j].first = arr[j - 1].first;
				temp[j].second = arr[j - 1].second;
			}
			temp[i].first = score.first;
			temp[i].second = score.second;
			arr = temp;
			return;
		}
	}
}

int HighscoreManager::highscores::getLowest()
{
	return arr[4].first;
}

HighscoreManager::HighscoreManager()
{
	std::filesystem::path path = std::filesystem::current_path().append("resources/cipeczka.txt");

	std::ifstream file;
	file.open(path.string());
	if (file.is_open())
	{
		std::string line;
		int i = 0;
		while (std::getline(file, line))
		{
			std::stringstream ss;
			ss << line;
			ss >> highScores.arr[i].first;
			ss >> highScores.arr[i].second;
			i++;
		}
	}
	file.close();
}

HighscoreManager::~HighscoreManager()
{
	std::filesystem::path path = std::filesystem::current_path().append("resources/cipeczka.txt");

	std::ofstream file;
	file.open(path.string());
	if (file.is_open())
	{
		for (auto& el : highScores.arr)
		{
			file << el.first << " " << el.second << std::endl;
		}
	}
	file.close();
}

void HighscoreManager::update(int score)
{
	if (highScores.getLowest() < score)
	{
		std::string name = "as";
		highScores.saveSocore(std::make_pair(score, name));
	}
}

