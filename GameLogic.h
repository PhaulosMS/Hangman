#pragma once
#include <string>
#include <unordered_set>
class GameLogic
{
private:
	int m_MaxGuesses;
	std::string m_Word;
	std::string m_GuessedWord;
	std::unordered_set<char> m_WrongGuesses;

private:
	
	void SetWord();
	void ProcessLetter(char Letter);
	bool IsGameOver() const;
	bool IsWin() const;

public:
	void StartGame();

public:
	//Getters
	std::string GetWord() const { return m_Word; } //Debugging purposes
	const int GetLives() const { return m_MaxGuesses; }



};

