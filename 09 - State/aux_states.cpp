#include "aux_states.h"
#include<iostream>
#include "game.h"
#include<string>
// Implementacija pomoćnih stanja.
using namespace std;
WelcomeState::WelcomeState(Game* game):GameState(game)
{
    sf::Vector2f vel(mpGame->getWindow().getSize());
   text1.setPosition(vel.x/2.f,vel.y/2.f);
   text2.setPosition((vel.x*2.f)/3.f,(vel.y*10.f)/11.f);
    text1.setString("Snake game by Doris Djivanovic");
    text2.setString("Hit any key to continue");
    text1.setOrigin(text1.getLocalBounds().width/2.f,text1.getLocalBounds().height/2.f);
    text2.setOrigin(text2.getLocalBounds().width/2.f,text2.getLocalBounds().height/2.f);
}

void WelcomeState::handlePlayerInput(sf::Keyboard::Key code)
{
    mpGame->changeState(State::Playing);
}

void WelcomeState::render()
{
     mpGame->getWindow().draw(text1);
     mpGame->getWindow().draw(text2);
}

WonState::WonState(Game* game):GameState(game)
{
    sf::Vector2f vel(mpGame->getWindow().getSize());
   text1.setPosition(vel.x/2.f,vel.y/2.f);
   text2.setPosition((vel.x*2.f)/3.f,(vel.y*10.f)/11.f);
    text2.setString("Hit C to continue, X to exit");
    text2.setOrigin(text2.getLocalBounds().width/2.f,text2.getLocalBounds().height/2.f);


}

void WonState::update(sf::Time dt){}

void WonState::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code==sf::Keyboard::C) mpGame->changeState(State::Playing);
    if(code==sf::Keyboard::X) mpGame->changeState(State::Exiting);
}

void WonState::render()
{
    text1.setString(std::string("You won! The score = ")+std::to_string(score));
    text1.setOrigin(text1.getLocalBounds().width/2.f,text1.getLocalBounds().height/2.f);
    mpGame->getWindow().draw(text1);
    mpGame->getWindow().draw(text2);
}

LostState::LostState(Game* game):GameState(game)
{
    sf::Vector2f vel(mpGame->getWindow().getSize());
   text1.setPosition(vel.x/2.f,vel.y/2.f);
   text2.setPosition((vel.x*2.f)/3.f,(vel.y*10.f)/11.f);
    text2.setString("Hit C to continue, X to exit");
    text2.setOrigin(text2.getLocalBounds().width/2.f,text2.getLocalBounds().height/2.f);

}

void LostState::update(sf::Time dt){}

void LostState::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code==sf::Keyboard::C) mpGame->changeState(State::Playing);
    if(code==sf::Keyboard::X) mpGame->changeState(State::Exiting);
}

void LostState::render()
{
    text1.setString(std::string("You lost! The score = ")+std::to_string(score));
    text1.setOrigin(text1.getLocalBounds().width/2.f,text1.getLocalBounds().height/2.f);
    mpGame->getWindow().draw(text1);
    mpGame->getWindow().draw(text2);
}

ExitingState::ExitingState(Game* game):GameState(game),i(3)
{
    sf::Vector2f vel(mpGame->getWindow().getSize());
   text1.setPosition(vel.x/2.f,vel.y/2.f);
}


void ExitingState::update(sf::Time dt)
{
    //if(i==-1) {cout<<"a"; mpGame->getWindow().close();}

    if(i>=0)
    {text1.setString(std::string("Game over ")+std::to_string(i));
        text1.setOrigin(text1.getLocalBounds().width/2.f,text1.getLocalBounds().height/2.f);
        --i;}
    else mpGame->getWindow().close();


}


void ExitingState::render()
{

    mpGame->getWindow().draw(text1);
}
