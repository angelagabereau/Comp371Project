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
    void initGhosts(GLfloat ghostData[][2]);
    void drawPellets();
    void drawAxis();
    void drawTiles();
    void drawGhosts();
    void drawStreetLights();
    void switchPelletsTexture();
    void switchAllTexture();
    void streetLightSwitch(GLint lightIndex);
    void masterStreetLightSwitch();
    void gotPellet();
    char* whereIsHe();
    char* whatDirectionsCanHeMove(float x, float z);
    void pacmanGhostCollisionDetection();
    void newLevel();
    Pacman *pacman;
    GLint autoplay;
    StreetLamp *streetLights[4];
    Ghost *ghosts[6];
    GLFrame camera9;    // Camera that is rolled, pitched and yawed

protected:
    void drawWall(GLfloat x, GLfloat y, char* val);
    void drawWalls();
    void initLevel1();
    void initLevel2();
    Pellet *pellets[28][28];
    Tile *tiles[28][28];
    Wall *walls[28][28];
    Eight *eight;
    Tile *tile;
    Ghost *ghost;
    char* mazeBlueprint[28][28];
    char* mazeBlueprint2[28][28];
    GLint xUnits;
    GLint zUnits;
    GLint ghostUnits;
    GLint pelletsTextureState;
    GLint allTextureState;
    GLint masterStreetLightState;
    GLint worldsEdgeX;
    GLint worldsEdgeZ;
    GLint score;
    GLint level;
private:
    char* tr(char x);
    void readstr(FILE *f,char *string);
    void createMaze();
};

#endif // MAP_H
