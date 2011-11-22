#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"

#include <GL/glut.h>
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
    x=xPos;
    y=yPos;
    z=zPos;
    this->loadTexture();
    this->eight = new Eight(0.0f,0.3f,-2.0f);
}

Pacman::~Pacman()
{
    //dtor
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
    glColor3f(1.0f,1.0f,1.0f);

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


