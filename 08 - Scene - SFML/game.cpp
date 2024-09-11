#include "game.h"

Game::Game():mWindow(sf::VideoMode(800, 800), "SFML window"),mWorld(mWindow)
{
    mTimePerFrame=sf::seconds(1.f/60.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       // stavi clock na nulu i vrati protekli interval
       timeSinceLastUpdate += clock.restart();
       // updatiraj eventualno više puta ako je iscrtavanje bilo sporo
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();
          update(mTimePerFrame);
       }
       render();
    }
}

void Game::processEvents()
{
    // Process events
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        // Close window : exit
        switch(event.type)
        {
          case sf::Event::Closed:
            mWindow.close();
            break;
          case sf::Event::KeyPressed:
            handleKeyInput(event.key.code);
            break;
          case sf::Event::MouseButtonPressed:
            handleMouseInput(event.mouseButton.button,true);
            break;
          case sf::Event::MouseButtonReleased:
            handleMouseInput(event.mouseButton.button,false);
            break;
          case sf::Event::MouseMoved:
            handleMovement(event.mouseMove);
            break;
          default:
            break;
        }
    }
}

void Game::update(sf::Time dt)
{
    mWorld.update(dt);
}

void Game::render()
{
    // Clear screen
    mWindow.clear();

    // Draw the sprite
    mWorld.draw();

    // Update the window
    mWindow.display();
}

void Game::handleKeyInput(sf::Keyboard::Key code)
{
    if(code==sf::Keyboard::H) mWorld.Eagle->removeComponent("Raptor2");
    if(code==sf::Keyboard::J) mWorld.Eagle->removeComponent("Raptor1");
    if(code==sf::Keyboard::K) mWorld.Eagle->removeComponent("Raptor3");
    if(code==sf::Keyboard::L) mWorld.Eagle->removeComponent("Raptor4");
}

void Game::handleMouseInput(sf::Mouse::Button button,bool isPressed)
{
    if(!isPressed) mWorld.Eagle->setCheck(0);
    else if(button!=sf::Mouse::Left) return;
    else mWorld.Eagle->setCheck(1);
}

void Game::handleMovement(sf::Event::MouseMoveEvent event)
{
    sf::Vector2i where=sf::Mouse::getPosition(mWindow);
    mWorld.Eagle->setDirection(where);
}
