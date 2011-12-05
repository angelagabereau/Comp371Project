#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <GL/glut.h>
#include "glFrame.h"
#include "Map.h"
#include "math3d.h"
#include "Mouse.h"

class EventListener
{
public:
    EventListener(GLint width, GLint height);
    virtual ~EventListener();
    void help();
    void specialKeys(GLint key, GLint x, GLint y);
    void keys (unsigned char thiskey, GLint x, GLint y);
    void resizeScene();
    void drawScene();
    void initGL();
	Mouse *mouse;
protected:
    GLint height;
    GLint width;
    bool textureSwitch;
    bool light1Switch;
    bool light2Switch;
    bool light3Switch;
    bool light4Switch;
    bool fullScreenMode;
    Map *map;
	int cameraSwitch;
	bool mouseSwitch;
	bool zoomByFovy;
	float yaw;
	float roll;
	float pitch;
	float moveAngle;
	float zoomMovingCamera;
private:
};

#endif // EVENTLISTENER_H
