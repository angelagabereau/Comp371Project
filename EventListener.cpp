#include <GL/glut.h>
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"

#include "glFrame.h"
#include "math3d.cpp"

using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::fstream;

using namespace std;

const int ESC = 27;
const double PI = 3.14159;

/* ascii code for the escape key */
#define ESCAPE 27

#include "EventListener.h"
#include "Map.h"

EventListener::EventListener(GLint width, GLint height)
{
    this->width = width;
    this->height = height;
    this->textureSwitch = true;
    this->light1Switch = true;
    this->light2Switch = true;
    this->light3Switch = true;
    this->light4Switch = true;
    this->fullScreenMode = false;
    this->cameraSwitch = 1;
    this->mouseSwitch = false;
    this->zoomByFovy = false;
    this->yaw = 0.0;
    this->roll = 0.0;
    this->pitch = 0.0;
    this->moveAngle = 90;
    this->zoomMovingCamera = 45.0;
    this->map = new Map();
    this->mouse = new Mouse();

    //Initiallize cameras

    this->map->streetLights[0]->camera.SetOrigin(0.0,6.0,0.0);
    this->map->streetLights[0]->camera.SetForwardVector(1.0,0.0,1.0);

    this->map->streetLights[1]->camera.SetOrigin(0.0,6.0,56.0);
    this->map->streetLights[1]->camera.SetForwardVector(1.0,0.0,-1.0);

    this->map->streetLights[2]->camera.SetOrigin(56.0,6.0,0.0);
    this->map->streetLights[2]->camera.SetForwardVector(-1.0,0.0,1.0);

    this->map->streetLights[3]->camera.SetOrigin(56.0,6.0,56.0);
    this->map->streetLights[3]->camera.SetForwardVector(-1.0,0.0,-1.0);

    this->map->camera9.SetOrigin(28.0,0.0,100.0);
    this->map->camera9.SetForwardVector(0.0,0.0,-1.0);
}

EventListener::~EventListener()
{
    //dtor
}

void EventListener::drawScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    gluPerspective(zoomMovingCamera, 1.5, 1.0, 120.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();				// Reset The View

    switch (cameraSwitch)
    {
    case 1:
        if (mouseSwitch==false)
            gluLookAt(28.0,20.0,100.0,
                      28.0,0.0,28.0,
                      0.0,1.0,0.0);
        else
            this->mouse->mouseLookAt();
        break;
    case 2:
        this->map->streetLights[0]->camera.ApplyCameraTransform();
        break;
    case 3:
        this->map->streetLights[1]->camera.ApplyCameraTransform();
        break;
    case 4:
        this->map->streetLights[2]->camera.ApplyCameraTransform();
        break;
    case 5:
        this->map->streetLights[3]->camera.ApplyCameraTransform();
        break;
    case 6:
        this->map->pacman->camera.ApplyCameraTransform();
        break;
    case 7:
        this->map->ghosts[0]->camera.ApplyCameraTransform();
        break;
    case 8:
        gluLookAt(28+72*cos(moveAngle*PI/180),20.0,28+72*sin(moveAngle*PI/180),
                  28.0,0.0,28.0,
                  0.0,1.0,0.0);
        break;
    case 9:
        this->map->camera9.ApplyCameraTransform();
        break;
    default:
        break;
    }

    //glTranslatef(-28.0f,40.0f,-40.0f);
    //glRotatef(90.0,1.0, 0.0,0.0);

    this->map->drawAxis();
    this->map->draw();

    // since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers();
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void EventListener::initGL()	        // We call this right after our OpenGL window is created.
{
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();				// Reset The Projection Matrix

    // gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    // gluPerspective(45.0, 1.5, 1.0, 20.0);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glClearColor(0.0,0.0,0.0,0.0);

    // Initialize the light.
    glEnable(GL_LIGHTING);
    //Ambient Light
    glEnable(GL_LIGHT0);

    //Street Lights
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
}

// Display some useful remarks in the Xterm window.
void EventListener::help ()
{
    printf("Press a key to select a property.\n");
    printf(" w       wireframe mode          \n");
    printf(" f       fill mode               \n");
    printf(" s       smooth shading			 \n");
    printf(" b       flat shading			 \n");
    printf(" r       reset view position     \n");
    printf(" l       pitch 			         \n");
    printf(" ;       roll   			     \n");
    printf(" ""       yaw			         \n");
    printf(" 1       light1 camera			 \n");
    printf(" 2       light2 camera			 \n");
    printf(" 3       light3 camera			 \n");
    printf(" 4       light4 camera			 \n");
    printf(" 9       ghost camera			 \n");
    printf(" 0       pacman camera			 \n");
    printf(" f       flat shading			 \n");
    printf(" d       day			         \n");
    printf(" n       night			         \n");
    printf(" u       lightpost 1			 \n");
    printf(" i       lightpost 2			 \n");
    printf(" o       lightpost 3		   	 \n");
    printf(" z       all texture mapping     \n");
    printf(" x       pacman texture mapping  \n");
    printf(" c       pellet texture mapping  \n");
    printf(" ,       moving camera left      \n");
    printf(" .       moving camera right     \n");
    printf(" m       moving main camera by mouse   \n");
    printf(" [       zoom in by fovy		 \n");
    printf(" ]       zoom out by fovy		 \n");
}

void EventListener::specialKeys(GLint key, GLint x, GLint y)
{
    if(key == GLUT_KEY_UP)
    {

        char* canMove = this->map->whatDirectionsCanHeMove(this->map->pacman->getX(),this->map->pacman->getZ());
        this->map->pacman->walkForward(canMove);
        this->map->pacmanGhostCollisionDetection();
        this->map->gotPellet();
    }

    if(key == GLUT_KEY_DOWN)
    {
        char*  canMove = this->map->whatDirectionsCanHeMove(this->map->pacman->getX(),this->map->pacman->getZ());
        this->map->pacman->walkBackward(canMove);
        this->map->pacmanGhostCollisionDetection();
        this->map->gotPellet();
    }

    if(key == GLUT_KEY_LEFT)
    {
        this->map->pacman->turnLeft();
    }

    if(key == GLUT_KEY_RIGHT)
    {
        this->map->pacman->turnRight();
    }

    // Refresh the Window
    glutPostRedisplay();
}

void EventListener::resizeScene()
{
    if (this->height==0)				// Prevent A Divide By Zero If The Window Is Too Small
        this->height=1;

    glViewport(0, 0, this->width, this->height);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)this->width/(GLfloat)this->height,0.1f,140.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Respond to a keystroke.  Some responses are processed here; the default
// action is to record the keystroke and use it in the display callback function.
void EventListener::keys (unsigned char thiskey, GLint x, GLint y)
{
    //wireframe, smooth, flat from http://mindfuck.de-brauwer.be/articles/polygon/index.php
    switch (thiskey)
    {
    case 'ESC':
        exit(0);
    case '1':
        cout << "Look from camera light 1" << endl;
        cameraSwitch=2;
        break;
    case '2':
        cout << "Look from camera light 2" << endl;
        cameraSwitch=3;
        break;
    case '3':
        cout << "Look from camera light 3" << endl;
        cameraSwitch=4;
        break;
    case '4':
        cout << "Look from camera light 4" << endl;
        cameraSwitch=5;
        break;
    case '0':
        cout << "Look from pacman" << endl;
        cameraSwitch=6;
        break;
    case '9':
        cout << "Look from a ghost" << endl;
        cameraSwitch=7;
        break;
    case 'r':
        cout << "Reset Camera" << endl;
        cameraSwitch=1;
        break;
    case 'h':		// Display help in text window
        help();
        break;
    case 'w':
        cout << "Wireframe mode on " << endl;
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glutPostRedisplay();
        break;
    case 'f':
        cout << "Fill mode on " << endl;
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glutPostRedisplay();
        break;
    case 's':
        cout << "Smooth shading " << endl;
        glShadeModel(GL_SMOOTH);
        glutPostRedisplay();
        break;
    case 'b':
        cout << "Flat shading " << endl;
        glShadeModel(GL_FLAT);
        glutPostRedisplay();
        break;
    case 'd':
        cout << "Day time " << endl;
        glEnable(GL_LIGHT0);
        break;
    case 'n':
        cout << "Night time " << endl;
        glDisable(GL_LIGHT0);
        break;
    case 'y':
        this->map->masterStreetLightSwitch();
        break;
    case 'u':
        this->map->streetLightSwitch(0);
        break;
    case 'i':
        this->map->streetLightSwitch(1);
        break;
    case 'o':
        this->map->streetLightSwitch(2);
        break;
    case 'p':
        this->map->streetLightSwitch(3);
        break;
    case 'c':
        cout << "Switch Pellets Texture Maping" << endl;
        this->map->switchPelletsTexture();
        break;
    case 'z':
        cout << "Switch All Texture Maping" << endl;
        this->map->switchAllTexture();
        break;
    case 'x':
        this->map->pacman->switchTexture();
        break;
    case ',':
        cout << "Moving Camera to Left" << endl;
        cameraSwitch=8;
        moveAngle += 1;
        break;
    case '.':
        cout << "Moving Camera to Right" << endl;
        cameraSwitch=8;
        moveAngle -= 1;
        break;
    case 'm':
        cout << "Moving Main Camera by Mouse" << endl;
        if (mouseSwitch==false)
            mouseSwitch=true;
        else
            mouseSwitch=false;
        break;
    case '[':
        cout << "Zoom in by changing fovy " << endl;
        cameraSwitch=8;
        zoomMovingCamera += 2;
        glutPostRedisplay();
        break;
    case ']':
        cout << "Zoom out by changing fovy" << endl;
        cameraSwitch=8;
        zoomMovingCamera -= 2;
        glutPostRedisplay();
        break;
    case 'l':
        cout << " Pitching " << endl;
        cameraSwitch=9;
        this->map->camera9.RotateLocalX(this->pitch);
        this->pitch += 0.001;
        break;
    case ';':
        cout << " Rolling " << endl;
        cameraSwitch=9;
        this->map->camera9.RotateLocalZ(this->roll);
        this->roll += 0.001;
        break;
    case '"':
        cout << " Yawing " << endl;
        cameraSwitch=9;
        this->map->camera9.RotateLocalY(this->yaw);
        this->yaw += 0.001;
        break;
    case 'a':
        this->map->autoplay = !this->map->autoplay;
    case '5':
        this->fullScreenMode = !this->fullScreenMode;
        if(this->fullScreenMode==1)
        {
            glutFullScreen();
        }
        else
        {
            glutPositionWindow(40,40);
            glutReshapeWindow(this->width,this->height);
            this->resizeScene();
        }
        break;
    case '6':
        this->map->newLevel();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
