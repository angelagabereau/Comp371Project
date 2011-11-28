#ifndef PACMAN_H
#define PACMAN_H
#include "Sprite.h"
#include "Eight.h"
class Pacman : Sprite
{
public:
    Pacman(GLfloat xPos,GLfloat yPos,GLfloat zPos);
    virtual ~Pacman();
    void draw();
    void turnLeft();
    void turnRight();
    void walkForward(char* walls);
    void walkBackward(char* walls);
    int loadTexture();
    void drawHalf(GLfloat r);
    Eight *eight;
    int switchTexture();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    GLfloat getRotation();
protected:
    GLuint textureBank[3];
    GLint currentTextureIndex;
    GLint worldsEdgeX;
    GLint worldsEdgeZ;
    GLint health;
private:
    GLfloat rotation;
};

#endif // PACMAN_H
