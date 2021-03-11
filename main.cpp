#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "BmpLoader.h"
#include <iostream>

using namespace std;

/*
Author : Kresna Bayu Sanyoto 181511051 JTK POLBAN
Created : 17 Januari 2021
Subject : computer graphics
*/

//Global Variable
GLint spin_x = 0,spin_y = 0;
GLfloat New_x,New_y,Zoom = 1,movement= 0;
GLuint grassTexture, sideFTexture, floorTexture, wallTexture, roofTexture, garageDoorTexture, windowTexture,doorTexture, porchWinTexture, skyTexture, stoneWallTexture;

//Method declaration
void init();//inisiate our openGL
void scene();
void display();
void reshape(int w, int h);
void time(int x);
void specialKey(int key, int x, int y);
void mouseMovement(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void scroll (int button, int dir, int x, int y);
GLuint loadTexture(const char* filename);

//Main
int main(int argc, char** argv)
{
    cout << "List funngsi keyboard dan mouse\n";
    cout << "Klik mouse lalu drag dan lepas pada sumbu x -> digunakan untuk merotate objek di sumbu x\n";
    cout << "Scroll untuk Zoom\n";
    cout << "page up untuk zoom in dan page down untuk zoom out\n";
    cout << "arrow key kanan dan kiri untuk rotasi pada sumbu x\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Kresna Bayu Sanyoto - 181511051 [3D House]");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKey);
    //glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseMovement);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(scroll);
    init();
    glutMainLoop();
    return 0;
}
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    //load texture
    grassTexture= loadTexture("grass.bmp");
    sideFTexture= loadTexture("side_foundation.bmp");
    floorTexture= loadTexture("floor.bmp");
    wallTexture= loadTexture("wall.bmp");
    roofTexture= loadTexture("roof.bmp");
    garageDoorTexture= loadTexture("garage_door.bmp");
    windowTexture= loadTexture("window.bmp");
    doorTexture= loadTexture("door.bmp");
    porchWinTexture= loadTexture("porch_window.bmp");
    skyTexture= loadTexture("sky.bmp");
    stoneWallTexture= loadTexture("stone_wall.bmp");
}
void scene()
{
    glTranslatef(0.0f, 0.0f, -40.0f);
    gluLookAt(10.0, 10.0, 10.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
    glRotatef(spin_x, 0.0, 1.0, 0.0);
    //glRotatef(spin_y, 0.0, 0.0, 1.0);
    glScalef(Zoom, Zoom, Zoom);

    glColor3f(1, 1, 1);
    GLfloat houseBase[4][3] =
    {
        {-60,0.0,60.0},
        {60,0.0,60.0},
        {60,0.0,-60.0},
        {-60,0.0,-60.0},
    };
    GLfloat texcoor[4][3] =
    {
        {0.0,20.0,0},
        {0.0,0.0,0},
        {20.0,0.0,0},
        {20.0,20.0,0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        for(unsigned int i = 0; i< sizeof(houseBase)/sizeof(houseBase[0]);i++){
            glTexCoord3f(texcoor[i][0],texcoor[i][1],texcoor[i][2]);
            glVertex3f(houseBase[i][0],houseBase[i][1],houseBase[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat foundationSide[18][3] =
    {
        {-5,0.5,5.0},
        {-5,0.0,5.0},
        {15,0.5,5.0},
        {15,0.0,5.0},
        {15,0.5,-5.0},
        {15,0.0,-5.0},
        {-5,0.5,-5.0},
        {-5,0.0,-5.0},
        {-5,0.5,-6.0},
        {-5,0.0,-6.0},
        {-15,0.5,-6.0},
        {-15,0.0,-6.0},
        {-15,0.5,6.0},
        {-15,0.0,6.0},
        {-5,0.5,6.0},
        {-5,0.0,6.0},
        {-5,0.5,5.0},
        {-5,0.0,5.0},

    };
    GLfloat texcoor1[18][3] =
    {
        {0,0.25,0},
        {0,0.0,0},
        {10.0,0.25,0},
        {10.0,0.0,0},
        {15.0,0.25,0},
        {15.0,0.0,0},
        {25.0,0.25,0},
        {25.0,0.0,0},
        {25.1,0.25,0},
        {25.1,0.0,0},
        {30.5,0.25,0},
        {30.5,0.0,0},
        {36.5,0.25,0},
        {36.5,0.0,0},
        {46.5,0.25,0},
        {46.5,0.0,0},
        {47,0.25,0},
        {47,0.0,0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sideFTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(foundationSide)/sizeof(foundationSide[0]);i++){
            glTexCoord3f(texcoor1[i][0],texcoor1[i][1],texcoor1[i][2]);
            glVertex3f(foundationSide[i][0],foundationSide[i][1],foundationSide[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat foundationTop[10][3] =
    {
        {-5,0.5,5.0},
        {15,0.5,5.0},
        {15,0.5,-5.0},
        {-5,0.5,-5.0},

        {-15,0.5,6.0},
        {-5,0.5,6.0},
        {-5,0.5,-6.0},
        {-15,0.5,-6.0},
    };
    GLfloat texcoor2[4][3] =
    {
        {0,0,0},
        {0,2.0,0},
        {1,0,0},
        {1,2.0,0},
    };
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        for(unsigned int i = 0; i< sizeof(foundationTop)/sizeof(foundationTop[0]);i++){
            if(i>=4){
                glTexCoord3f(texcoor2[i][0],texcoor2[i][1],texcoor2[i][2]);
            }
            glVertex3f(foundationTop[i][0],foundationTop[i][1],foundationTop[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    GLfloat wallOne[8][3] =
    {
        {7.5,10.5,5.0},
        {7.5,0.5,5.0},
        {15,7.5,5.0},
        {15,0.5,5.0},
        {15,7.5,-5.0},
        {15,0.5,-5.0},
        {7.5,10.5,-5.0},
        {7.5,0.5,-5.0},
    };
    GLfloat texcoor3[10][3] =
    {
        {0.0,3,0.0},
        {0.0,0.0,0.0},
        {2.5,3,0.0},
        {2.5,0.0,0.0},
        {5.5,3,0.0},
        {5.5,0.0,0.0},
        {8,3,0.0},
        {8,0.0,0.0},
        {11,3,0.0},
        {11,0.0,0.0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(wallOne)/sizeof(wallOne[0]);i++){
            glTexCoord3f(texcoor3[i][0],texcoor3[i][1],texcoor3[i][2]);
            glVertex3f(wallOne[i][0],wallOne[i][1],wallOne[i][2]+movement);
        }
    glEnd();
    glPopMatrix();
    GLfloat wallTwo[10][3] =
    {
        {7.5,13.5,5.0},
        {7.5,0.5,5.0},
        {7.5,13.5,-5.0},
        {7.5,0.5,-5.0},
        {-5.0,10.5,-5.0},
        {-5.0,0.5,-5.0},
        {-5.0,10.5,5.0},
        {-5.0,0.5,5.0},
        {7.5,13.5,5.0},
        {7.5,0.5,5.0},
    };
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(wallTwo)/sizeof(wallTwo[0]);i++){
            glTexCoord3f(texcoor3[i][0],texcoor3[i][1],texcoor3[i][2]);
            glVertex3f(wallTwo[i][0],wallTwo[i][1],wallTwo[i][2]+movement);
        }
    glEnd();
    glPopMatrix();
    GLfloat wallThree[8][3] =
    {
        {-5.0,8.5,4.0},
        {-5.0,0.5,4.0},
        {-13.0,5.0,4.0},
        {-13.0,0.5,4.0},
        {-13.0,5.0,-5.0},
        {-13.0,0.5,-5.0},
        {-5.0,8.5,-5.0},
        {-5.0,0.5,-5.0},
    };
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(wallThree)/sizeof(wallThree[0]);i++){
            glTexCoord3f(texcoor3[i][0],texcoor3[i][1],texcoor3[i][2]);
            glVertex3f(wallThree[i][0],wallThree[i][1],wallThree[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat roof[12][3] =
    {
        {15.3,7.4,-5.3},
        {15.3,7.4,5.3},
        {7.5,10.5,5.3},
        {7.5,10.5,-5.3},

        {-5.3,10.5,5.3},
        {-5.3,10.5,-5.3},
        {7.8,13.6,-5.3},
        {7.8,13.6,5.3},

        {-15.0,4.2,6.0},
        {-15.0,4.2,-6.0},
        {-5.0,8.5,-6.0},
        {-5.0,8.5,6.0},

    };
    GLfloat texcoor4[4][3] =
    {
        {3,0,0},
        {0,0,0},
        {0,3,0},
        {3,3,0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, roofTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        int r=0;
        for(unsigned int i = 0; i< sizeof(roof)/sizeof(roof[0]);i++){
            if(r>=4)
            {
                r=0;
            }
            glTexCoord3f(texcoor4[r][0],texcoor4[r][1],texcoor4[r][2]);
            r++;
            glVertex3f(roof[i][0],roof[i][1],roof[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat garageDoor[4][3] =
    {
        {14.6,0,5.1},
        {14.6,6,5.1},
        {7.9,6,5.1},
        {7.9,0,5.1},
    };
    GLfloat texcoor5[4][3] =
    {
        {0,0,0},
        {0,1,0},
        {1,1,0},
        {1,0,0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, garageDoorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        for(unsigned int i = 0; i< sizeof(garageDoor)/sizeof(garageDoor[0]);i++){
            glTexCoord3f(texcoor5[i][0],texcoor5[i][1],texcoor5[i][2]);
            glVertex3f(garageDoor[i][0],garageDoor[i][1],garageDoor[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat window[20][3] =
    {
        {15.1,2.0,-1.0},
        {15.1,5.0,-1.0},
        {15.1,5.0,-3.0},
        {15.1,2.0,-3.0},

        {4.5,2.0,5.1},
        {4.5,5.0,5.1},
        {6.5,5.0,5.1},
        {6.5,2.0,5.1},

        {4.5,8.0,5.1},
        {4.5,11.0,5.1},
        {6.5,11.0,5.1},
        {6.5,8.0,5.1},

        {3.5,2.0,-5.1},
        {3.5,5.0,-5.1},
        {5.5,5.0,-5.1},
        {5.5,2.0,-5.1},

        {-1.5,2.0,-5.1},
        {-1.5,5.0,-5.1},
        {-3.5,5.0,-5.1},
        {-3.5,2.0,-5.1},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, windowTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        r=0;
        for(unsigned int i = 0; i< sizeof(window)/sizeof(window[0]);i++){
            if(r>=4)
            {
                r=0;
            }
            glTexCoord3f(texcoor5[r][0],texcoor5[r][1],texcoor5[r][2]);
            r++;
            glVertex3f(window[i][0],window[i][1],window[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat door[4][3] =
    {
        {-2.0,0.5,5.1},
        {-2.0,5.5,5.1},
        {2.5,5.5,5.1},
        {2.5,0.5,5.1},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, doorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        for(unsigned int i = 0; i< sizeof(door)/sizeof(door[0]);i++){
            glTexCoord3f(texcoor5[i][0],texcoor5[i][1],texcoor5[i][2]);
            glVertex3f(door[i][0],door[i][1],door[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat porchWindow[8][3] =
    {
        {-12.0,0.5,4.1},
        {-12.0,4.0,4.1},
        {-6.0,4.0,4.1},
        {-6.0,0.5,4.1},

        {-13.1,0.5,-4},
        {-13.1,4.0,-4},
        {-13.1,4.0,3},
        {-13.1,0.5,3},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, porchWinTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        r=0;
        for(unsigned int i = 0; i< sizeof(porchWindow)/sizeof(porchWindow[0]);i++){
            if(r>=4)
            {
                r=0;
            }
            glTexCoord3f(texcoor5[r][0],texcoor5[r][1],texcoor5[r][2]);
            r++;
            glVertex3f(porchWindow[i][0],porchWindow[i][1],porchWindow[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat sky[10][3] =
    {
        {60,0,60},
        {60,60,60},
        {-60,0,60},
        {-60,60,60},
        {-60,0,-60},
        {-60,60,-60},
        {60,0,-60},
        {60,60,-60},
        {60,0,60},
        {60,60,60},
    };
    GLfloat texcoor6[10][3] =
    {
        {0,0,0},
        {0,1,0},
        {1,0,0},
        {1,1,0},
        {2,0,0},
        {2,1,0},
        {3,0,0},
        {3,1,0},
        {4,0,0},
        {4,1,0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, skyTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(sky)/sizeof(sky[0]);i++){
            glTexCoord3f(texcoor6[i][0],texcoor6[i][1],texcoor6[i][2]);
            glVertex3f(sky[i][0],sky[i][1],sky[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat stoneWall[34][3] =
    {
        {14,0,12},
        {14,8,12},
        {17,0,12},
        {17,4,12},
        {20,0,12},
        {20,4,12},
        {20,0,-9},
        {20,4,-9},
        {-20,0,-9},
        {-20,4,-9},
        {-20,0,12},
        {-20,4,12},
        {4,0,12},
        {4,4,12},
        {7,0,12},
        {7,8,12},

        {7,0,13},
        {7,8,13},
        {4,0,13},
        {4,4,13},
        {-21,0,13},
        {-21,4,13},
        {-21,0,-10},
        {-21,4,-10},
        {21,0,-10},
        {21,4,-10},
        {21,0,13},
        {21,4,13},
        {17,0,13},
        {17,4,13},
        {14,0,13},
        {14,8,13},
        {14,0,12},
        {14,8,12},

    };

    GLfloat texcoor7[34][3] =
    {
        {0,0,0},
        {0,2,0},
        {1.5,0,0},
        {1.5,2,0},
        {3,0,0},
        {3,1,0},
        {8,0,0},
        {8,1,0},
        {18,0,0},
        {18,1,0},
        {23,0,0},
        {23,1,0},
        {30,0,0},
        {30,1,0},
        {31.5,0,0},
        {31.5,1,0},
        {32,0,0},
        {32,1,0},
        {33.5,0,0},
        {33.5,1,0},
        {40.5,0,0},
        {40.5,1,0},
        {45.5,0,0},
        {45.5,1,0},
        {55.5,0,0},
        {55.5,1,0},
        {60.5,0,0},
        {60.5,1,0},
        {62,0,0},
        {62,1,0},
        {63.5,0,0},
        {63.5,2,0},
        {64.5,0,0},
        {64.5,2,0},
    };
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, stoneWallTexture);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(stoneWall)/sizeof(stoneWall[0]);i++){
            glTexCoord3f(texcoor7[i][0],texcoor7[i][1],texcoor7[i][2]);
            glVertex3f(stoneWall[i][0],stoneWall[i][1],stoneWall[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    GLfloat stoneWallTop[16][3] =
    {
        {14,8,12},
        {14,8,13},
        {17,4,12},
        {17,4,13},
        {20,4,12},
        {21,4,13},
        {20,4,-9},
        {21,4,-10},
        {-20,4,-9},
        {-21,4,-10},
        {-20,4,12},
        {-21,4,13},
        {4,4,12},
        {4,4,13},
        {7,8,12},
        {7,8,13},
    };
    GLfloat texcoor8[16][3] =
    {
        {2,0.25,0},
        {2,0,0},
        {4,0.25,0},
        {4,0,0},
        {7,0.25,0},
        {7,0,0},
        {13,0.25,0},
        {13,0,0},
        {23,0.25,0},
        {23,0,0},
        {28,0.25,0},
        {28,0,0},
        {35,0.25,0},
        {35,0,0},
        {37,0.25,0},
        {37,0,0},
    };

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, stoneWallTexture);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
        for(unsigned int i = 0; i< sizeof(stoneWallTop)/sizeof(stoneWallTop[0]);i++){
            glTexCoord3f(texcoor8[i][0],texcoor8[i][1],texcoor8[i][2]);
            glVertex3f(stoneWallTop[i][0],stoneWallTop[i][1],stoneWallTop[i][2]+movement);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    scene();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}
void time(int x){
    glutPostRedisplay();
    glutTimerFunc(1000/60, time, 0);
}
void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		spin_y += 1;
		spin_y = spin_y % 360;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		spin_y -= 1;
		spin_y = spin_y % 360;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_LEFT:
	{
		spin_x += 1;
		spin_x = spin_x % 360;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		spin_x -= 1;
		spin_x = spin_x % 360;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		Zoom = Zoom + 0.01;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		if (Zoom >= 0) {
			Zoom = Zoom - 0.01;
		}
		glutPostRedisplay();
		break;
	}
	}
}
void mouseMovement(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		New_x = x;
		New_y = y;
	}
}
void mouseMotion(int x, int y)
{
	spin_x = x - New_x;
	spin_y = y - New_y;
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key){
    case 'w':
        {
            movement+=0.20;
            glutPostRedisplay();
            break;
        }
    case 's':
        {
            movement-=0.20;
            glutPostRedisplay();
            break;
        }

    }

}
void scroll (int button, int dir, int x, int y){
    if (dir > 0){
        Zoom = Zoom + 0.01;
		glutPostRedisplay();
    }else{
        if (Zoom >= 0) {
			Zoom = Zoom - 0.01;
		}
		glutPostRedisplay();
    }
}
GLuint loadTexture(const char* filename) {
	BmpLoader bl(filename);
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 bl.iWidth, bl.iHeight,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 bl.textureData);
	return textureId;
}
