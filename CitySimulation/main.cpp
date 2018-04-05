#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Math.h>
#include <string.h>
#include <Windows.h>
#include <MMSystem.h>
#include <time.h>
#include <math.h>

#define COLUMNS 600
#define ROWS 600
#define ROUND(a) ((int) (a + 0.5))

extern short CarDirection;
extern short CarLength;
extern short Car;
extern short HIT;
extern short posX[];
extern short posY[];
extern short R1check;
extern short R2check;
extern short R3check;
extern short R4check;
extern short R5check;
extern short R6check;
extern short Delay;
extern short Accelerate;


int FPS=100;
float H1=0.0,H2=COLUMNS;
float V1=0.0,V2=ROWS;


void Keyboard_callback(int,int,int);
void Timer_callback(int);
void Display_callback();
void Reshape_callback(int,int);
void InputKeys_callback(unsigned char, int , int );

void init()
{
    glClearColor(0,0.2,0,1.0);
    initGrid(COLUMNS,ROWS);

}

int main(int argv,char **argc)
{
    glutInit(&argv,argc);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(700,700);
    glutCreateWindow("Car Game");
    glutDisplayFunc(Display_callback);
    glutReshapeFunc(Reshape_callback);
    glutTimerFunc(0,Timer_callback,0);
    glutKeyboardFunc(InputKeys_callback);
    glutSpecialFunc(Keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}

void Display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Delay++;
    printf("%d\n",Delay);
    BackGround();
    DrawRoad();
    DrawCar();
    RandomCar();
    EnvironMent1();
    DrawBoat();
    DrawHeli();
    glutSwapBuffers();
}

void Reshape_callback(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(H1,H2,V1,V2+200,-1000.0,1000.0);
    glMatrixMode(GL_MODELVIEW);

}

void Timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,Timer_callback,0);

}

void Keyboard_callback(int key,int,int)
{
    switch(key)
    {
        case GLUT_KEY_UP:

            if(CarDirection!=DOWN)
            {
                Accelerate=1;
                CarDirection=UP;
                Car=true;
                HIT=0;
                R1check=true;
                R2check=true;
                R3check=true;
                R4check=true;
                R5check=true;
            }

            break;

        case GLUT_KEY_DOWN:

            if(CarDirection!=UP)
            {
                Accelerate=1;
                CarDirection=DOWN;
                Car=true;
                HIT=0;
                R1check=true;
                R2check=true;
                R3check=true;
                R4check=true;
                R5check=true;
            }

            break;

        case GLUT_KEY_RIGHT:

            if(CarDirection!=LEFT)
            {
                Accelerate=1;
                CarDirection=RIGHT;
                Car=true;
                HIT=0;
                if(posX[0]>550)
                {
                   glTranslatef(-11.0,0.0,0.0);
                }
                if(posX[0]<550)
                {
                    glTranslatef(-1.0,0.0,0.0);
                }

                R1check=true;
                R2check=true;
                R3check=true;
                R4check=true;
                R5check=true;
            }

            break;

        case GLUT_KEY_LEFT:

            if(CarDirection!=RIGHT)
            {
                Accelerate=1;
                CarDirection=LEFT;
                Car=true;
                HIT=0;
                if(posX[0]>550)
                {
                    glTranslatef(11.0,0.0,0.0);
                }
                if(posX[0]<550)
                {
                    glTranslatef(1.0,0.0,0.0);
                }

                R1check=true;
                R2check=true;
                R3check=true;
                R4check=true;
                R5check=true;
            }

            break;

    }
}

void InputKeys_callback(unsigned char Key, int, int)
{
    if(Key==32)
    {
        Car=false;
    }
    else if(Key==87 || Key==119)
    {
        if(FPS<800)
        {
             FPS=FPS+1;
        }
    }
    else if(Key==83 || Key==115)
    {
        if(FPS>1)
        {
           FPS=FPS-1;
        }
    }
    else if(Key==100)
    {
        glTranslatef(-20.0,0.0,0.0);
    }
    else if(Key==97)
    {

        glTranslatef(20.0,0.0,0.0);
    }
    else if(Key==117)
    {
        glScalef(0.99,0.99,1);
    }
    else if(Key==106)
    {
        glScalef(1.01,1.01,0);
    }
}

