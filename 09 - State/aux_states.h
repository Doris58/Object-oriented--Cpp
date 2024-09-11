#ifndef AUX_STATES_H
#define AUX_STATES_H

#include "game_state.h"


// Sva pomoćna stanja (osim PlayingState). Njihove implementacije
// su prilično slične pa ih možemo grupirati u jedan file.

class WelcomeState : public GameState{
public:
    WelcomeState(Game* game);///jer ne mogu konstr direktno GameState i jer GameState nema prazan konstr.!
    virtual void handlePlayerInput(sf::Keyboard::Key code);
     virtual void update(sf::Time dt){}///impl jer je pozivamo u run??ili staviti if !=Welcome
    virtual void render();
private:

};

class ExitingState : public GameState{
public:
    ExitingState(Game* game);
    virtual void handlePlayerInput(sf::Keyboard::Key code){};
    virtual void update(sf::Time dt);
    virtual void render();
private:
    int i;

};

class WonState : public GameState{
public:
    WonState(Game* game);
    virtual void handlePlayerInput(sf::Keyboard::Key code);
    virtual void update(sf::Time dt);
    virtual void render();
private:

};

class LostState : public GameState{
public:
    LostState(Game* game);
    virtual void handlePlayerInput(sf::Keyboard::Key code);
    virtual void update(sf::Time dt);
    virtual void render();
private:

};

#endif // AUX_STATES_H
