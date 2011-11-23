#include "Ghost.h"

Ghost::Ghost( GLfloat xPos,GLfloat yPos,GLfloat zPos): Sprite()
{
    this->x=xPos;
    this->y=yPos;
    this->z=zPos;
    this->loadTexture();
}

Ghost::~Ghost()
{
    //dtor
}


void Ghost::draw()
{
    glPushMatrix();
    glEnable(GL_BLEND);     // Turn Blending On
    glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off

    GLfloat ambient[] = { 0.8, 0.8, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat shininess[] = { 50.0 };

    glColor4f(1.0f,1.0f,1.0f,1.0f);         // Full Brightness, 50% Alpha ( NEW )
//glBlendFunc(GL_SRC_ALPHA,GL_ONE);       // Blending Function For Translucency Based On Source Alpha
    // setup texture mapping
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //glBlendFunc(GL_ONE,GL_ZERO); //- everything works as usual, despite blending turned on
    //glBlendFunc(GL_ZERO,GL_ONE); //- nothing is being drawn (Z-buffer may be still affected)
    // glBlendFunc(GL_ONE,GL_ONE);// - colors are added (values >1 are clipped to 1)
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); //- transparency: alpha=0 - invisible, alpha=1 - no transparency

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glColor4f(1.0f,1.0f,1.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    move();
    glRotatef(-90.0,1.0f,0.0f,0.0f); //Stand up the ghosts


    GLUquadricObj *quadratic;
    quadratic=gluNewQuadric();
    gluCylinder(quadratic,0.6f,0.3f,1.8f,32,32);

    // glRotatef(180.0f, 1.0f, 0.0f,0.0f);//Flip sphere so we do not see texture seem.
    GLUquadricObj* l_poQuadric = gluNewQuadric();
    gluQuadricDrawStyle(l_poQuadric, GLU_FILL);
    gluQuadricNormals(l_poQuadric, GLU_SMOOTH);
    gluQuadricTexture(l_poQuadric, GL_TRUE);
    gluCylinder(l_poQuadric,0.6f,0.3f,1.8f,32,32);
    gluDeleteQuadric(l_poQuadric);
    glPopMatrix();
    glEnable( GL_TEXTURE_2D );

    glDisable(GL_BLEND);        // Turn Blending Off
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
}



int Ghost::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    this->texture = SOIL_load_OGL_texture
                    (
                        "/home/angela/Documents/Comp371Project/data/pellet.bmp",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y
                    );

    if(this->texture == 0)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;                                        // Return Success

}
