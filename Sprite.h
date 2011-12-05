#ifndef SPRITE_H
#define SPRITE_H


#include <GL/glut.h>
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
#include "glFrame.h"

class Sprite
{
public:
    Sprite();
    virtual ~Sprite();
    virtual void draw() = 0;
    virtual void move();
    virtual int loadTexture()=0;
	GLFrame camera;  //  GLFrame camera
protected:
    GLfloat ambient[4];
	GLfloat diffuse[4];
	 GLfloat specular[4];
    GLfloat shininess[1];
    float x, y, z;	// Object's position.
    GLuint texture;

private:
    bool cameraOn;		// Selected object receives keystrokes.




};

#endif // SPRITE_H
