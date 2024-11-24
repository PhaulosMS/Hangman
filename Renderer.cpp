#include "Renderer.h"
#include <iostream>


Renderer::Renderer(std::string Title, int WindowWidth, int WindowHeight, GameLogic& GameLogic) 
	: m_Title(Title), m_WindowWidth(WindowWidth), m_WindowHeight(WindowHeight), m_GameLogic(GameLogic)
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
			if (Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || m_GameLogic.IsWin())
			{
				m_Window.close();
			}

			m_GameLogic.AskForInput(Event);
		}

		DrawGraphics();
	}
}

void Renderer::SetupGame()
{
	m_GameLogic.StartGame();
	SetFont();
	SetupText();
	
}

void Renderer::SetupText()
{
	SetupIngameTitle();
	SetupGuessedWord();
}

void Renderer::SetupIngameTitle()
{
	// Ingame Title
	m_IngameTitle.setString(m_Title);
	m_IngameTitle.setFont(m_Font);
	m_IngameTitle.setCharacterSize(32);
	m_IngameTitle.setFillColor(sf::Color::Black);

	sf::FloatRect titleBounds = m_IngameTitle.getLocalBounds();
	m_IngameTitle.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
	m_IngameTitle.setPosition(m_WindowWidth / 2.0f, 50.0f);
}

void Renderer::SetupGuessedWord()
{
	//Word needed to be guessed
	m_GuessedWord.setString(m_GameLogic.GetGuessedWord());
	m_GuessedWord.setFont(m_Font);
	m_GuessedWord.setCharacterSize(64);
	m_GuessedWord.setFillColor(sf::Color::Black);

	sf::FloatRect GuessedWordBounds = m_GuessedWord.getLocalBounds();
	m_GuessedWord.setOrigin(GuessedWordBounds.left + GuessedWordBounds.width / 2.0f, GuessedWordBounds.top + GuessedWordBounds.height / 2.0f);
	m_GuessedWord.setPosition(m_WindowWidth / 2.0f, 150.0f);
	m_GuessedWord.setLetterSpacing(2);
}

std::vector<sf::RectangleShape> Renderer::MakeGallow()
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
	    RectangleBases[0].setPosition(sf::Vector2f((float)m_WindowWidth / 2, (float)m_WindowHeight - 300));
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

	SetupGuessedWord();

	m_Window.clear(sf::Color::White);

	m_Window.draw(m_IngameTitle);
	m_Window.draw(m_GuessedWord);

	std::vector<sf::RectangleShape> Rects = MakeGallow();
	for (const sf::RectangleShape& Rect : Rects) {
		m_Window.draw(Rect);
	}
	
	m_Window.display();
}
