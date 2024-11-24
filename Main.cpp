#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define Title "Hangman"
#define WindowHeight 1024
#define WindowWidth 768

int main() 
{
    GameLogic GameLogic;
    Renderer Game(Title, WindowWidth, WindowHeight, GameLogic);
    

    Game.Run();
}
