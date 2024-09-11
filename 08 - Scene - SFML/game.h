#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "world.h"

class Game
{
    public:
        Game();
        void run();

    private:
        // Procesiraj dogaðaje
        void processEvents();
        // konstruiraj novo stanje igre
        void update(sf::Time dt);
        // iscrtaj novo stanje
        void render();

        // implementacijski detalji
        void handleKeyInput(sf::Keyboard::Key code);
        void handleMouseInput(sf::Mouse::Button button,bool isPressed);
        void handleMovement(sf::Event::MouseMoveEvent);

        sf::RenderWindow mWindow;
        sf::Time mTimePerFrame;
        World mWorld;
};

#endif
