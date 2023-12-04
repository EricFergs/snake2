#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.hpp"
#include "StateMan.hpp"


struct Context
{
    std::unique_ptr<GameEngine::AssetMan> m_assets;
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context()
    {
        m_assets = std::make_unique<GameEngine::AssetMan>();
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
public:
    const float fps = 1.f / 60.f;
    const sf::Time TIME_PER_FRAME = sf::seconds(fps);
    std::shared_ptr<Context> GetContext() const;
    
private:
    std::shared_ptr<Context> m_context;
    
};

enum AssetID
{
    MAIN_FONT = 0,
    WALL,
    FOOD,
    YELLOW,
    PINK,
    GRASS,
    SNAKE
};