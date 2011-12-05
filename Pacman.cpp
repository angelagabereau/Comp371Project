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
    this->health = 100;
    this->dead = 0;
    this->pelletPower = 0;
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
void Pacman::walkForward(char* canMove)
{
    if(this->rotation == 0 && canMove[3]=='1') // facing south, make sure there is no wall
    {
        this->z++;
        this->camera.SetForwardVector(0.0,0.0,1.0);
    }
    else if(this->rotation == 90 && canMove[0]=='1')  // facing east
    {
        this->x++;
        this->camera.SetForwardVector(1.0,0.0,0.0);
    }
    else if(this->rotation == 180 && canMove[1]=='1')  //facing north
    {
        this->z--;
        this->camera.SetForwardVector(0.0,0.0,-1.0);
    }
    else if(this->rotation == 270 && canMove[2]=='1')  //facing west
    {
        this->x--;
        this->camera.SetForwardVector(-1.0,0.0,0.0);
    }
    else
    {
        //  cout << "Ouch!  Watch it!" << endl;
    }
}

void Pacman::walkBackward(char* canMove)
{
    if(this->rotation == 0 && canMove[1]=='1') // facing south  //Check north.
    {
        this->z--;
    }
    else if(this->rotation == 90 && canMove[2]=='1')  // facing east, check behid-> west
    {
        this->x--;
    }
    else if(this->rotation == 180 && canMove[3]=='1')  //facing north
    {
        this->z++;
    }
    else if(this->rotation == 270 && canMove[0]=='1')  //facing west, check behind ->east
    {
        this->x++;
    }
    else
    {
        // cout << "Ouch! Watch it!" << endl;
    }
}

GLint Pacman::takeHit()
{

    this->health = this->health-20;
    cout<<"Pacman hit! OUCH! Health: "<<this->health<<endl;

    if(this->health<=0)
    {
        cout<<"Pacman killed! GAME OVER!"<<endl;
        this->dead = 1;
    }

    return this->health;
}

GLint Pacman::isAlive()
{
    return !this->dead;
}
void Pacman::takePowerPellet()
{
    this->pelletPower = 1;
    this->pelletPowerTime = 100;
}
GLint Pacman::hasPelletPower()
{
    return this->pelletPower;
}
void Pacman::decreasePelletPowerTime()
{
    this->pelletPowerTime--;
    if(this->pelletPowerTime==0)
    {
        cout<<"Power Pellet Time is up!  Defend yourself."<<endl;
        this->pelletPower=0;
    }
}

int Pacman::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    this->textureBank[0] = SOIL_load_OGL_texture
                           (
                               //  "/home/angela/Documents/Comp371Project/data/pacman1.bmp",
                               "data/pacman1.bmp",
                               SOIL_LOAD_AUTO,
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_INVERT_Y
                           );

    this->textureBank[1] = SOIL_load_OGL_texture
                           (
                               //"/home/angela/Documents/Comp371Project/data/pacman2.bmp",
                               "data/pacman2.bmp",
                               SOIL_LOAD_AUTO,
                               SOIL_CREATE_NEW_ID,
                               SOIL_FLAG_INVERT_Y
                           );

    this->textureBank[2] = SOIL_load_OGL_texture
                           (
                               //"/home/angela/Documents/Comp371Project/data/pacman3.bmp",
                               "data/pacman3.bmp",
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
    if(this->pelletPower==1)//Power pellet mode
        glBindTexture(GL_TEXTURE_2D, this->textureBank[1]);
    else
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

GLfloat Pacman::getRotation()
{

    return this->rotation;
}
