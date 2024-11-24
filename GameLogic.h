#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class GameLogic
{

public:
	GameLogic();
private:
	int m_Lives;
	std::string m_Word;
	std::string m_GuessedWord;
	std::vector<char> m_WrongGuesses;

private:
	
	void SetWord();
	void ProcessLetter(char Letter);
	bool IsGameOver() const;
	void PopulateGuessedWord();
	void SetGuessedWord(char Letter);
	void ConvertWordToUpper();
	char keyCodeToChar(sf::Keyboard::Key key);
	

public:
	void StartGame();
	void AskForInput(sf::Event Event);
	bool IsWin() const;

public:
	//Getters
	std::string GetWord() const { return m_Word; } //Debugging purposes
	std::string GetGuessedWord() const { return m_GuessedWord; }
	const int GetLives() const { return m_Lives; }



};

