#include "playing_state.h"

// Implementacija PlayingState klase
PlayingState::PlayingState(Game* game):GameState(game),mWorld(sf::Vector2i(800,800)),mSnake(20)
{}

void PlayingState::update(sf::Time dt)
{
    if(mSnake.hasLost()){mSnake.reset(); mWorld.respawnApple();}

    if(mSnake.getDirection()!=Direction::None)
    {
    mWorld.update(mSnake);
    if(mSnake.hasLost())
    {
        if(mSnake.getScore()>100) mpGame->changeState(State::Won);
        else mpGame->changeState(State::Lost);
        mpGame->getState()->setScore(mSnake.getScore());
    }

    else
    {
      mSnake.update();
       if(mSnake.hasLost())
        {
        if(mSnake.getScore()>100) mpGame->changeState(State::Won);
        else mpGame->changeState(State::Lost);
        mpGame->getState()->setScore(mSnake.getScore());
        }

    }

    }
}


void PlayingState::render()
{
      mpGame->getWindow().draw(mWorld);
      mpGame->getWindow().draw(mSnake);
}


void PlayingState::handlePlayerInput(sf::Keyboard::Key code)
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
