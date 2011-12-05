#include "Tile.h"

Tile::Tile( GLfloat xPos,GLfloat yPos,GLfloat zPos): Sprite()
{
    x=xPos;
    y=yPos;
    z=zPos;
    eight = new Eight(0.0, 0.0, 0.0);
    this->loadTexture();
}

Tile::~Tile()
{
    //dtor
}



void Tile::draw()
{
    glPushMatrix();
    move();

    glRotatef(90.0f,1.0f,0.0f,0.0f); //Flip tile from x-y axis to the x-z axis.
    glTranslatef(1.0f,1.0f,0.0f);
    this->whiteCube();

    //Get in position to draw '8'
    glScalef( 0.7f, 0.7f, 0.7f );
    glTranslatef(-0.5f,-0.5f,-0.01f );
    eight->draw();

    glPopMatrix();
}

void Tile::whiteCube()
{

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 100.0 };
    // setup texture mapping

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glColor3f(1.0f,1.0f,1.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

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

}
int Tile::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    this->texture = SOIL_load_OGL_texture
                    (
                        "/home/angela/Documents/Comp371Project/data/tilefloor.bmp",
                        //"data/tilefloor.bmp",
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
