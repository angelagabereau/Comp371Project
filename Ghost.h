#ifndef GHOST_H
#define GHOST_H

#include "Sprite.h"


class Ghost : Sprite
{
public:
    Ghost(GLfloat xPos,GLfloat yPos,GLfloat zPos);
    virtual ~Ghost();
    void draw();
    int loadTexture();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    void moveDirection(int direction);
};

#endif // GHOST_H
