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
protected:
private:
};

#endif // GHOST_H
