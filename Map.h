#ifndef MAP_H
#define MAP_H

#include <GL/glut.h>
#include "Pellet.h"
#include "Pacman.h"
#include "Eight.h"
#include "Tile.h"
#include "Ghost.h"
#include "StreetLamp.h"
#include "Wall.h"
#include "glFrame.h"

class Map
{
public:
    Map();
    virtual ~Map();
    void draw();
    void initPellets();
    void initTiles();
    void initGhosts();
    void drawPellets();
    void drawAxis();
    void drawTiles();
    void drawGhosts();
    void drawStreetLights();
    void switchPelletsTexture();
    void switchAllTexture();
    void streetLightSwitch(GLint lightIndex);
    void masterStreetLightSwitch();
    Pacman *pacman;
protected:
    void drawWall(GLfloat x, GLfloat y, char* val);
    void drawWalls();
    Pellet *pellets[28][28];
    Tile *tiles[28][28];
    Ghost *ghosts[6];
    StreetLamp *streetLights[4];
    Wall *walls[28][28];
    Eight *eight;
    Tile *tile;
    Ghost *ghost;
    GLFrame camera;
    char* mazeBlueprint[28][28];
    GLint xUnits;
    GLint zUnits;
    GLint ghostUnits;
    GLint pelletsTextureState;
    GLint allTextureState;
    GLint masterStreetLightState;
private:
    char* tr(char x);
    void readstr(FILE *f,char *string);
    void createMaze();
};

#endif // MAP_H
