#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
class Renderer
{
public:
	Renderer(std::string Title, int WindowWidth, int WindowHeight, GameLogic& GameLogic);
	void Run();

private:
	sf::RenderWindow m_Window;
	sf::Font m_Font;
	sf::Text m_IngameTitle;
	sf::Text m_GuessedWord;

	std::string m_Title;
	int m_WindowWidth;
	int m_WindowHeight;

private:
	void SetFont();
	void DrawGraphics();
	std::vector<sf::RectangleShape> MakeGallow();
	void SetupGame();
	void SetupText();
	void SetupIngameTitle();
	void SetupGuessedWord();
	GameLogic& m_GameLogic;

};

