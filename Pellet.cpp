#include "Pellet.h"

Pellet::Pellet( GLfloat xPos,GLfloat yPos,GLfloat zPos, GLint colorFlag, GLint type): Sprite()
{
    this->x=xPos;
    this->y=yPos;
    this->z=zPos;

    this->colorFlag = colorFlag;
    this->type = type;
    this->textureSwitch = 1;
    if(this->type==1)
        this->size = 0.5;
    else
        this->size = 0.3;
    this->loadTexture();
}
Pellet::~Pellet()
{
    //dtor
}

void Pellet::draw()
{
    glPushMatrix();

    GLfloat yellow[] = { 1.0f, 1.0, 0.0, 1.0 };
    GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
    GLfloat orange[] = { 1.0f, 0.65f, 0.0, 1.0 };
    GLfloat purple[] = { 0.58f, 0.0f, 0.83f, 1.0 };
    GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0f, 1.0, 1.0 };
    GLfloat pink[] = { 1.0f, 0.08f, 0.58f, 1.0 };
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 100.0 };

    switch (this->colorFlag)
    {
    case 1:
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
        break;
    case 2:
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
        break;
    case 3:
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
        break;
    case 4:
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
        break;
    case 5:
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pink);
        break;
    default:
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
        break;
    }
    // setup texture mapping
    //if(this->type==1)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient);
    if(this->textureSwitch==0)
        glDisable( GL_TEXTURE_2D );
    else
        glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glColor3f(1.0f,1.0f,1.0f);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    move();
    glRotatef(180.0f, 1.0f, 0.0f,0.0f);//Flip sphere so we do not see texture seem.
    GLUquadricObj* l_poQuadric = gluNewQuadric();
    gluQuadricDrawStyle(l_poQuadric, GLU_FILL);
    gluQuadricNormals(l_poQuadric, GLU_SMOOTH);
    gluQuadricTexture(l_poQuadric, GL_TRUE);
    gluSphere(l_poQuadric,this->size,24,24);
    gluDeleteQuadric(l_poQuadric);
    glPopMatrix();
    glEnable( GL_TEXTURE_2D );
}

void Pellet::setTextureSwitch(GLint state)
{
    this->textureSwitch = state;
}

int Pellet::getType()
{
    return this->type;
}

int Pellet::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    if(this->type==1)
    {
        texture = SOIL_load_OGL_texture
                  (
                      "/home/angela/Documents/Comp371Project/data/pellet2.bmp",
                      SOIL_LOAD_AUTO,
                      SOIL_CREATE_NEW_ID,
                      SOIL_FLAG_INVERT_Y
                  );
    }
    else
    {
        texture = SOIL_load_OGL_texture
                  (
                      "/home/angela/Documents/testtexture/data/pellet1.bmp",
                      SOIL_LOAD_AUTO,
                      SOIL_CREATE_NEW_ID,
                      SOIL_FLAG_INVERT_Y
                  );
    }

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

