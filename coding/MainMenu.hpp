#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "Game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "State.hpp"


class MainMenu : public Engine::State
{
public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;


    void HandleWindowEvents(const sf::Event& event);
    void HandleKeyPress(sf::Keyboard::Key keyCode);
private:
    std::shared_ptr<Context> m_context;

    sf::Text m_playButton;
    sf::Text m_gameTitle;
    sf::Text m_exitButton;
    
   
    bool m_isPlayButtonSelected;
    bool m_isExitButtonPressed;
    bool m_isExitButtonSelected;
    bool m_isPlayButtonPressed;
    
    
    void InitText(sf::Text& text, const std::string& content, float yOffset, int characterSize);
};
