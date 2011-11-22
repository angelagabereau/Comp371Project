#ifndef PACMAN_H
#define PACMAN_H
#include "Sprite.h"
#include "Eight.h"
class Pacman : public Sprite
{
public:
    Pacman(GLfloat xPos,GLfloat yPos,GLfloat zPos);
    virtual ~Pacman();
    void draw();
    int loadTexture();
    void drawHalf(GLfloat r);
    Eight *eight;
    int switchTexture();
protected:
    GLuint textureBank[3];
    GLint currentTextureIndex;
private:


};

#endif // PACMAN_H
