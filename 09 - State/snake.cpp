#include "snake.h"

//  Implementacija klase Snake dolazi ovdje.
Snake::Snake(int blockSize):msize(blockSize),mbodyRect(sf::Vector2f(sf::Vector2i(blockSize,blockSize))),mSnakeBody(3)
{
     mbodyRect.setOrigin(mbodyRect.getSize());

     mSnakeBody[0]=SnakeSegment(7,7);
     mSnakeBody[1]=SnakeSegment(7,6);
     mSnakeBody[2]=SnakeSegment(7,5);

     mdir=Direction::None;
     mlives=3;
     mspeed=0;
     mscore=0;
     mlost=false;
}


Snake::~Snake()
{
  reset();
}

sf::Vector2i Snake::getPosition(){ return sf::Vector2i(mSnakeBody[0].x,mSnakeBody[0].y);}

void Snake::extend()
{

   mSnakeBody.push_back(SnakeSegment(0,0));

}  // Poveæaj zmiju za jedan blok.

void Snake::reset()
{
     mSnakeBody.resize(3);
     mSnakeBody[0]=SnakeSegment(7,7);
     mSnakeBody[1]=SnakeSegment(7,6);
     mSnakeBody[2]=SnakeSegment(7,5);

     mdir=Direction::None;
     mlives=3;
     mspeed=0;
     mscore=0;
     mlost=false;
}   // Vrati zmiju na startnu startnu poziciju.

void Snake::update()
{   if(mdir!=Direction::None)
      {
       move();
       checkCollision();
      }
}   // Update metoda.

void Snake::cut(int n)
{
   mSnakeBody.resize(mSnakeBody.size()-n);
} // Odsjeci zadnjih n segmenata.

void Snake::move()
{
    mSnakeBody.push_back(SnakeSegment(0,0));

    for(int i=mSnakeBody.size()-2;i>=1;i--)
        mSnakeBody[i]=mSnakeBody[i-1];

  switch(mdir)
   {
     case Direction::Up:
         mSnakeBody[0]=(SnakeSegment(mSnakeBody[0].x,mSnakeBody[0].y-1));
      break;
     case Direction::Down:
          mSnakeBody[0]=(SnakeSegment(mSnakeBody[0].x,mSnakeBody[0].y+1));
      break;
     case Direction::Left:
         mSnakeBody[0]=(SnakeSegment(mSnakeBody[0].x-1,mSnakeBody[0].y));
      break;
     case Direction::Right:
          mSnakeBody[0]=(SnakeSegment(mSnakeBody[0].x+1,mSnakeBody[0].y));
      break;
   }
   mSnakeBody.pop_back();

}   // Pomakni zmiju za jedan blok u danom smjeru.
    // Provjeri samopresjecanje i napravi odgovarajuæu radnju.
void Snake::checkCollision()
{
   int i;
   for(i=1;i<mSnakeBody.size();i++)
    if(mSnakeBody[0].x==mSnakeBody[i].x && mSnakeBody[0].y==mSnakeBody[i].y)
   {
       mlives--;
       if(!getLives()) lose();

       else
       cut(mSnakeBody.size()-i);
   }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    mbodyRect.setFillColor(sf::Color::Magenta);
    for(int i=0;i<mSnakeBody.size();i++)
    {
        if(i==1) mbodyRect.setFillColor(sf::Color::Green);
        mbodyRect.setPosition((float)(mSnakeBody[i].x*msize),(float)(mSnakeBody[i].y*msize));
        target.draw(mbodyRect);
    }

}
