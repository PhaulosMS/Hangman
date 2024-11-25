#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>  
#include "GameLogic.h"

struct LetterButton {
    float X, Y, Width, Height;
    char Letter;
    sf::RectangleShape ButtonBackground;
    bool IsCorrect;  
    bool IsClicked;  
};

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
    sf::Text m_Lives;
    std::string m_Title;
    int m_WindowWidth;
    int m_WindowHeight;
    std::vector<LetterButton> m_LetterButtons;

private:
    void SetFont();
    void DrawGraphics();
    std::vector<sf::RectangleShape> MakeGallow();
    void SetupGame();
    void SetupText();
    void SetupIngameTitle();
    void SetupGuessedWord();
    void SetupLives();
    void DrawKeyboard(); 
    void HandleMouseClick(int MouseX, int MouseY); 
    GameLogic& m_GameLogic;
};
