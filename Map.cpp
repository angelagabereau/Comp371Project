#include "Map.h"

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"
#include<bitset>


using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::fstream;
using std::bitset;


#define ESC 27
//#define M_PI 3.1415926

using namespace std;

Map::Map()
{
    //ctor
    this->score = 0;
    this->xUnits = 28;
    this->zUnits = 28;
    this->worldsEdgeX = 28*2;
    this->worldsEdgeZ = 28*2;
    this->ghostUnits = 6;
    this->initPellets();
    this->initTiles();
    this->initGhosts();

    this->pacman = new Pacman(27.0f,1.1f,27.0f);

    //Draw lights
    /*   this->streetLights[0] = new StreetLamp(GL_LIGHT1,0.0,4.0,0.0,4.0,0.0,4.0); //back left
       this->streetLights[1] = new StreetLamp(GL_LIGHT2,0.0,4.0,56.0,4.0,0.0,48.0);//front left
       this->streetLights[2] = new StreetLamp(GL_LIGHT3,56.0,4.0,0.0,48.0,0.0,4.0);//back right
       this->streetLights[3] = new StreetLamp(GL_LIGHT4,56.0,4.0,56.0,48.0,0.0,48.0);//front right*/
    //Draw lights
    this->streetLights[0] = new StreetLamp(GL_LIGHT1,0.0,4.0,0.0,4.0,0.0,4.0); //back left
    this->streetLights[1] = new StreetLamp(GL_LIGHT2,0.0,4.0,56.0,48.0,0.0,-48.0);//front left
    this->streetLights[2] = new StreetLamp(GL_LIGHT3,56.0,4.0,0.0,-48.0,0.0,48.0);//back right
    this->streetLights[3] = new StreetLamp(GL_LIGHT4,56.0,4.0,56.0,-48.0,0.0,-48.0);//front right

    GLfloat ambientlightColor[] = { 1.0, 1.0, 1.0, 0.5 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlightColor);

    this->pelletsTextureState = 1;
    this->masterStreetLightState = 1;

    this->createMaze();
}

Map::~Map()
{
    //dtor
}

void Map::draw()
{
    camera.ApplyCameraTransform();
    if(this->allTextureState)
        glDisable( GL_TEXTURE_2D );
    else
        glEnable( GL_TEXTURE_2D );
    this->pacman->draw();
    this->drawTiles();
    this->drawStreetLights();

    this->drawGhosts();

    this->drawPellets();
    this->drawWalls();
}

void Map::streetLightSwitch(GLint lightIndex)
{
    this->streetLights[lightIndex]->lightSwitch();
}
void Map::masterStreetLightSwitch()
{
    this->masterStreetLightState = !this->masterStreetLightState;
    for(GLint i=0; i<4; i++)
    {
        this->streetLights[i]-> lightSwitchTo(this->masterStreetLightState);
    }

}
void Map::drawStreetLights()
{
    for(GLint i=0; i<4; i++)
    {
        this->streetLights[i]->draw();
    }
}


void Map::drawGhosts()
{
    for(GLint i=0; i<this->ghostUnits; i++)
    {
        this->ghosts[i]->draw();
    }
}

void Map::drawPellets()
{
    for(GLint i=0; i<this->xUnits; i++)
    {
        for(GLint j=0; j<this->zUnits; j++)
        {
            this->pellets[i][j]->draw();
        }
    }
}

void Map::drawTiles()
{
    for(GLint i=0; i<this->xUnits; i++)
    {
        for(GLint j=0; j<this->zUnits; j++)
        {
            this->tiles[i][j]->draw();
        }
    }

}


void Map::drawAxis()
{
    glPushMatrix();
    // Draw model axes.
    glBegin(GL_LINES);
    // X axis
    glColor3f(1, 0, 0); //Red
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    // Y axis
    glColor3f(0, 1, 0); //Blue
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    // Z axis
    glColor3f(0, 0, 1); //Gree
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();
    glPopMatrix();
}

void Map::initGhosts()
{

    for(GLint i=0; i<this->ghostUnits; i++)
    {
        GLfloat placeme = i*2.0f;
        this->ghosts[i] = new Ghost(placeme+13.0, 0.1f, 45.0f);
    }

}
void Map::initTiles()
{

    GLfloat moveX = 0.0f;

    for(GLint i=0; i<this->xUnits; i++)
    {
        GLfloat moveZ = 0.0f;
        for(GLint j=0; j<this->zUnits; j++)
        {
            this->tiles[i][j]= new Tile(moveX,0.0f,moveZ);
            moveZ = moveZ + 2.0f;
        }
        moveX = moveX + 2.0f;
    }

}

void Map::initPellets()
{
    GLint numPowerPellets = 6;
    GLfloat moveX = 1.0f;

    for(GLint i=0; i<this->xUnits; i++)
    {
        GLfloat moveZ = 1.0f;
        for(GLint j=0; j<this->zUnits; j++)
        {

            this->pellets[i][j]= new Pellet(moveX,0.5f,moveZ, (i+j)%5+1, (i+j)%10+1);
            moveZ = moveZ + 2.0f;
        }
        moveX = moveX + 2.0f;
    }

}

void Map::switchPelletsTexture()
{

    //Get/set the current pellet texture state.

    //this->pelletsTextureState = 0; No Texture
    //this->pelletsTextureState = 1; Texture all pellets
    //this->pelletsTextureState = 2; Texture only power pellets

    this->pelletsTextureState = ++this->pelletsTextureState%3;

    for(GLint i=0; i<this->xUnits; i++)
    {
        for(GLint j=0; j<this->zUnits; j++)
        {
            if(this->pelletsTextureState == 0)
            {
                //Turn off texture for all pellets
                this->pellets[i][j]->setTextureSwitch(0);

            }
            else if(this->pelletsTextureState == 1)
            {
                //Turn texture on for power, off for normal.
                if(this->pellets[i][j]->getType()==1)
                    this->pellets[i][j]->setTextureSwitch(1);
                else
                    this->pellets[i][j]->setTextureSwitch(0);
            }
            else
            {
                //Turn on texture for all pellets
                this->pellets[i][j]->setTextureSwitch(1);
            }
        }
    }
}

void Map::switchAllTexture()
{

    if(this->allTextureState)
    {
        //Turn off all textures
        glDisable( GL_TEXTURE_2D );
        this->allTextureState  = false;
        this->pelletsTextureState = 0;

        for(GLint i=0; i<this->xUnits; i++)
        {
            for(GLint j=0; j<this->zUnits; j++)
            {
                //Turn off texture for all pellets
                this->pellets[i][j]->setTextureSwitch(1);
            }
        }

    }
    else
    {
        glEnable( GL_TEXTURE_2D );
        this->allTextureState  = true;
        this->pelletsTextureState = 2;
        for(GLint i=0; i<this->xUnits; i++)
        {
            for(GLint j=0; j<this->zUnits; j++)
            {
                //Turn off texture for all pellets
                this->pellets[i][j]->setTextureSwitch(0 );
            }
        }
    }
}


char* Map::tr(char x) 	// Transforms Every char into a binary number.
{
// Every '1' corresponds to a wall, considering
// every char is a labyrinth's unit square.
// 1000 = east wall
// 0100 = north
// 0010 = west
// 0001 = south

    char* res;
    switch(x)
    {
    case 'a':
        res = "0001";
        break;
    case 'b':
        res = "0010";
        break;
    case 'c':
        res = "0011";
        break;
    case 'd':
        res = "0100";
        break;
    case 'e':
        res = "0101";
        break;
    case 'f':
        res = "0110";
        break;
    case 'g':
        res = "0111";
        break;
    case 'h':
        res = "1000";
        break;
    case 'i':
        res = "1001";
        break;
    case 'j':
        res = "1010";
        break;
    case 'k':
        res = "1011";
        break;
    case 'l':
        res = "1100";
        break;
    case 'm':
        res = "1101";
        break;
    case 'n':
        res = "1110";
        break;
    case 'o':
        res = "1111";
        break;
    default:
        res = "0000";
        break;
    }
    return res;
}

void Map::readstr(FILE *f,char *string)		// Read char from the file
{
    do
    {
        fgets(string, 28, f);
    }
    while ((string[0] == '/') || (string[0] == '\n'));
    return;
}
char* Map::whereIsHe()
{

    float x = this->pacman->getX();
    float z = this->pacman->getZ();

    return this->walls[(int)x/2][(int)z/2]->getType();
}
void Map::gotPellet(){

    float x = this->pacman->getX();
    float z = this->pacman->getZ();

    bool onTileX = (int)round(x)  % 2;
    bool onTileZ = (int)round(z)  % 2;

    if(onTileX&&onTileZ){
        GLint hasBeenEaten = this->pellets[(int)x/2][(int)z/2]->getHasBeenEaten();
        if(hasBeenEaten==0){
            GLint nutritionalValue = this->pellets[(int)x/2][(int)z/2]->eat();
            this->score++;
            cout<<"Yum Yum. I Love pellets.  Score: "<<this->score<<endl;
            cout<<"Eaten: "<<hasBeenEaten<<" nutritional value = "<<nutritionalValue<<endl;
            if(nutritionalValue==1){
                cout<<"Power pellet time!"<<endl;
            }
        }
    }


    return;


}

char* Map::whatDirectionsCanHeMove(float x, float z)
{

    //Start with the assumption that the sprite can move in all directions
    //and then take away directions.

    //Represented with a 4 bit strig representing 4  direction, ENWS
//    char canMove[] = "1111";
    char* canMove = new char[4];
    canMove[0] ='1';
    canMove[1] ='1';
    canMove[2] ='1';
    canMove[3] ='1';

    //  cout<<"---------**BEGIN----------"<<endl;
//  cout<<"---------BEGIN----------"<<endl;
    cout<<"---------BEGIN----------"<<endl;

    int wallIndexX = (int)x/2;
    int wallIndexZ = (int)z/2;

    cout<<"X: "<<wallIndexX<<" Z: "<<wallIndexZ<<endl;

    //ON THE SEAM, BETWEEN 2 TILES
    //check even and odd. x and z.
    bool onTileX = (int)round(x)  % 2;
    bool onTileZ = (int)round(z)  % 2;

    //cout<<"bwteen z "<<z<<" on z: "<<betweenTilesZ<<endl;
    // cout<<"between x "<<x<<" on x: "<<betweenTilesX<<endl;
    if(onTileZ==0)  //Can only move N S
    {
        canMove[0] = '0';
        canMove[2] = '0';
        cout<<canMove<<" is between tiles Z"<<endl;
    }
    else
    {

        //Can he move north.
        if(wallIndexZ<=0) //on northern edge, cannot go further north
        {
            cout<<"north edge"<<endl;
            canMove[1] = '0';
        }
        else
        {
            //Check current tile's N and the northern tile's S
            char* northTileWallCode = this->walls[wallIndexX][wallIndexZ-1]->getType();
            char* currentTileWallCode = this->walls[wallIndexX][wallIndexZ]->getType();
            if(currentTileWallCode[1]=='1' || northTileWallCode[3]=='1')
                canMove[1]= '0';
        }

        //Can he move south.
        if(wallIndexZ>=this->zUnits-1)//is on southern edge, cannot go further south
        {
            cout<<"south edge"<<endl;
            canMove[3]= '0';
        }
        else
        {
            //Check current tile's S and the southern tile's N
            char* southTileWallCode = this->walls[wallIndexX][wallIndexZ+1]->getType();
            char* currentTileWallCode = this->walls[wallIndexX][wallIndexZ]->getType();
            if(currentTileWallCode[3]=='1' || southTileWallCode[1]=='1')
                canMove[3]= '0';

        }



    }

    // even on x plane means you can only move on the x plane , so no N S
    if(onTileX==0)
    {
        canMove[1] = '0';
        canMove[3] = '0';
        cout<<canMove<<" is between tiles X"<<endl;
    }
    else
    {

        //Can he move east.
        if(wallIndexX>=this->xUnits-1) //is on eastern edge, cannot go further east
        {
            cout<<x<<this->xUnits<<"east edge"<<endl;
            canMove[0]= '0';
        }
        else
        {
            //Check current tile's E and the eastern tile's W
            char* eastTileWallCode = this->walls[wallIndexX+1][wallIndexZ]->getType();
            char* currentTileWallCode = this->walls[wallIndexX][wallIndexZ]->getType();
            if(currentTileWallCode[0]=='1' || eastTileWallCode[2]=='1')
                canMove[0]= '0';
        }


        //Can he move west.
        if(wallIndexX<=0) //is on western edge, cannot go further west
        {
            cout<<"west edge"<<endl;
            canMove[2]= '0';
        }
        else
        {
            //Check current tile's W and the western tile's E
            char* westTileWallCode = this->walls[wallIndexX-1][wallIndexZ]->getType();
            char* currentTileWallCode = this->walls[wallIndexX][wallIndexZ]->getType();
            cout<<"west tile: "<<westTileWallCode<<" curretn: "<<currentTileWallCode<<endl;
            if(currentTileWallCode[2]=='1' || westTileWallCode[0]=='1')
                canMove[2]= '0';

        }



    }

    //  char* currentTileWallCode = this->walls[wallIndexX][wallIndexZ]->getType();
    //    cout<<wallIndexX<<"  ||||   "<<this->xUnits<<"x units"<<endl;







    cout<<canMove<<" bounds done"<<endl;

    return canMove;
}

void Map::createMaze()
{
    string s;
    ifstream infile;
    infile.open("/home/angela/Documents/testtexture/data/Maze.txt");
    int i = 0;

    if (infile.is_open())
    {
        while(getline(infile,s) && i<28)
        {
            for (int j = 0; j < 28; j++)
            {
                char* wallCode = tr(s[j]);
                //  cout<<wallCode<<"MM"<<i<<":"<<j<<endl;
                this->walls[i][j] = new Wall(i*2.0f,0.5f,j*2.0f, wallCode);
            }
            i++;
        }
        infile.close();
    }
    else
    {
        printf(  "Error: can't open maze input file " );
    }

}

void Map::drawWalls()
{
    glPushMatrix();
    // glTranslatef(17.5f,0.5f,8.9f);
    for (int i = 0; i < 28; i++)		// Draw Walls For Every Square Unit
    {
        for (int j = 0; j < 28; j++)
        {
            this->walls[i][j]->draw();
            //this->walls[0][0]->draw();
        }
    }
    glPopMatrix();

}


