#include "world.h"
#include <ctime>
#include <random>

// Implementacija klase World dolazi ovdje.
World::World(sf::Vector2i windowSize):mWindowSize(windowSize.x,windowSize.y),mBlockSize(20)
{

    int a=(mWindowSize.x/mBlockSize)*mBlockSize;
    int b=(mWindowSize.y/mBlockSize)*mBlockSize;
    for(int i=0;i<4;i++)
    {
        if(i==0||i==2)
            mBounds[i].setSize(sf::Vector2f(sf::Vector2i(mBlockSize,b-(2*mBlockSize))));
        else
            mBounds[i].setSize(sf::Vector2f(sf::Vector2i(a,mBlockSize)));

        mBounds[i].setFillColor(sf::Color::Yellow);
    }
    mBounds[0].setPosition(0.f,(float)mBlockSize);
    mBounds[2].setPosition((float)(a-mBlockSize),(float)mBlockSize);
    mBounds[3].setPosition(0.f,(float) (b-mBlockSize) );

    mApple.setRadius((float)mBlockSize/2.f);

    mApple.setFillColor(sf::Color::Red);
    mApple.setOrigin((float)mBlockSize,(float)mBlockSize);
   respawnApple();

    while(mApple.getPosition()==sf::Vector2f((float)(5*mBlockSize),(float)(5*mBlockSize))) respawnApple();
}

void World::respawnApple()
{
    std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis1(2,mWindowSize.x/mBlockSize-1),dis2(2,mWindowSize.y/mBlockSize-1);

     mApple.setPosition((float)(dis1(gen)*mBlockSize),(float)(dis2(gen)*mBlockSize));

}

void World::update(Snake & snake)
{
    sf::Vector2f koordglave(0,0);
    switch(snake.getDirection())
   {
     case Direction::Up:
         koordglave.y=-1;
        break;
     case Direction::Down:
         koordglave.y=1;
         break;
     case Direction::Left:
         koordglave.x=-1;
         break;
     case Direction::Right:
         koordglave.x=1;
         break;
    }
         koordglave.x+=snake.getPosition().x;
         koordglave.y+=snake.getPosition().y;
    if(mApple.getPosition()==sf::Vector2f((float)(koordglave.x*mBlockSize),(float)(koordglave.y*mBlockSize)))
  {
      snake.extend();
      snake.increaseScore();
      respawnApple();


  }
  else if(koordglave.x==1|| koordglave.x==mWindowSize.x/mBlockSize||koordglave.y==1||koordglave.y==mWindowSize.y/mBlockSize)
    snake.lose();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}



