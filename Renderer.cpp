#include "Renderer.h"
#include <iostream>


Renderer::Renderer(std::string Title, int WindowWidth, int WindowHeight) : m_Title(Title), m_WindowWidth(WindowWidth), m_WindowHeight(WindowHeight)
{
	m_Window.create(sf::VideoMode(m_WindowWidth, m_WindowHeight), m_Title);
	m_Window.setFramerateLimit(60);
	SetupGame();
}

void Renderer::Run()
{
	while (m_Window.isOpen())
	{
		sf::Event Event;
		while (m_Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				m_Window.close();
			}
			
		}

		DrawGraphics();
	}
	
}

void Renderer::SetupGame()
{
	SetFont();
	SetupText();
}

void Renderer::SetupText()
{
	m_IngameTitle.setString(m_Title);
	m_IngameTitle.setFont(m_Font);
	m_IngameTitle.setCharacterSize(32);
	m_IngameTitle.setFillColor(sf::Color::Black);

	sf::FloatRect textBounds = m_IngameTitle.getLocalBounds();
	m_IngameTitle.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_IngameTitle.setPosition(m_WindowWidth / 2.0f, 50.0f);
}

std::vector<sf::RectangleShape> Renderer::DrawBase()
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
	    RectangleBases[0].setPosition(sf::Vector2f(m_WindowWidth / 2, m_WindowHeight - 300));
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

void Renderer::SetFont()
{
	if (!m_Font.loadFromFile("Fonts/Roboto-Regular.ttf")) std::cerr << "Font file can not be found";
}

void Renderer::DrawGraphics()
{
	m_Window.clear(sf::Color::White);

	m_Window.draw(m_IngameTitle);

	std::vector<sf::RectangleShape> Rects = DrawBase();
	for (const sf::RectangleShape& Rect : Rects) {
		m_Window.draw(Rect);
	}
	m_Window.display();
}
