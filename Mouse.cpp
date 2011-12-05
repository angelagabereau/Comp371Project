#include "Mouse.h"

#define PI 3.1415926

using namespace std;

Mouse::Mouse()
{
	this->mouserdown = GL_FALSE;
	this->mouseldown = GL_FALSE;
	this->mousemdown = GL_FALSE;

	this->mouseX = 0;
	this->mouseY = 0;

	this->center[0] = 28.0;
	this->center[1] = 0.0;
	this->center[2] = 28.0;

	this->xRotate = PI/4;
	this->yRotate = PI/4;
	this->cenLength = 80.0f;

	this->mSpeed = 0.4;
	this->rSpeed = 0.02;
	this->lSpeed = 0.4;

}

Mouse::~Mouse()
{
	//dtor
}

// calculate the eye position according to center position, angle and length 
void Mouse::calEyePosition()  
{
	if(this->yRotate > PI/2.2)
		this->yRotate = PI/2.2; 

	if(this->yRotate < 0.01)  
		this->yRotate = 0.01;

	if(this->xRotate > 2*PI)   
		this->xRotate = 0.01;

	if(this->xRotate < 0)   
		this->xRotate = 2 * PI;

	if(this->cenLength > 100)  
		this->cenLength = 100; 

	if(this->cenLength < 5)   
		this->cenLength = 5;

	this->eye[0] = this->center[0] + this->cenLength * sin(this->yRotate) * cos(this->xRotate);  
	this->eye[2] = this->center[2] + this->cenLength * sin(this->yRotate) * sin(this->xRotate);
	this->eye[1] = this->center[1] + this->cenLength * cos(this->yRotate);

}

// center moves
void Mouse::moveBackward()              
{
	this->center[0] += this->mSpeed * cos(this->xRotate);
	this->center[2] += this->mSpeed * sin(this->xRotate);
	this->calEyePosition();
}

void Mouse::moveForward()
{
	this->center[0] -= this->mSpeed * cos(this->xRotate);
	this->center[2] -= this->mSpeed * sin(this->xRotate);
	this->calEyePosition();
}

/// visual angle rotates
void Mouse::rotateLeft()
{
	this->xRotate -= this->rSpeed;
	this->calEyePosition();
}

void Mouse::rotateRight()
{
	this->xRotate += this->rSpeed;
	this->calEyePosition();
}

void Mouse::rotateUp()
{
	this->yRotate += this->rSpeed;
	this->calEyePosition();
}

void Mouse::rotateDown()
{
	this->yRotate -= this->rSpeed;
	this->calEyePosition();
}

/// call back func for mouse kicks
void Mouse::mouseFunc(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		if(button == GLUT_RIGHT_BUTTON) 
			this->mouserdown = GL_TRUE;
		if(button == GLUT_LEFT_BUTTON) 
			this->mouseldown = GL_TRUE;
		if(button == GLUT_MIDDLE_BUTTON)
			this->mousemdown = GL_TRUE;
	}
	else
	{
		if(button == GLUT_RIGHT_BUTTON) 
			this->mouserdown = GL_FALSE;
		if(button == GLUT_LEFT_BUTTON) 
			this->mouseldown = GL_FALSE;
		if(button == GLUT_MIDDLE_BUTTON)
			this->mousemdown = GL_FALSE;
	}
	mouseX = x, mouseY = y;
}

/// call back func for mouse motions
void Mouse::mouseMotion(int x, int y)
{
	if(this->mouserdown == GL_TRUE)
	{      
		this->xRotate += (x - this->mouseX) / 80.0f;     
		this->yRotate -= (y - this->mouseY) / 120.0f;
	}

	if(this->mouseldown == GL_TRUE)
	{
		this->cenLength += (y - this->mouseY) / 25.0f;
	}
	this->mouseX = x, this->mouseY = y;
	this->calEyePosition();
	glutPostRedisplay();
}

void Mouse::mouseLookAt()           
{
	this->calEyePosition();
	gluLookAt(this->eye[0], this->eye[1], this->eye[2],
			  this->center[0], this->center[1], this->center[2],
			  0, 1, 0);
}