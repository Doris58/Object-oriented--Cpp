
#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "sceneGraph.h"
#include <string>
#include <array>

class World
{
    public:
        explicit World(sf::RenderWindow& window);
        void update(sf::Time dt);
        void draw();
        PlaneNode *Eagle,*Raptor1,*Raptor3;

    private:
        sf::RenderWindow& mWindow;
        sf::Texture mTextureD,mTextureE,mTextureR;
        SceneNode mSceneGraph;
        SceneNode* background;

};

#endif






