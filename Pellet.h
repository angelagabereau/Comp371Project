#ifndef PELLET_H
#define PELLET_H
#include <GL/glut.h>
#include "Sprite.h"

class Pellet : public Sprite
{

public:
    Pellet(GLfloat xPos,GLfloat yPos,GLfloat zPos, GLint colorFlag, GLint type);
    virtual ~Pellet();
    void draw();
    int loadTexture();
    void setTextureSwitch(GLint state);
    int getType();
    GLint getHasBeenEaten();
    GLint eat();
protected:
    GLint textureSwitch;
    GLint colorFlag;
    GLint type;
    GLfloat size;
    GLint hasBeenEaten;
private:
};

#endif // PELLET_H
