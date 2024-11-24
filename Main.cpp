#include <SFML/Graphics.hpp>
#include <iostream>

const int WindowHeight = 1024;
const int WindowWidth = 768;
const sf::String Title = "Hangman";
sf::RenderWindow Window(sf::VideoMode(WindowWidth, WindowHeight), Title);


std::vector<sf::RectangleShape> DrawBase(float WindowWidth, float WindowHeight)
{
    sf::Vector2f BaseSize(400.0f, 5.0f);
    sf::Vector2f BaseOrigin(BaseSize.x / 2, BaseSize.y / 2);

    sf::Vector2f PoleSize(5.0f, 400.0f); 
    sf::Vector2f PoleOrigin(PoleSize.x / 2, PoleSize.y); 

    sf::Vector2f BeamSize(150.0f, 5.0f); 
    sf::Vector2f BeamOrigin(0.0f, BeamSize.y / 2); 

    sf::Vector2f RopeSize(5.0f, 50.0f); 
    sf::Vector2f RopeOrigin(RopeSize.x / 2, 0.0f); 

    std::vector<sf::RectangleShape> RectangleBases(4);

    // Base
    RectangleBases[0].setSize(BaseSize);
    RectangleBases[0].setOrigin(BaseOrigin);
    RectangleBases[0].setPosition(sf::Vector2f(WindowWidth / 2, WindowHeight - 300));
    RectangleBases[0].setFillColor(sf::Color::Black);

    // Pole
    RectangleBases[1].setSize(PoleSize);
    RectangleBases[1].setOrigin(PoleOrigin);
    RectangleBases[1].setPosition(RectangleBases[0].getPosition().x, RectangleBases[0].getPosition().y - BaseSize.y / 2);
    RectangleBases[1].setFillColor(sf::Color::Black);

    // Beam
    RectangleBases[2].setSize(BeamSize);
    RectangleBases[2].setOrigin(BeamOrigin);
    RectangleBases[2].setPosition(RectangleBases[1].getPosition().x, RectangleBases[1].getPosition().y - PoleSize.y);
    RectangleBases[2].setFillColor(sf::Color::Black);

    // Rope
    RectangleBases[3].setSize(RopeSize);
    RectangleBases[3].setOrigin(RopeOrigin);
    RectangleBases[3].setPosition(RectangleBases[2].getPosition().x + BeamSize.x, RectangleBases[2].getPosition().y);
    RectangleBases[3].setFillColor(sf::Color::Black);

    return RectangleBases;
 
}


int main()
{
    Window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Fonts/Roboto-Regular.ttf"))
    {
        std::cerr << "Can not find font";
    }
 
    sf::Text text(Title, font);
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);

  
    text.setPosition(WindowWidth / 2.0f, 50.0f); 


    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                Window.close();
            }
        }

        std::vector<sf::RectangleShape> Rectangles = DrawBase(WindowWidth, WindowHeight);
        Window.clear(sf::Color::White);
        for (const auto& rect : Rectangles) {
            Window.draw(rect);
        }
        Window.draw(text);
        Window.display();
    }

 

    return 0;
}