#ifndef GAME_STATE_H
#define GAME_STATE_H

// includes ...
#include "snake.h"
#include "world.h"


#include<stdexcept>
class Game;   //Samo referenca da se ne uvode cirkularne zavisnosti!

class GameState{
public:
    // Sva moguæa stanja igre.
    enum State {
        Welcome,
        Playing,
        Won,
        Lost,
        Exiting,
        Count     // Count æe dati broj stanja.
    };
    GameState(Game * game) : mpGame(game)//,mWorld(sf::Vector2i(800,800)),mSnake(20)
    {
        if(!font.loadFromFile("Comfortaa-Bold.ttf"))
        throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
        text1.setFont(font);
        text2.setFont(font);
        text1.setCharacterSize(30);
        text2.setCharacterSize(14);
    }
    void setScore(int s)
    {score=s;}

    // Metode koje ovise o stanju.
    virtual void update(sf::Time dt) = 0;
    virtual void handlePlayerInput(sf::Keyboard::Key code)= 0;
    virtual void render() = 0;

protected:
    Game * mpGame;
    sf::Font font;
    sf::Text text1;
    sf::Text text2;
    int score;
   // Snake mSnake;
    // World mWorld;

};

#endif // GAME_STATE_H
