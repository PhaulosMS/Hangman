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
            if (Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                m_Window.close();
            }

            if (m_GameLogic.IsGameOver())
            {
                DrawGraphics(); // Fixes if keyboard input was used drawing didn't happen
                sf::Clock Clock;
                while (m_GameLogic.IsGameOver())
                {
                    sf::Time Timer = Clock.getElapsedTime();

                    if (Timer.asSeconds() > 3)
                    {
                        SetupGame();
                        break;
                    }

                    while (m_Window.pollEvent(Event)) {}
                }
                continue;
            }

            m_GameLogic.AskForInput(Event);

            if (Event.type == sf::Event::MouseButtonPressed)
            {
                if (Event.mouseButton.button == sf::Mouse::Left)
                {
                    HandleMouseClick(Event.mouseButton.x, Event.mouseButton.y);
                }
            }
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
    SetupLives();
}

void Renderer::SetupIngameTitle()
{
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
    m_GameLogic.GetLives() == 0 ? m_GuessedWord.setString(m_GameLogic.GetWord()) : m_GuessedWord.setString(m_GameLogic.GetGuessedWord());
    m_GuessedWord.setFont(m_Font);
    m_GuessedWord.setCharacterSize(64);
    m_GuessedWord.setFillColor(sf::Color::Black);

    sf::FloatRect GuessedWordBounds = m_GuessedWord.getLocalBounds();
    m_GuessedWord.setOrigin(GuessedWordBounds.left + GuessedWordBounds.width / 2.0f, GuessedWordBounds.top + GuessedWordBounds.height / 2.0f);
    m_GuessedWord.setPosition(m_WindowWidth / 2.0f, 150.0f);
    m_GuessedWord.setLetterSpacing(2);
}

void Renderer::SetupLives()
{
    m_Lives.setString("Lives: " + std::to_string(m_GameLogic.GetLives()));
    m_Lives.setFont(m_Font);
    m_Lives.setCharacterSize(32);
    m_Lives.setFillColor(sf::Color::Black);

    sf::FloatRect LivesBounds = m_IngameTitle.getLocalBounds();
    m_Lives.setOrigin(LivesBounds.left + LivesBounds.width / 2.0f, LivesBounds.top + LivesBounds.height / 2.0f);
    m_Lives.setPosition(m_WindowWidth - 100.0f, 50.0f);
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

    RectangleBases[0].setSize(BaseSize);
    RectangleBases[0].setOrigin(BaseOrigin);
    RectangleBases[0].setPosition(sf::Vector2f((float)m_WindowWidth / 2, (float)m_WindowHeight - 300));
    RectangleBases[0].setFillColor(sf::Color::Black);

    RectangleBases[1].setSize(PoleSize);
    RectangleBases[1].setOrigin(PoleOrigin);
    RectangleBases[1].setPosition(RectangleBases[0].getPosition().x, RectangleBases[0].getPosition().y - BaseSize.y / 2);
    RectangleBases[1].setFillColor(sf::Color::Black);

    RectangleBases[2].setSize(BeamSize);
    RectangleBases[2].setOrigin(BeamOrigin);
    RectangleBases[2].setPosition(RectangleBases[1].getPosition().x, RectangleBases[1].getPosition().y - PoleSize.y);
    RectangleBases[2].setFillColor(sf::Color::Black);

    RectangleBases[3].setSize(RopeSize);
    RectangleBases[3].setOrigin(RopeOrigin);
    RectangleBases[3].setPosition(RectangleBases[2].getPosition().x + BeamSize.x, RectangleBases[2].getPosition().y);
    RectangleBases[3].setFillColor(sf::Color::Black);

    return RectangleBases;
}

void Renderer::SetFont()
{
    if (!m_Font.loadFromFile("Fonts/Roboto-Regular.ttf"))
        std::cerr << "Font file can not be found";
}

void Renderer::DrawGraphics()
{
    SetupGuessedWord();
    SetupLives();

    m_Window.clear(sf::Color::White);

    m_Window.draw(m_IngameTitle);
    m_Window.draw(m_GuessedWord);
    m_Window.draw(m_Lives);

    std::vector<sf::RectangleShape> Rects = MakeGallow();
    for (const sf::RectangleShape& Rect : Rects) {
        m_Window.draw(Rect);
    }

    DrawKeyboard();

    m_Window.display();
}

void Renderer::DrawKeyboard()
{
    float StartX = 50.0f;  
    float StartY = m_Window.getSize().y - 200.0f; 
    float ButtonSize = 40.0f; 



    for (char Letter = 'A'; Letter <= 'Z'; ++Letter) {
        float X = StartX + (Letter - 'A') % 13 * (ButtonSize + 10);  
        float Y = StartY + (Letter - 'A') / 13 * (ButtonSize + 10);

        LetterButton Button;
        Button.X = X;
        Button.Y = Y;
        Button.Width = ButtonSize;
        Button.Height = ButtonSize;
        Button.Letter = Letter;
        

        bool IsGuessed = false;
        if (!m_GameLogic.GetGuessedLetters().empty()) { IsGuessed = std::find(m_GameLogic.GetGuessedLetters().begin(), m_GameLogic.GetGuessedLetters().end(), Letter) != m_GameLogic.GetGuessedLetters().end(); }

        if (IsGuessed) 
        {
            if (m_GameLogic.IsCorrectGuess(Letter)) 
            {
                Button.ButtonBackground.setFillColor(sf::Color::Green);  
            }
            else 
            {
                Button.ButtonBackground.setFillColor(sf::Color::Red);  
            }
        }
        else 
        {
            Button.ButtonBackground.setFillColor(sf::Color::White);  
        }

        Button.ButtonBackground.setSize(sf::Vector2f(Button.Width, Button.Height));
        Button.ButtonBackground.setPosition(X, Y);

        m_Window.draw(Button.ButtonBackground);

        sf::Text letterText;
        letterText.setFont(m_Font);
        letterText.setString(std::string(1, Letter));
        letterText.setCharacterSize(24);
        letterText.setFillColor(sf::Color::Black);
        letterText.setStyle(sf::Text::Bold);
        letterText.setPosition(X + ButtonSize / 4, Y + ButtonSize / 4); 

        m_Window.draw(letterText);

        m_LetterButtons.push_back(Button);
    }
}

void Renderer::HandleMouseClick(int MouseX, int MouseY)
{
    for (LetterButton& Button : m_LetterButtons)
    {
        if (MouseX >= Button.X && MouseX <= Button.X + Button.Width &&
            MouseY >= Button.Y && MouseY <= Button.Y + Button.Height)
        {
            m_GameLogic.ProcessLetter(Button.Letter);
            std::cout << "Letter clicked: " << Button.Letter << std::endl;
            break;
        }
    }
}
