#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "StopWatch.h"

StopWatch stopWatch;
bool started = false;

void Draw(int i) {
    // drawing clock
    double d;
    glPushMatrix();
    glRotatef(i*6, 0,0,1);
    if(i%5==0) d=2.0;
    else d = 1.0;
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.01*d, 1.0, 0.0);
    glVertex3f( 0.01*d, 1.0, 0.0);
    glVertex3f( 0.0 , 1.0-0.1*d, 0.0);
    glEnd();
    glPopMatrix();
}
void changeSize(int w, int h) {
    if(h == 0) h = 1;
    float ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
}
void renderScene(void) {
    if(!started) {
        stopWatch.start();
        started = true;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0, 0.0f,1.0f,0.0f);
    for(int i=0; i<60; i++) { Draw(i); } // 시계를 그린다
    glColor3f(0,0,0);

    static float sec;
	int angle;

	stopWatch.stop();
    float dt = stopWatch.getElapsedTime(); // 흐른 시간을 측정한다.
    stopWatch.start();
    sec += dt/1000000.0; // 바늘의 위치를 정한다
	int iSec = (int) sec;
	angle = 6*iSec;
	


    glPushMatrix();
    glRotatef(-angle, 0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0); // 바늘을 그린다
    glVertex3f(0.0,1.0,0.0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Dr.Kang's Animation Lecture - 00");
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8,0.8,1.0,1.0);
    glutMainLoop();
    return 0;
}