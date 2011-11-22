#ifndef STREETLAMP_H
#define STREETLAMP_H

#include "Sprite.h"


class StreetLamp : public Sprite
{
public:
    StreetLamp(GLint light, GLfloat xPos,GLfloat yPos,GLfloat zPos,GLfloat xLookAt,GLfloat yLookAt,GLfloat zLookAt);
    virtual ~StreetLamp();
    void draw();
    int loadTexture();
    void drawPost();
    void drawLightVector();
    void drawBulb();
    void drawLight();
    void lightSwitch();
    void lightSwitchTo(GLint state);
protected:
    GLint light;
    GLfloat xLookAt;
    GLfloat yLookAt;
    GLfloat zLookAt;
    GLuint lightBulbTexture;
    GLint lightState;
private:
};

#endif // STREETLAMP_H
