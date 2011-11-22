#include "StreetLamp.h"

StreetLamp::StreetLamp(GLint light, GLfloat xPos,GLfloat yPos,GLfloat zPos,GLfloat xLookAt,GLfloat yLookAt,GLfloat zLookAt): Sprite()
{
    this->x=xPos;
    this->y=yPos;
    this->z=zPos;
    this->loadTexture();
    this->light = light;
    this->xLookAt = xLookAt;
    this->yLookAt = yLookAt;
    this->zLookAt = zLookAt;
    this->lightState = 1;
}

StreetLamp::~StreetLamp()
{
    //dtor
}

void StreetLamp::lightSwitch()
{
    if(this->lightState)
    {
        glDisable(this->light);
        this->lightState  = false;
    }
    else
    {
        glEnable(this->light);
        this->lightState  = true;
    }
}
void StreetLamp::lightSwitchTo(GLint state)
{
    if(state==0)
    {
        glDisable(this->light);
        this->lightState  = false;
    }
    else
    {
        glEnable(this->light);
        this->lightState  = true;
    }
}
void StreetLamp::draw()
{
    glPushMatrix();

    this->drawLight();
//this->drawLightVector();
    move();
    //Lightbulb
    this->drawBulb();

    //Lampost
    this->drawPost();

    glPopMatrix();
}

void StreetLamp::drawLight()
{

    GLfloat streetlightColor[] = { 1.0, 0.0, 1.0, 1.0 };

    GLfloat light_position[] = { this->x,this->y,this->z, 1.0 };
    GLfloat spotDir[] = { this->xLookAt,this->yLookAt,this->zLookAt, 1.0 };

    glLightfv(this->light,GL_SPECULAR,streetlightColor);
    glLightfv(this->light,GL_AMBIENT,streetlightColor);
    glLightfv(this->light,GL_DIFFUSE,streetlightColor);
    glLightfv(this->light,GL_POSITION,light_position);

    // Definig spotlight attributes
    glLightf(this->light,GL_SPOT_CUTOFF,25.0);
    glLightf(this->light,GL_SPOT_EXPONENT,2.5);
    glLightfv(this->light,GL_SPOT_DIRECTION,spotDir);

}

void StreetLamp::drawBulb()
{
    glPushMatrix();
    GLfloat ambient[] =  { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] =  { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glBindTexture(GL_TEXTURE_2D, this->lightBulbTexture);

    GLUquadricObj* l_poQuadric = gluNewQuadric();
    gluQuadricDrawStyle(l_poQuadric, GLU_FILL);
    gluQuadricNormals(l_poQuadric, GLU_SMOOTH);
    gluQuadricTexture(l_poQuadric, GL_TRUE);
    glRotatef(180.0f, 1.0f, 0.0f,0.0f);//Flip sphere so we do not see texture seem.
    gluSphere(l_poQuadric,0.4,24,24);
    gluDeleteQuadric(l_poQuadric);
    glPopMatrix();

}

void StreetLamp::drawPost()
{

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 1.0 };

    glTranslated(0.0,this->y/-1.8,0.0);
    glScalef(0.2f, 1.8f,0.2f );

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glBindTexture(GL_TEXTURE_2D, this->texture);

    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();


}

void StreetLamp::drawLightVector()
{

    //This is what the light vector should be.
    //Why it is not working.... I have no idea.
    GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    glMaterialfv(GL_FRONT, GL_SPECULAR, red);
    glVertex3f(this->x,this->y,this->z);
    glVertex3f(this->xLookAt,this->yLookAt,this->zLookAt);
    glEnd();
}

int StreetLamp::loadTexture()
{
    // Load Bitmaps And Convert To Texture
    this->texture = SOIL_load_OGL_texture
                    (
                        "/home/angela/Documents/Comp371Project/data/scratchmetal.bmp",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y
                    );

    this->lightBulbTexture = SOIL_load_OGL_texture
                             (
                                 "/home/angela/Documents/Comp371Project/data/lightbulb.bmp",
                                 SOIL_LOAD_AUTO,
                                 SOIL_CREATE_NEW_ID,
                                 SOIL_FLAG_INVERT_Y
                             );
    if(this->texture == 0 || this->lightBulbTexture == 0)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, this->texture);
//   glBindTexture(GL_TEXTURE_2D, this->lightBulbTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;                                        // Return Success

}
