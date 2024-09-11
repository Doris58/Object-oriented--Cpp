#define PI 3.14159

#include "sceneGraph.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

SceneNode::SceneNode():mChildren(),mName(),mParent(nullptr)
{}

SceneNode::SceneNode(std::string name):mChildren(),mName(name),mParent(nullptr)
{}

BackgrNode::BackgrNode(const sf::Texture& texture):mTexture(texture)
{
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect({0,0,800,800});
    sf::FloatRect bounds=mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

PlaneNode::PlaneNode(std::string name,const sf::Texture& texture):SceneNode(name),mTexture(texture),mVelocity(0.f,0.f),mDirection({0,0}),check(0)
{
    mSprite.setTexture(mTexture);
    sf::FloatRect bounds=mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void SceneNode::addComponent(Ptr pnode)
{
    pnode->mParent=this;
    mChildren.push_back(std::move(pnode));
}

void SceneNode::removeComponent(std::string const & name)
{
    auto li=mChildren.begin();
    for(;li!=mChildren.end();++li)
        if((*li)->getName()==name) break;

    if(li==mChildren.end())
       {
           auto lj=mChildren.begin();
           for(;lj!=mChildren.end();++lj) (*lj)->removeComponent(name);
           if(lj==mChildren.end()) return;
       }

    (*li)->mParent=nullptr;
    if((*li)->mChildren.empty())
    {
        mChildren.erase(li);
        return;
    }
    for(auto lj=(*li)->mChildren.begin();lj!=(*li)->mChildren.end();)
        {
            if(name=="Raptor3") (*lj)->setPosition(+150.f,+150.f);
            else (*lj)->setPosition(-150.f,+150.f);
            addComponent(std::move(*lj));
            lj=(*li)->mChildren.erase(lj);
        }
    mChildren.erase(li);
}

void SceneNode::updateChildren(sf::Time dt)
{
    for(auto li=mChildren.begin();li!=mChildren.end();++li)
        (*li)->update(dt);
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void PlaneNode::updateCurrent(sf::Time dt)
{
    if(!check) return;
    sf::Vector2f movement(0,0);
    sf::Vector2f position=getPosition();
    sf::Vector2f vektor(mDirection.x-position.x,mDirection.y-position.y);
    float vel=sqrt(vektor.x*vektor.x+vektor.y*vektor.y);
    vektor.x/=vel;
    vektor.y/=vel;
    movement.x=mVelocity.x*vektor.x;
    movement.y=mVelocity.y*vektor.y;
    float angle=acos(vektor.y)*180.f/PI;
    if(mDirection.x-position.x>=0.f) angle=-angle;
    setRotation(angle+180);
    move(movement*dt.asSeconds());
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform*=getTransform();
    drawCurrent(target,states);
    for(auto li=mChildren.begin();li!=mChildren.end();++li)
        (*li)->draw(target,states);
}

void BackgrNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}

void PlaneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}


