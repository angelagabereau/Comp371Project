#include "Wall.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"


using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::fstream;


#define ESC 27
#define M_PI 3.1415926

using namespace std;

Wall::Wall(GLfloat xPos,GLfloat yPos,GLfloat zPos, char* type)
{
    this->x=xPos;
    this->y=yPos;
    this->z=zPos;

    this->height = 0.5f;
    this->length = 1.0f;
    this->width = 0.2f;

    // cout<<xPos<<":"<<yPos<<":"<<zPos<<":"<<endl;
    //ctor
    this->type = type;
    this->loadTexture();
}

Wall::~Wall()
{
    //dtor
}

char* Wall::getType()
{
    return this->type;
}

void Wall::drawCube()
{


    GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glBegin(GL_QUADS);
    // Front Face
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.00f, -1.00f,  1.00f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.00f, -1.00f,  1.00f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.00f,  1.00f,  1.00f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.00f,  1.00f,  1.00f);
    // Back Face
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.00f, -1.00f, -1.00f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.00f,  1.00f, -1.00f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.00f,  1.00f, -1.00f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.00f, -1.00f, -1.00f);
    // Top Face
    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.00f,  1.00f, -1.00f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.00f,  1.00f,  1.00f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.00f,  1.00f,  1.00f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.00f,  1.00f, -1.00f);
    // Right face
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.00f, -1.00f, -1.00f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.00f,  1.00f, -1.00f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.00f,  1.00f,  1.00f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.00f, -1.00f,  1.00f);
    // Left Face
    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.00f, -1.00f, -1.00f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.00f, -1.00f,  1.00f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.00f,  1.00f,  1.00f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.00f,  1.00f, -1.00f);
    glEnd();

}

void Wall::draw()
{

    glPushMatrix();
    this->move();

    glBindTexture(GL_TEXTURE_2D, this->texture);

    if (this->type[0] == '1')
    {
        //East wall, relative to tile
        //x+2<--->z+2
        glPushMatrix();
        glTranslatef(2.0,0.0,1.0);
        glScalef(this->width,this->height,this->length);    //Scale the cube
        this->drawCube();
        glPopMatrix();
    }
    if (this->type[1] == '1')
    {
        //North wall, relative to tile
        //x<--->y
        glPushMatrix();
        glTranslatef(1.0,0.0,0.0);
        glScalef(this->length,this->height,this->width); //Scale the cube
        this->drawCube();
        glPopMatrix();
    }
    if (this->type[2] == '1')
    {
        //West wall, relative to tile
        //x<--->z
        glPushMatrix();
        glTranslatef(0.0,0.0,1.0);
        glScalef(this->width,this->height,this->length);//Scale the cube
        this->drawCube();
        glPopMatrix();
    }
    if (this->type[3] == '1')
    {
        //South wall, relative to tile
        //x+2.0<--->y+2.0
        glPushMatrix();
        glTranslatef(1.0f, 0.0f, 2.0f);
        glScalef(this->length,this->height,this->width);//Scale the cube
        this->drawCube();
        glPopMatrix();
    }

    glPopMatrix();
}

int Wall::loadTexture()
{
    // Load Bitmaps And Convert To Texture

    texture = SOIL_load_OGL_texture
              (
                  //"/home/angela/Documents/Comp371Project/data/metalwall.bmp",
                  "data/metalwall.bmp",
                  SOIL_LOAD_AUTO,
                  SOIL_CREATE_NEW_ID,
                  SOIL_FLAG_INVERT_Y
              );

    if(texture == 0)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;                                        // Return Success

}
