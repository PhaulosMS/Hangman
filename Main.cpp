#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//TODO
/*
* Refactor to put render into class
* start making letters undernearth
* start adding logic and make gameloop class
* 
*/

#define Title "Hangman"
#define WindowHeight 1024
#define WindowWidth 768


int main() 
{
    GameLogic GameLogic;
    Renderer Game(Title, WindowWidth, WindowHeight, GameLogic);
    

    Game.Run();
}
