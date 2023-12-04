#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    //void Reset(const sf::Vector2f& position, const sf::Vector2f& direction);

    //void ResetGame() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    sf::Sprite m_food2;
    sf::Sprite m_yellowapple;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;

    sf::Text m_scoreText;
    int m_score;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;
    //void GamePlay::Reset()
    //{
        //m_score = 0;
        //m_snakeDirection = {16.f, 0.f};
       // m_elapsedTime = sf::Time::Zero;

    
        //Init();
   // }

};
