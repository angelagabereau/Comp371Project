#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "strstream"

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


using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::fstream;

using namespace std;

const int ESC = 27;

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
    this->map = new Map();
}

EventListener::~EventListener()
{
    //dtor
}

void EventListener::drawScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();				// Reset The View

//  glTranslatef(0.0f,-2.0f,-10.0f);
    glTranslatef(-0.0f,0.0f,-20.0f);
    //
    glRotatef(90.0,1.0, 0.0,0.0);
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix

    // gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0, 1.5, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
    printf(" up      pitch 			         \n");
    printf(" down    roll   			     \n");
    printf(" left    yaw			         \n");
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
}





void EventListener::specialKeys(GLint key, GLint x, GLint y)
{
    if(key == GLUT_KEY_UP)
    {
     //   cout << "up " << endl;
     char* whereHeIs = this->map->whereIsHe();
        //  cout<<whereHeIs<<" Where is he? "<<endl;
        this->map->pacman->walkForward(whereHeIs);
    }

    if(key == GLUT_KEY_DOWN)
    {
          char* whereHeIs = this->map->whereIsHe();
        //  cout<<whereHeIs<<" Where is he? "<<endl;

        this->map->pacman->walkBackward(whereHeIs);
    }

    if(key == GLUT_KEY_LEFT)
    {
     //   cout << "right " << endl;
        this->map->pacman->turnLeft();
    }

    if(key == GLUT_KEY_RIGHT)
    {
       // cout << "left " << endl;
        this->map->pacman->turnRight();
    }

    /*  if(key == GLUT_KEY_UP)
      {
          cameraW.RotateLocalX(pitch);
          pitch += 0.001;

      }

      if(key == GLUT_KEY_DOWN)
      {
          cameraW.RotateLocalZ(roll);
          roll += 0.001;
      }

      if(key == GLUT_KEY_LEFT)
      {
          cameraW.RotateLocalY(yaw);
          yaw += 0.001;
      }
    */
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
        /*  case '1':
               cameraW.SetOrigin(-14.0,4.0,-49.0);
               cameraW.SetForwardVector(1.0,-1.0,1.0);
               break;
           case '2':
               cameraW.SetOrigin(-14.0,4.0,-22.0);
               cameraW.SetForwardVector(1.0,-1.0,-1.0);
               break;
           case '3':
               cameraW.SetOrigin(13.0,4.0,-49.0);
               cameraW.SetForwardVector(-1.0,-1.0,1.0);
               break;
           case '4':
               cameraW.SetOrigin(13.0,4.0,-22.0);
               cameraW.SetForwardVector(-1.0,-1.0,-1.0);
               break;
           case '0':
               cameraW.SetOrigin(-10.0,1.8,-45.0);
               cameraW.SetForwardVector(0.0,0.0,1.0);
               break;
           case '9':
               cameraW.SetOrigin(-9.0,1.8,-50.0);
               cameraW.SetForwardVector(0.0,0.0,1.0);
               break;
           case 'r':
               cameraW.Normalize();
               cameraW.SetOrigin(0.0,10.0,0.0);
               cameraW.SetForwardVector(0.0,0.0,-1.0);
               //cameraP.Normalize();
               //cameraP.SetOrigin(0.0,10.0,0.0);
               //cameraP.SetForwardVector(0.0,0.0,-1.0);
               //cameraG.Normalize();
               //cameraG.SetOrigin(0.0,10.0,0.0);
               //cameraG.SetForwardVector(0.0,0.0,-1.0);
               break;*/
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
    default:
        break;
    }
    glutPostRedisplay();
}
