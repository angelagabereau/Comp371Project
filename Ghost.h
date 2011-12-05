#ifndef GHOST_H
#define GHOST_H

#include "Sprite.h"


class Ghost : public Sprite
{
public:
    Ghost(GLfloat xPos,GLfloat yPos,GLfloat zPos);
    virtual ~Ghost();
    void draw();
    int loadTexture();
    void turnLeft();
    void turnRight();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    GLint takeHit();
    GLint isAlive();
    void moveDirection(int direction);
    void walkForward(char* walls);
protected:
    GLint dead;
    GLfloat rotation;
};

#endif // GHOST_H
