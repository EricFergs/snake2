#include "MainMenu.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : m_context(context), m_isPlayButtonSelected(true),
      m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitText(sf::Text& text, const std::string& content, float yOffset, int characterSize)
{
    text.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    text.setString(content);

    
    text.setPosition((m_context->m_window->getSize().x - text.getGlobalBounds().width) / 2,
                     m_context->m_window->getSize().y / 2 + yOffset);

    text.setCharacterSize(characterSize);
}


void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Splatoon1.ttf");

   
    InitText(m_gameTitle, "Snake", -150.f, 100);

    
    InitText(m_playButton, "Start", -30.f, 80);

    
    InitText(m_exitButton, "Leave", 30.f, 80);
}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        HandleWindowEvents(event);

        if (event.type == sf::Event::KeyPressed)
        {
            HandleKeyPress(event.key.code);
        }
    }
}

void MainMenu::HandleWindowEvents(const sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        m_context->m_states->PopAll();
    }
}

void MainMenu::HandleKeyPress(sf::Keyboard::Key keyCode)
{
    if (keyCode == sf::Keyboard::Up && !m_isPlayButtonSelected)
    {
        m_isPlayButtonSelected = true;
        m_isExitButtonSelected = false;
    }
    else if (keyCode == sf::Keyboard::Down && !m_isExitButtonSelected)
    {
        m_isPlayButtonSelected = false;
        m_isExitButtonSelected = true;
    }
    else if (keyCode == sf::Keyboard::Return)
    {
        m_isPlayButtonPressed = m_isPlayButtonSelected;
        m_isExitButtonPressed = !m_isPlayButtonSelected;
    }
}

void MainMenu::Update(const sf::Time &deltaTime)
{
    if (m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_states->PopAll();
    }
    if (m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color(0, 255, 0));
        m_exitButton.setFillColor(sf::Color(255, 255, 255));
    }
    else
    {
        m_exitButton.setFillColor(sf::Color(0, 255, 0));
        m_playButton.setFillColor(sf::Color(255, 255, 255));
    }

    
}

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color(255, 0, 255));
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_gameTitle); 
    m_context->m_window->display();
}
//draw