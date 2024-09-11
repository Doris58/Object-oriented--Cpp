#include "game.h"


// Implementacija Game klase dolazi ovdje.
Game::Game():mWorld(sf::Vector2i(800,800)),mWindow(sf::VideoMode(800,800),"My window"),mSnake(20)
{
  mTimePerFrame=sf::seconds(1.f/10.f);
}

void Game::run()
{
   sf::Clock clock;
   sf::Time timeSinceLastUpdate=sf::Time::Zero;
   while (mWindow.isOpen())
   {
       processEvents();
        timeSinceLastUpdate+=clock.restart();
        while(timeSinceLastUpdate>mTimePerFrame)
        {
         processEvents();
         update(mTimePerFrame);
         timeSinceLastUpdate-=mTimePerFrame;
        }

   render();
   }
}


// Procesiraj dogaðaje
void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code);
            break;
        }
    }
}

// konstruiraj novo stanje igre
void Game::update(sf::Time dt)
{
    if(mSnake.getDirection()!=Direction::None)
    {
    mWorld.update(mSnake);
    if(mSnake.hasLost())
        {
          mSnake.reset();
          mWorld.respawnApple();

        }
    else
    {
       mSnake.update();
       if(mSnake.hasLost())
        {
          mSnake.reset();
          mWorld.respawnApple();

        }
    }

    }
}

// iscrtaj novo stanje
void Game::render()
{
  mWindow.clear();
  mWindow.draw(mWorld);
  mWindow.draw(mSnake);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code)
{
   if(code == sf::Keyboard::Up && mSnake.getDirection()!=Direction::Down)
        mSnake.setDirection(Direction::Up);
   if(code == sf::Keyboard::Down && mSnake.getDirection()!=Direction::Up)
        mSnake.setDirection(Direction::Down);
   if(code == sf::Keyboard::Left && mSnake.getDirection()!=Direction::Right)
        mSnake.setDirection(Direction::Left );
   if(code == sf::Keyboard::Right && mSnake.getDirection()!=Direction::Left)
        mSnake.setDirection(Direction::Right);
}



