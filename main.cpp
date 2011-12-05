#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include "SOIL/SOIL.h"

/* ascii code for the escape key */
#define ESCAPE 27

#include "EventListener.h"

/* The number of our GLUT window */
int window;

EventListener *eventListener;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL()	        // We call this right after our OpenGL window is created.
{
    eventListener->initGL();
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    eventListener->resizeScene();
}

/* The main drawing function. */
void DrawGLScene()
{
    eventListener->drawScene();
}

void Keys (unsigned char thiskey, GLint x, GLint y)
{
    eventListener->keys(thiskey,x,y);
}

void SpecialKeys (GLint key, GLint x, GLint y)
{
    eventListener->specialKeys(key,x,y);
}

void MouseFunc(int button, int state, int x, int y)
{
    eventListener->mouse->mouseFunc(button,state,x,y);
}

void MouseMotion(int x, int y)
{
    eventListener->mouse->mouseMotion(x,y);
}

int main(int argc, char **argv)
{
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
       X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
    glutInit(&argc, argv);

    /* Select type of Display mode:
     Double buffer
     RGBA color
     Alpha components supported
     Depth buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);

    /* Open a window */
    glutCreateWindow("Comp 371 - Final Project - Team 8 -  Press 'h' for instructions.");

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);

    /* Go fullscreen.  This is as soon as possible. */
    //glutFullScreen();

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&Keys);
    glutSpecialFunc(&SpecialKeys);

    // Register the function called when the mouse is moved
    glutMouseFunc(&MouseFunc);
    glutMotionFunc(&MouseMotion);

    eventListener = new EventListener(640,480);

    /* Initialize our window. */
    InitGL();

    glEnable(GL_DEPTH_TEST); //enabling z-buffer

    /* Start Event Processing Engine */
    glutMainLoop();

    return 1;

}
