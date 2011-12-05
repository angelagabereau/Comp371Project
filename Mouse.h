#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glut.h>
#include <cmath>

class Mouse
{
public:
    Mouse();
    virtual ~Mouse();
    void calEyePosition();
    void moveBackward();
    void moveForward();
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
    void mouseLookAt();
    void mouseMotion(GLint x, GLint y);
    void mouseFunc(GLint button, GLint state, GLint x, GLint y);
private:

    // record the state of mouse
    GLboolean mouserdown;
    GLboolean mouseldown;
    GLboolean mousemdown;

    // when a mouse-key is pressed, record current mouse position
    GLint mouseX;
    GLint mouseY;

    // center position
    GLfloat center[3];

    // eye's position
    GLfloat eye[3];

    // angle between y-axis and look direction
    GLfloat yRotate;

    // angle between x-axis and look direction
    GLfloat xRotate;

    // length between center and eye
    GLfloat cenLength;

    // center move speed
    GLfloat mSpeed;

    // rotate speed
    GLfloat rSpeed;

    // reserved
    GLfloat lSpeed;

};

#endif // MOUSE_H
