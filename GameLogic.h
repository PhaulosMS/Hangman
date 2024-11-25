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
	std::vector<char> m_Guesses;

private:
	void SetWord();
	
	void PopulateGuessedWord();
	void SetGuessedWord(char Letter);
	void ConvertWordToUpper();
	char keyCodeToChar(sf::Keyboard::Key key);

public:
	void StartGame();
	void AskForInput(sf::Event Event);
	bool IsWin() const;
	bool IsGameOver() const;
	void ProcessLetter(char Letter);
	


public:
	//Getters
	std::string GetWord() const { return m_Word; } //Debugging purposes
	std::string GetGuessedWord() const { return m_GuessedWord; }
	bool IsCorrectGuess(char letter) { return m_Word.find(letter) != std::string::npos; }
	const std::vector<char>& GetGuessedLetters() const { return m_Guesses; }
	const int GetLives() const { return m_Lives; }
};

