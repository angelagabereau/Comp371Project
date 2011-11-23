#include <cstdlib>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"
#include <GL/glut.h>

using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::fstream;

using namespace std;

#include "glFrame.h"

#include "Pacman.h"
#include "Eight.h"

Pacman::Pacman( GLfloat xPos,GLfloat yPos,GLfloat zPos): Sprite()
{
    this->x=xPos;
    this->y=yPos;
    this->z=zPos;
    this->rotation=0.0;
    this->loadTexture();
    this->eight = new Eight(0.0f,0.3f,-2.0f);
    this->worldsEdgeX = 28*2;
    this->worldsEdgeZ = 28*2;
}

Pacman::~Pacman()
{
    //dtor
}
void Pacman::turnLeft()
{
    this->rotation=this->rotation+90;
    if(this->rotation==360)//scale back factor.
        this->rotation=0;
}
void Pacman::turnRight()
{
    //If the roation is zero then set the rotation to 360 and subtract.
    //This keeps the rotation value [0,360] and is used to calculate direction of movement.
    if(this->rotation==0)
        this->rotation=360;
    this->rotation=this->rotation-90;
}
void Pacman::walkForward(char* walls)
{

    bool onTileX = round(this->x) == this->x && (round(this->x)  % 2 != 0);
    bool onTileZ = round(this->z) == this->z && (round(this->z)  % 2 != 0);

    cout<<"pacman x"<<this->x<<" on x: "<<onTileX<<endl;
    cout<<"pacman z"<<this->z<<" on z: "<<onTileZ<<endl;



    //First check which direction pacman is facing by checking pacman's rotation
    //Then check if pacman is on a tile or on an edge.  x and z are whole numbers on tile edges and a float with .5 on the tile.
    //Then check if there is a wall in front of pacman.  This is determined by the char in walls cooresponding to pacman's direction.

    if(this->rotation == 0  && z<this->worldsEdgeZ) // facing south, make sure there is no wall
    {
        if((onTileZ && walls[3]=='0') || !onTileZ)//If we are on a tile, check there is no wall.
            this->z+=0.5;
    }
    else if(this->rotation == 90 && x>0)  // facing west
    {
        if((onTileX && walls[2]=='0') || !onTileX)//If we are on a tile, check there is no wall.
            this->x-=0.5;
    }
    else if(this->rotation == 180 && z>0)  //facing north
    {
        if((onTileZ && walls[1]=='0') || !onTileZ)//If we are on a tile, check there is no wall.
            this->z-=0.5;
    }
    else if(this->rotation == 270 && x<this->worldsEdgeX)  //facing east
    {
        if((onTileX && walls[0]=='0') || !onTileX)//If we are on a tile, check there is no wall.
            this->x+=0.5;
    }
    else
    {
        cout << "Keep turning, you can only move forward at noon, 3, 6 and 9." << endl;
    }
}

void Pacman::walkBackward(char* walls)
{

    bool onTileX = round(this->x) == this->x && (round(this->x)  % 2 != 0);
    bool onTileZ = round(this->z) == this->z && (round(this->z)  % 2 != 0);

    cout<<"pacman x"<<this->x<<" on x: "<<onTileX<<endl;
    cout<<"pacman z"<<this->z<<" on z: "<<onTileZ<<endl;

    if(this->rotation == 0 && z>0) // facing south  //Check world boundary. Do not move beyond.
    {
        if((onTileZ && walls[1]=='0') || !onTileZ)//If we are on a tile, check there is no wall.
            this->z-=0.5;
    }
    else if(this->rotation == 90 && x<this->worldsEdgeX)  // facing west
    {
        if((onTileX && walls[0]=='0') || !onTileX)//If we are on a tile, check there is no wall.
            this->x+=0.5;
    }
    else if(this->rotation == 180 && z<this->worldsEdgeZ)  //facing north
    {
        if((onTileZ && walls[3]=='0') || !onTileZ)//If we are on a tile, check there is no wall.
            this->z+=0.5;
    }
    else if(this->rotation == 270 && x>0)  //facing east
    {
        if((onTileX && walls[2]=='0') || !onTileX)//If we are on a tile, check there is no wall.
            this->x-=0.5;

    }
    else
    {
        cout << "Keep turning, you can only move forward at noon, 3, 6 and 9." << endl;
    }

}


int Pacman::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    this->textureBank[0] = SOIL_load_OGL_texture
                           (
                               "/home/angela/Documents/Comp371Project/data/pacman1.bmp",
                               SOIL_LOAD_AUTO,
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_INVERT_Y
                           );

    this->textureBank[1] = SOIL_load_OGL_texture
                           (
                               "/home/angela/Documents/Comp371Project/data/pacman2.bmp",
                               SOIL_LOAD_AUTO,
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_INVERT_Y
                           );

    this->textureBank[2] = SOIL_load_OGL_texture
                           (
                               "/home/angela/Documents/Comp371Project/data/pacman3.bmp",
                               SOIL_LOAD_AUTO,
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_INVERT_Y
                           );

    if(this->textureBank[0] == 0 || this->textureBank[1] == 0 || this->textureBank[3]== 0 )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }

    //Set current texture
    this->currentTextureIndex = 2;

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, this->textureBank[this->currentTextureIndex]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;                                        // Return Success

}

int Pacman::switchTexture()
{
    this->currentTextureIndex = ++this->currentTextureIndex%3;

    cout << "Changed Pacman's Texture" << this->currentTextureIndex << endl;
    return true;
}

void Pacman::drawHalf(GLfloat r)
{
    GLfloat off[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat yellow[] = { 1.0f, 1.0, 0.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat polished[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glMaterialfv(GL_FRONT, GL_AMBIENT, off);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);

    GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
    glClipPlane (GL_CLIP_PLANE0, eqn);
    glEnable (GL_CLIP_PLANE0);
    glRotatef(180.0f, 1.0f, 0.0f,0.0f);//Flip sphere so we do not see texture seem.
    glBindTexture(GL_TEXTURE_2D, this->textureBank[this->currentTextureIndex]);
    GLUquadricObj* p_poQuadric = gluNewQuadric();
    gluQuadricDrawStyle(p_poQuadric, GLU_FILL);
    gluQuadricNormals(p_poQuadric, GLU_SMOOTH);
    gluQuadricTexture(p_poQuadric, GL_TRUE);
    gluSphere(p_poQuadric,r,24,24);
    gluDeleteQuadric(p_poQuadric);
    glDisable (GL_CLIP_PLANE0);
}

void Pacman::draw()
{
    GLfloat r = 0.8f;
    const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    const GLfloat polished[] = { 100.0 };

    glPushMatrix();

    move();
    glRotatef(this->rotation, 0.0f, 1.0f, 0.0f);
    //cout << this->rotation << endl;
    // glColor3f(1.0f,1.0f,1.0f);

    glPushMatrix(); //Top
    drawHalf(r);
    glPopMatrix();

    glPushMatrix(); //Bottom
    glRotatef(200.0,1.0f,0.0f,0.0f);
    drawHalf(r); //Bottom
    glPopMatrix();

    glPushMatrix();  //Eye balls.
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);

    glTranslatef(-0.3f,0.6f,0.7f);
    glutSolidSphere(0.15,24,24);
    glTranslatef(0.6f,0.0f,0.0f);
    glutSolidSphere(0.15,24,24);
    glPopMatrix();

    //Eight
    glPushMatrix();
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    glScalef(0.5f,0.5f,0.5f);
    glTranslatef(-0.5f,0.3f,-2.0f);
    eight->draw();
    glPopMatrix();

    glPopMatrix();

}

GLfloat Pacman::getX()
{

    return this->x;
}

GLfloat Pacman::getY()
{

    return this->y;
}

GLfloat Pacman::getZ()
{

    return this->z;
}

