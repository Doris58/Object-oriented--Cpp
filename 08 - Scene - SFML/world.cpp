#include "world.h"

World::World(sf::RenderWindow& window):Eagle(nullptr),mWindow(window),mSceneGraph(),background(nullptr)
{
    if(!mTextureD.loadFromFile("../../data/Desert.png")) throw std::runtime_error("Can't open file Desert.png!");
    if(!mTextureE.loadFromFile("../../data/Eagle.png")) throw std::runtime_error("Can't open file Eagle.png!");
    if(!mTextureR.loadFromFile("../../data/Raptor.png")) throw std::runtime_error("Can't open file Raptor.png!");
    mTextureD.setRepeated(true);

    std::unique_ptr<BackgrNode> backgroundSprite(new BackgrNode(mTextureD));
    background=backgroundSprite.get();
    sf::Vector2u position=window.getSize();
    backgroundSprite->setPosition(position.x/2.f,position.y/2.f);
    mSceneGraph.addComponent(std::move(backgroundSprite));

    std::unique_ptr<PlaneNode> EagleSprite(new PlaneNode("Eagle",mTextureE));
    Eagle=EagleSprite.get();
    Eagle->setPosition(400.f,300.f);
    Eagle->setVelocity(300.f,300.f);
    mSceneGraph.addComponent(std::move(EagleSprite));

    std::unique_ptr<PlaneNode> RaptorSprite1(new PlaneNode("Raptor1",mTextureR));
    Raptor1=RaptorSprite1.get();
    RaptorSprite1->setPosition(-75.f,+75.f);

    std::unique_ptr<PlaneNode> RaptorSprite2(new PlaneNode("Raptor2",mTextureR));
    RaptorSprite2->setPosition(-75.f,+75.f);
    RaptorSprite1->addComponent(std::move(RaptorSprite2));
    Eagle->addComponent(std::move(RaptorSprite1));

    std::unique_ptr<PlaneNode> RaptorSprite3(new PlaneNode("Raptor3",mTextureR));
    Raptor3=RaptorSprite3.get();
    RaptorSprite3->setPosition(+75.f,+75.f);

    std::unique_ptr<PlaneNode> RaptorSprite4(new PlaneNode("Raptor4",mTextureR));
    RaptorSprite4->setPosition(+75.f,+75.f);
    RaptorSprite3->addComponent(std::move(RaptorSprite4));
    Eagle->addComponent(std::move(RaptorSprite3));

}

void World::update(sf::Time dt)
{
    mSceneGraph.update(dt);
}

void World::draw()
{
    mWindow.draw(mSceneGraph);
}
