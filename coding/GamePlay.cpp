#include "GamePlay.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context),
      m_score(0),
      m_snakeDirection({32.f, 0.f}),  
      m_elapsedTime(sf::Time::Zero)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");
    m_context->m_assets->AddTexture(YELLOW, "assets/textures/yellowapple.png");
    m_context->m_assets->AddTexture(PINK, "assets/textures/pinkapple.png");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for (auto &wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    m_walls[0].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 16});  
    m_walls[1].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 16});  
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);               

    m_walls[2].setTextureRect({0, 0, 16, (int)m_context->m_window->getSize().y});  
    m_walls[3].setTextureRect({0, 0, 16, (int)m_context->m_window->getSize().y});  
    m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);               

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setScale(2.f, 2.f);  
    m_food.setPosition((m_context->m_window->getSize().x / 2) + 128, m_context->m_window->getSize().y / 2);

    m_food2.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food2.setScale(2.f, 2.f);  
    m_food2.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    m_yellowapple.setTexture(m_context->m_assets->GetTexture(YELLOW));
    m_yellowapple.setScale(2.f, 2.f);  
    m_yellowapple.setPosition(m_context->m_window->getSize().x / 2 -128, m_context->m_window->getSize().y / 2);

    m_pinkapple.setTexture(m_context->m_assets->GetTexture(PINK));
    m_pinkapple.setScale(2.f, 2.f);  
    m_pinkapple.setPosition(m_context->m_window->getSize().x / 2 + 128, m_context->m_window->getSize().y / 2 - 256);

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));  
    
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(30);  
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_states->PopAll();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = {0.f, -32.f};  
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 32.f};  
                break;
            case sf::Keyboard::Left:
                newDirection = {-32.f, 0.f};  
                break;
            case sf::Keyboard::Right:
                newDirection = {32.f, 0.f};  
                break;

            default:
                break;
            }

            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(const sf::Time &deltaTime)
{
    m_elapsedTime += deltaTime;

    if (m_elapsedTime.asSeconds() > 0.1)
    {
        for (auto &wall : m_walls)
        {
            if (m_snake.IsOn(wall))
            {
                m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
                break;
            }
        }
        if (m_snake.IsOn(m_pinkapple))
        {
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        }
        if (m_snake.IsOn(m_food))
        {
            m_snake.Grow(m_snakeDirection);

            int x = 0, y = 0;
            x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 32);  // Adjusted for larger blocks
            y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 32);  // Adjusted for larger blocks
            m_food.setPosition(x, y);

            int x2 = 0, y2 = 0;
            x2 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 32);  
            y2 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 32); 
            m_pinkapple.setPosition(x2, y2);

            m_score += 1;
            m_scoreText.setString("Score : " + std::to_string(m_score));
        }
        if (m_snake.IsOn(m_food2))
        {
            m_snake.Grow(m_snakeDirection);

            int x = 0, y = 0;
            x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 32);  // Adjusted for larger blocks
            y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 32);  // Adjusted for larger blocks

            m_food2.setPosition(x, y);

            int x2 = 0, y2 = 0;
            x2 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 32);  
            y2 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 32); 
            m_pinkapple.setPosition(x2, y2);

            m_score += 1;
            m_scoreText.setString("Score : " + std::to_string(m_score));
        }
        if (m_snake.IsOn(m_yellowapple))
        {
            m_snake.Grow(m_snakeDirection);
            m_snake.Grow(m_snakeDirection);
            m_snake.Grow(m_snakeDirection);

            int x = 0, y = 0;
            x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 32);  // Adjusted for larger blocks
            y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 32);  // Adjusted for larger blocks

            m_yellowapple.setPosition(x, y);

            int x2 = 0, y2 = 0;
            x2 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 32);  
            y2 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 32); 
            m_pinkapple.setPosition(x2, y2);

            m_score += 3;
            m_scoreText.setString("Score : " + std::to_string(m_score));
        }
        
        else
        {
            m_snake.Move(m_snakeDirection);
        }

        if (m_snake.IsSelfIntersecting())
        {
            m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        }

        m_elapsedTime = sf::Time::Zero;
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);

    for (auto &wall : m_walls)
    {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_food2);
    m_context->m_window->draw(m_yellowapple);
    m_context->m_window->draw(m_pinkapple);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);

    m_context->m_window->display();
}
