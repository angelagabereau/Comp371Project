#ifndef WALL_H
#define WALL_H

#include "Sprite.h"


class Wall : public Sprite
{
    public:
        Wall(GLfloat xPos,GLfloat yPos,GLfloat zPos, char *type);
        virtual ~Wall();
        void draw();
        int loadTexture();
        void drawCube();
    protected:
        const char* type;
        GLfloat height;
        GLfloat width;
        GLfloat length;
    private:
};

#endif // WALL_H
