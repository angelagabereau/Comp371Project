#ifndef EIGHT_H
#define EIGHT_H

#include "Sprite.h"

class Eight : public Sprite
{
public:
    Eight(GLfloat xPos,GLfloat yPos,GLfloat zPos);
    virtual ~Eight();
    void draw();
    void digitalStrut();
    void cube();
    void triangle();
    int loadTexture();
protected:
private:
};

#endif // EIGHT_H
