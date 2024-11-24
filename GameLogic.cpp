#include "GameLogic.h"
#include <fstream>
#include <iostream>
#include <ctime>>
#include <random>

void GameLogic::StartGame()
{
	SetWord();
}

void GameLogic::SetWord()
{
	std::ifstream File("Words/Words.txt");
	if (!File.is_open()) { std::cerr << "Word file could not open please check it exists -> /Words/Words.txt"; }

	std::string WordToPushBack;
	std::vector<std::string> AvailableWords;

	while (std::getline(File, WordToPushBack))
	{
		AvailableWords.push_back(WordToPushBack);
	}

	std::srand(std::time(0));
	m_Word = AvailableWords[std::rand() % AvailableWords.size()];
	
	File.close();
}

void GameLogic::ProcessLetter(char Letter)
{
}

bool GameLogic::IsGameOver() const
{
	return false;
}

bool GameLogic::IsWin() const
{
	return false;
}


