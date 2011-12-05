#include "Eight.h"

Eight::Eight( GLfloat xPos,GLfloat yPos,GLfloat zPos): Sprite()
{
    x=xPos;
    y=yPos;
    z=zPos;
    this->loadTexture();
}
Eight::~Eight()
{
    //dtor
}

void Eight::cube()
{

    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)
    glNormal3f(0.0f,0.0f,-1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();					// done with the polygon

}/*
void Eight::cube()
{
    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
    glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
    glEnd();					// done with the polygon
}
*/
void Eight::triangle()
{
    glBegin(GL_POLYGON);				// start drawing a polygon
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f( 0.0f, 0.2f, 0.0f);		// Top
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();
}
void Eight::digitalStrut()
{
    glPushMatrix();
    glScalef( 0.1, 0.2, 0.2 );

    glPushMatrix();
    glTranslatef(0.0f,2.5f,0.0f);		// Move up 3
    glScalef( 1.0, 0.5, 1.0 );
    triangle();
    glPopMatrix();

    glPushMatrix();
    glScalef( 1.0, 2.0, 1.0 );
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,-2.5f,0.0f);		// Move up 3
    glRotatef(180.0f, 0.0f, 0.0f,1.0f);
    glScalef( 1.0, 0.5, 1.0 );
    triangle();
    glPopMatrix();

    glPopMatrix();

}

void Eight::draw()
{

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, this->texture);
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat shininess[] = { 00.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    move();
    //VERTICAL STRUTS
    //TOP
    digitalStrut(); //Top Right
    glTranslatef(1.0f,0.0f,0.0f);
    digitalStrut(); //Top Left
    //BOTTOM
    glTranslatef(0.0f,1.0f,0.0f);	//Bottom
    digitalStrut(); //Bottom Right
    glTranslatef(-1.0f,0.0f,0.0f);
    digitalStrut(); //Bottom Left

    //HORIZONTAL STRUTS
    glRotatef(90.0f,0.0f,0.0f,1.0f);  //Draw horizontal struts
    glTranslatef(0.5f,-0.5f,0.0f);	//Top
    digitalStrut();
    glTranslatef(-1.0f,0.0f,0.0f);	//Middle
    digitalStrut();
    glTranslatef(-1.0f,0.0f,0.0f);	//Bottom
    digitalStrut();

    glPopMatrix();
}

int Eight::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    this->texture = SOIL_load_OGL_texture
                    (
                      "/home/angela/Documents/Comp371Project/data/eight.bmp",
                       // "data/eight.bmp",
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
