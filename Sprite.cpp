#include "Sprite.h"

Sprite::Sprite()
{
    //ctor


}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::move()
{
    // Move the object to its current position.
    glTranslatef(x, y, z);
}

