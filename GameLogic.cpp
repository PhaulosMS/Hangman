#include "GameLogic.h"
#include <fstream>
#include <iostream>
#include <ctime>>
#include <random>
#include <SFML/Graphics.hpp>



GameLogic::GameLogic() : m_Lives(6), m_Guesses() {}

void GameLogic::StartGame()
{
	m_Lives = 6;
	m_GuessedWord.clear();
	m_Guesses.clear();
	SetWord();
	PopulateGuessedWord();
	
}


void GameLogic::SetWord() 
{
	std::string WordToPushBack;
	std::vector<std::string> AvailableWords;

	std::ifstream File("Words/Words.txt");
	if (File.is_open() && File.peek() != std::ifstream::traits_type::eof())
	{ 
		while (std::getline(File, WordToPushBack))
		{
			AvailableWords.push_back(WordToPushBack);
		}
		std::srand(static_cast<unsigned int>(std::time(0)));
		File.close();
	}
	else
	{
		AvailableWords = FallBackWords;
		std::cerr << "File could not be found or is empty looking for Words/Words.txt, using default words as backup";
	}

	m_Word = AvailableWords[std::rand() % AvailableWords.size()];
	ConvertWordToUpper();
}

void GameLogic::ProcessLetter(char Letter)
{
	Letter = std::toupper(Letter);
	
	if (std::find(m_Word.begin(), m_Word.end(), Letter) != m_Word.end())
	{
		SetGuessedWord(Letter);
		m_Guesses.push_back(Letter);
		
	}
	else if (std::find(m_Guesses.begin(), m_Guesses.end(), Letter) != m_Guesses.end())
	{
		std::cout << "You have already guessed this letter: " << Letter << std::endl;
	}
	else
	{
		m_Lives--;
		m_Guesses.push_back(Letter);
	}
}

bool GameLogic::IsGameOver() const
{
	if (m_Lives == 0) return true;
	else if (m_GuessedWord == m_Word) return true;
	else return false;

}

bool GameLogic::IsWin() const
{
	return false;

}

void GameLogic::PopulateGuessedWord()
{
	
	for (int i = 0; i < m_Word.size(); i++)
	{
		{
			m_GuessedWord.push_back('_');
		}
	}
}

void GameLogic::SetGuessedWord(char Letter)
{
	std::vector<int> Indecies;
	

	for (int i = 0; i < m_Word.size(); i++)
	{
		if (m_Word[i] == Letter)
		{
			Indecies.push_back(i);
		}
	}

	for (int i = 0; i < Indecies.size(); i++)
	{
		m_GuessedWord[Indecies[i]] = Letter;
	}
}

void GameLogic::ConvertWordToUpper()
{
	std::transform(m_Word.begin(), m_Word.end(), m_Word.begin(), [](unsigned char c) {return std::toupper(c); });
}

char GameLogic::keyCodeToChar(sf::Keyboard::Key key)
{
	if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
		return 'A' + static_cast<char>(key - sf::Keyboard::A);
	}
	return '\0';
}

void GameLogic::AskForInput(sf::Event Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		sf::Keyboard::Key key = Event.key.code;
		if (keyCodeToChar(key) != NULL)
		{
			ProcessLetter(keyCodeToChar(key));
		}
	}
}


