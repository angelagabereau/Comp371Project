#ifndef TILE_H
#define TILE_H

#include "Sprite.h"
#include "Eight.h"


class Tile : public Sprite
{
public:
    Tile(GLfloat xPos,GLfloat yPos,GLfloat zPos);
    virtual ~Tile();
    void draw();
    void whiteCube();
    int loadTexture();
protected:
    Eight *eight;
private:
};

#endif // TILE_H
