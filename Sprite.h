#ifndef SPRITE_H
#define SPRITE_H


#include <GL/glut.h>
//#include "glFrame.h"
#include "SOIL/SOIL.h"
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"

class Sprite
{
public:
    Sprite();
    virtual ~Sprite();
    virtual void draw() = 0;
    virtual void move();
    virtual int loadTexture()=0;
protected:
    GLfloat ambient[];
    GLfloat diffuse[];
    GLfloat specular[];
    GLfloat shininess[];
    float x, y, z;	// Object's position.
    GLuint texture;

private:
    bool cameraOn;		// Selected object receives keystrokes.
    //  GLFrame camera;


};

#endif // SPRITE_H
