#include <SFML/Graphics/CircleShape.hpp>
#include "MainMenu.hpp"

int main()
{
    // Create the context
    std::shared_ptr<Context> context = std::make_shared<Context>();

    // Create the window
    context->m_window->create(sf::VideoMode(1280, 704), "snake", sf::Style::Close);

    // Add the MainMenu state
    context->m_states->Add(std::make_unique<MainMenu>(context));

    // Create the shape
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Create the clock
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    // Define the constant TIME_PER_FRAME
    const float fps = 1.f / 60.f;
    const sf::Time TIME_PER_FRAME = sf::seconds(fps);

    // Game loop
    while (context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            context->m_states->ProcessStateChange();

            if (!context->m_states->IsEmpty())
            {
                context->m_states->GetCurrent()->ProcessInput();
                context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
                context->m_states->GetCurrent()->Draw();
            }
            else
            {
                context->m_window->close();
            }
        }
    }

    return 0;
}
