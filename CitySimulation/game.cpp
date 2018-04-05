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
#define ROUND(a) ((int) (a + 0.5))

int gridX,gridY;
int HIT=0;

int Accelerate=0;
float speed=1;
int Delay=0;

int Y11=100,Y12=130,Y13=170,Y14=200,Y15=155;
int boat1=1;

int Y21=600,Y22=630,Y23=670,Y24=700,Y25=655;
int boat2=2;

int Hx11=50,Hy11=780,Hx12=80,Hy12=810;
float angle=10;

int posX[3]={20,20,20},posY[3]={20,30,40};
int CarLength=3;
bool Car=true;
int CarDirection=UP;

int R1posX[2]={30,40},R1posY[2]={560,560};
bool R1check=true;
int tag1=1;

int R2posX[2]={680,690},R2posY[2]={580,580};
bool R2check=true;
int tag2=2;


int R3posX[2]={510,520},R3posY[2]={580,580};
bool R3check=true;
int tag3=3;

int R4posX[2]={5,5},R4posY[2]={-10,0};
bool R4check=true;
int tag4=4;
int dir4=UP;

int R5posX[2]={5,5},R5posY[2]={-30,-20};
bool R5check=false;
int tag5=5;

int R6posX[3]={605,605,605},R6posY[3]={-30,-20,-10};
bool R6check=true;
int tag6=6;


void print(int x, int y,int f, char *string)
{
    glRasterPos2f(x,y);
    int len = (int) strlen(string);
    for (int i = 0; i < len; i++)
    {
        if(f==1)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        }
        else if(f==2)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15,string[i]);
        }
        else if(f==3)
        {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13,string[i]);
        }
        else if(f==4)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
        }
        else if(f==5)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
        }
        else if(f==6)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
        }
        else if(f==7)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,string[i]);
        }
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        }
    }
}
float round_value(float v)
{
  return floor(v + 0.5);
}

void DrawLine(float X1,float Y1,float X2,float Y2,float size)
{
double dx=(X2-X1);
  double dy=(Y2-Y1);
  double steps;
  float xInc,yInc,x=X1,y=Y1;

  glPointSize(size);

  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;


  glBegin(GL_POINTS);

  glVertex2d(x,y);
  int k;

  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(round_value(x), round_value(y));
  }
  glEnd();

  glFlush();
}

void DrawTriangle(float X1,float Y1,float X2,float Y2,float X3,float Y3)
{
    DrawLine(X1,Y1,X2,Y2,2);
    DrawLine(X2,Y2,X3,Y3,2);
    DrawLine(X3,Y3,X1,Y1,2);
    scanfill(X1,Y1,X2,Y2,X3,Y3,X3,Y3,2);
}

void plot(float x, float y,float pntX1,float pntY1,float size)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x+pntX1, y+pntY1);
	glEnd();
}
void DrawCircle(float pntX1,float pntY1,float r,float size)
{
	float x = 0;
	float y = r;
	float decision = 5/4 - r;
	plot(x, y,pntX1,pntY1,size);

	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2*x+1;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+1;
		}
		plot(x, y,pntX1,pntY1,size);
		plot(x, -y,pntX1,pntY1,size);
		plot(-x, y,pntX1,pntY1,size);
		plot(-x, -y,pntX1,pntY1,size);
		plot(y, x,pntX1,pntY1,size);
		plot(-y, x,pntX1,pntY1,size);
		plot(y, -x,pntX1,pntY1,size);
		plot(-y, -x,pntX1,pntY1,size);
	}
}
void initGrid(int x,int y)
{
    gridX=x;
    gridY=y;
}
void UnitSquare(int x,int y)
{
    if(x==0 || y==0 || x==gridX-10 || y==gridY-10)
    {
        glLineWidth(3.0);
        glColor3f(0,0.2,0);

    }
    else
    {
        glLineWidth(3.0);
        glColor3f(0,0.2,0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x,y);
            glVertex2f(x+10,y);
            glVertex2f(x+10,y+10);
            glVertex2f(x,y+10);
        glEnd();
    }
}
void DrawGrid()
{
    for(int x=0;x<gridX;x=x+10)
    {
        for(int y=0;y<gridY;y=y+10)
        {

                UnitSquare(x,y);

        }
    }
}
void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)    // if second point is below first point interchange them
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)      // if denominator is zero we can't find slope
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;    // y2-y1=0 implies line is horizontal
            x=x1;
            for(i=y1;i<y2;i++)        // starting from x1,y1 add slope mx to x
            {                                  // and round it to find the next point on the
                                                // line. For that particular scan line i
                        if(x<le[i])         // insert the x value into either le or re.
                                    le[i]=x; // Initially both le and re will contain same
                                                // value...
                        if(x>re[i])         // in the next time for the other edge
                                    re[i]=x; // either le or re will change
                        x+=mx;            // NOTE: le and re are integer arrays and x
            }                                  // is float so automatic type conversion.
}
void drawpixel(int x,int y,float size)
{
            glPointSize(size);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float size)
{
            int le[6000],re[6000];
            int i,y;
            for(i=0;i<6000;i++)   // initialize le and re array values
            {
                        le[i]=6000;
                        re[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le,re);    // call edge detect four times
            edgedetect(x2,y2,x3,y3,le,re);    // once for each edge.
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x1,y1,le,re);
for(y=0;y<6000;y++)        // for every scan line with value y
{
           if(le[y]<=re[y])            // refer to le and re arrays to see if a part
                        for(i=le[y]+1;i<re[y];i++) // of the scanline is inside polygon
                                    drawpixel(i,y,size);       // if so draw a horizontal line from
}                                                              // left edge to right edge
}

void Rectangle(float x1,float y1,float x2,float y2)
{
   /*DrawLine(x1,y1,x1,y2,2);
   DrawLine(x1,y2,x2,y2,2);
   DrawLine(x2,y2,x2,y1,2);
   DrawLine(x2,y1,x1,y1,2);
   scanfill(x1,y1,x1,y2,x2,y1,x2,y2,1.5);*/
   glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void pavement(float x1,float y1,float x2,float y2)
{
    glColor3f(0.112, 0.112, 0.112);
    Rectangle(x1,y1,x2,y2);


}
void glRoad(float x1,float y1,float x2,float y2)
{
    glColor3f(0.112, 0.112, 0.112);
    Rectangle(x1,y1,x2,y2);
    float para=(x2-x1)/(y2-y1);
    para=fabs(para);
    if(para<1)
    {
        glColor3f(1.0,1.0,0.0);
        x1=x1+18.5;
        x2=x2-18.5;

        Rectangle(x1,y1,x1+1,y2);

        for(int i=y1+10;i<y2;i=i+13)
        {
            if((i/13)%2==0)
            {
                glColor3f(0.112, 0.112, 0.112);
                Rectangle(x1,i,x2,i+10);
            }
        }

    }
    else
    {
        /*glColor3f(1.0,1.0,0.0);
        y1=y1+18.5;
        y2=y2-18.5;

        Rectangle(x1+30,y1,x2,y1-0.5);   //Using Scanfill FPS drops hevily

        for(int i=x1;i<x2;i=i+13)
        {
            if((i/13)%2==0)
            {
                glColor3f(0.112, 0.112, 0.112);
                Rectangle(i,y1,i+10,y2);
            }
        }*/

        glColor3f(1.0,1.0,0.0);
        y1=y1+18.5;
        y2=y2-20.5;
        for(int i=x1;i<x2;i=i+13)
        {
            if((i/13)%2==0)
            {
                glColor3f(1.0,1.0,0.0);
                Rectangle(i,y1,i+10,y2);
            }
        }
    }
}
void DrawRoad()
{
    pavement(320,560,352,370);
    pavement(210,402,352,370);
    pavement(210,402,178,280);
    pavement(210,280,40,248);
    pavement(210,280,600,248);


    DrawGrid();
    glRoad(0,0,40,600);
    glRoad(0,560,600,600);
    DrawZebraCrossingV(0,420,40,470);
    DrawZebraCrossingH(250,560,300,600);
    glRoad(600,560,640,800);
    glRoad(600,0,640,5000);
    glRoad(850,0,890,5000);
    glColor3f(0.2, 0.67843137, 1.0);
    Rectangle(650,0,840,5000);

}
void DrawZebraCrossingV(float x1,float y1,float x2,float y2)
{
    glColor3f(0.112, 0.112, 0.112);
    Rectangle(x1,y1,x2,y2);
    for(int i=0;i<x2;i=i+10)
    {
        i=i+5;
        glColor3f(0.8,0.8,0.8);
        Rectangle(i,y1,i+4,y2);
    }

}

void DrawZebraCrossingH(float x1,float y1,float x2,float y2)
{
    glColor3f(0.112, 0.112, 0.112);
    Rectangle(x1,y1,x2,y2);
    for(int i=y1;i<y2;i=i+10)
    {
        i=i+5;
        glColor3f(0.8,0.8,0.8);
        Rectangle(x1,i,x2,i+4);
    }
}

void DrawCar()
{
    speed=10;
    if(Car)
    {
        if(Accelerate!=0)
        {
           for(int i=CarLength - 1;i>0;i--)
            {
                posX[i]=posX[i-1];
                posY[i]=posY[i-1];
                Accelerate=0;
                Car=false;
            }

        if(CarDirection==UP)
        {
            posY[0]=posY[0]+speed;
            Accelerate=0;
            Car=false;

        }
        else if(CarDirection==DOWN)
        {
            posY[0]=posY[0]-speed;
            Accelerate=0;
            Car=false;

        }
        else if(CarDirection==RIGHT)
        {
            posX[0]=posX[0]+speed;
            Accelerate=0;
            Car=false;


        }
        else if(CarDirection==LEFT)
        {
            posX[0]=posX[0]-speed;
            Accelerate=0;
            Car=false;

        }

        for(int i=0;i<CarLength;i++)
        {
            if(i==1)
            {
                glColor3f(0.8,0.0,0.0);
            }
            else
            {
                glColor3f(1.0,1.0,1.0);
            }
            Rectangle(posX[i],posY[i],posX[i]+12,posY[i]+12);
        }
    }
    }

    else
    {
        if(HIT==1)
        {
            glColor3f(1.0,0.0,0.0);
            Rectangle(posX[0],posY[0],posX[0]+12,posY[0]+12);
            Rectangle(posX[1],posY[1],posX[1]+12,posY[1]+12);
            Rectangle(posX[2],posY[2],posX[2]+12,posY[2]+12);
        }
        else
        {
            glColor3f(1,1,1);
            Rectangle(posX[0],posY[0],posX[0]+12,posY[0]+12);
            glColor3f(0.8,0.0,0.0);
            Rectangle(posX[1],posY[1],posX[1]+12,posY[1]+12);
            glColor3f(1,1,1);
            Rectangle(posX[2],posY[2],posX[2]+12,posY[2]+12);
        }

    }


}

void DrawRandomCar(int tag,bool check, int Direction,int Length,int positionX[],int positionY[],float width)
{

    if(check)
    {
        for(int i=Length - 1;i>0;i--)
        {
            positionX[i]=positionX[i-1];
            positionY[i]=positionY[i-1];
        }

        if(Direction==UP)
        {
            positionY[0]=positionY[0]+10;
        }
        else if(Direction==DOWN)
        {
            positionY[0]=positionY[0]-10;
        }
        else if(Direction==RIGHT)
        {
           positionX[0]=positionX[0]+10;
        }
        else if(Direction==LEFT)
        {
             positionX[0]=positionX[0]-10;
        }
        if(positionX[0]>600 && tag!=6)
        {
            glColor3f(1.0,0.0,0.0);
            positionX[0]=30;
        }
        else if(positionX[0]<0)
        {
            positionX[0]=600;
        }
        else if(positionY[0]<0 )
        {
            positionY[0]=600;
        }
        else if(positionY[0]<-10)
        {
            positionY[0]=800;
        }
        else if(positionY[0]>600 && tag!=6)
        {
            positionY[0]=-10;
        }
        else if(positionY[0]>800 && tag==6 )
        {
            positionY[0]=-10;
        }

        for(int i=0;i<Length;i++)
        {
            if(positionX[i]==posX[0] && positionY[i]>=posY[0] && positionY[i]<=posY[0]+10 )
            {
                HIT=1;
                Car=false;

                if(tag==1)
                {
                    R1check=false;
                }
                else if(tag==2)
                {
                    R2check=false;
                    R3check=false;

                }
                else if(tag==3)
                {
                    R3check=false;
                    R2check=false;
                }
                else if(tag==4)
                {
                    R4check=false;
                }
                else if(tag==5)
                {
                    R5check=false;
                }
            }

            if(positionY[0]==400 && tag==5 && Delay%300<150)
            {
                R5check=false;
            }
            if(positionY[0]==400 && tag==4 && Delay%300<150)
            {
                R4check=false;
            }
            if(positionX[0]==310 && tag==3 && Delay%300<150)
            {
                R3check=false;
            }
            if(positionX[0]==340 && tag==2 && Delay%300<150)
            {
                R2check=false;
            }
            if(positionX[0]==370 && tag==4 && Delay%300<150 && dir4==LEFT)
            {
                R4check=false;
            }
            if(positionX[0]==230 && tag==1 && Delay%300<150 && R3check==false)
            {
                R1check=false;
            }

        }

        if(positionY[0]==580 && tag==4 && Delay>1000 && dir4==UP)
        {
            dir4=LEFT;
            R5check=true;
        }

        for(int i=0;i<Length;i++)
        {
            Rectangle(positionX[i],positionY[i],positionX[i]+width,positionY[i]+width);
        }
    }
    else
    {
        for(int i=0;i<Length;i++)
        {
           if(HIT==1)
           {
              glColor3f(1.0,0.0,0.0);
           }
            Rectangle(positionX[i],positionY[i],positionX[i]+width,positionY[i]+width);
        }
    }
}

void RandomCar()
{
    glColor3f(0,1,1);
    DrawRandomCar(tag1,R1check,RIGHT,2,R1posX,R1posY,12);
    glColor3f(0.7,0.7,0.7);
    DrawRandomCar(tag2,R2check,LEFT,2,R2posX,R2posY,12);
    glColor3f(0.7,0,0);
    DrawRandomCar(tag3,R3check,LEFT,2,R3posX,R3posY,12);
    glColor3f(1.0,0.5,0.0);
    DrawRandomCar(tag4,R4check,dir4,2,R4posX,R4posY,15);
    glColor3f(0.5,0.5,0.0);
    DrawRandomCar(tag5,R5check,UP,2,R5posX,R5posY,15);
    glColor3f(0,0,1);
    DrawRandomCar(tag6,R6check,UP,3,R6posX,R6posY,15);
    if(Delay%300>150)
    {
        R4check=true;
        R3check=true;
        if(Delay>1000)
        {
            R5check=true;
        }

    }
    if(Delay%300>170)
    {
        R2check=true;
        R1check=true;

    }

}

void BackGround()
{
    glColor3f(0.6, 1.0, 1.0);
    glRectd(-8000,8000,600,600);
    glRectd(-8000,600,0,0);
    tree(390,610,10,0);
}

void Buildings(float x1,float y1,float x2,float y2)
{
    Rectangle(x1,y1,x2,y2);
    for(int i=x1;i<x2+1;i=i+10)
    {
        glColor3f(0.0,0.0,0.0);
        DrawLine(i,y1,i,y2-5,5);
    }
    for(int i=y1;i<y2+1;i=i+10)
    {
        glColor3f(0.0,0.0,0.0);
        DrawLine(x1,i,x2,i,5);
    }
}
void Mountains()
{
    tree(50,655,10,1);
    tree(490,660,10,1);
    glColor3f(0.3, 0.2, 0.0);
    DrawTriangle(530,600,575,650,600,600);
    glColor3f(0.6, 0.4, 0.0);
    DrawTriangle(520,603,530,600,575,650);

    glColor3f(0.3, 0.2, 0.0);
    DrawTriangle(490,600,515,640,530,600);
    glColor3f(0.6, 0.4, 0.0);
    DrawTriangle(475,603,490,600,515,640);

    glColor3f(0.3, 0.2, 0.0);
    DrawTriangle(390,600,435,640,470,600);
    glColor3f(0.6, 0.4, 0.0);
    DrawTriangle(435,640,470,600,490,600);

    glColor3f(0.3, 0.2, 0.0);
    DrawTriangle(30,600,75,670,120,600);
    glColor3f(0.6, 0.4, 0.0);
    DrawTriangle(20,603,30,600,75,670);

    glColor3f(0.3, 0.2, 0.0);
    DrawTriangle(7,600,15,680,30,600);
    glColor3f(0.6, 0.4, 0.0);
    DrawTriangle(4,600,15,603,15,680);
}

void tree(int x, int y,float radius,int branch)
{
    if(branch==1)
    {
        glColor3f(0.2, 0.1, 0.0);
        DrawLine(x,y-10,x,y-(2*radius)-30,13);

         for(int i=radius;i>0;i=i-2)
            {
                glColor3f(0.0, 0.6, 0.0);
                DrawCircle(x,y,i,5);
                DrawCircle(x-13,y+13,i,0);
                DrawCircle(x+13,y+13,i,0);
                DrawCircle(x-13,y-13,i,0);
                DrawCircle(x+13,y-13,i,0);
            }
    }

    else
    {
        for(int i=radius;i>0;i=i-2)
            {
                glColor3f(0.0, 0.6, 0.0);
                DrawCircle(x,y,i,2);
                DrawCircle(x-11,y+8,i,2);
                DrawCircle(x+11,y+8,i,2);
            }
    }

}
void EnvironMent1()
{
    Mountains();

    glColor3f(1.0, 0.92, 0.6);
    Buildings(130,600,150,680);

    glColor3f(1.0, 0.86, 0.3);
    Buildings(160,600,190,670);

    glColor3f(0.3, 0.47, 1.0);
    Buildings(180,600,230,630);

    glColor3f(0.6, 1.0, 0.2);
    Buildings(200,600,230,650);

    glColor3f(1.0, 0.2, 0.2);
    Buildings(320,600,360,640);

    glColor3f(0.83921569, 0.83921569, 0.76078431);
    Buildings(360,600,390,660);

    glColor3f(0.1,0.1,0.1);
    DrawLine(240,600,240,640,10);
    DrawLine(310,600,310,640,10);
    glColor3f(1.0, 1.0, 0.4);
    Rectangle(240,630,310,660);
    glColor3f(1.0,0.1,0.1);
    tree(140,615,10,1);

}

void Boat(int boat,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float x5,float y5)
{
    glBegin(GL_POLYGON);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);
        glVertex2f(x4,y4);
    glEnd();
    glColor3f(0.33333333, 1.0, 0.0);
    DrawTriangle(x2,y2,x5,y5,x2,y3);
    if(boat==1)
    {
         Y11=y1+5;
         Y12=y2+5;
         Y13=y3+5;
         Y14=y4+5;
         Y15=y5+5;
    }
    if(boat==2)
    {
         Y21=y1-3;
         Y22=y2-3;
         Y23=y3-3;
         Y24=y4-3;
         Y25=y5-3;
    }


}

void DrawBoat()
{

    glColor3f(0.0,0.0,0.0);
    if(Y11>750)
    {
       Y11=100,Y12=130,Y13=170,Y14=200,Y15=155;
    }
    Boat(boat1,730,Y11,700,Y12,700,Y13,730,Y14,760,Y15);

    glColor3f(1.0,0.0,0.0);
    if(Y21<0)
    {
       Y21=600,Y22=630,Y23=670,Y24=700,Y25=655;
    }
    Boat(boat2,800,Y21,770,Y22,770,Y23,800,Y24,830,Y25);

    glRoad(640,300,850,360);
}

void Helicopter(float angle,float x1,float y1,float x2,float y2)
{
    glColor3f(1.0,0.5,0.5);
    Rectangle(x1-30,y1+20,x2-50,y2+10);
    Rectangle(x1-30,y1+20,x2-30,y2-20);
    Rectangle(x1,y1,x2,y2);
    Rectangle(x1+15,y1+30,x2-10,y2+20);
    Rectangle(x1-10,y1+50,x2+15,y2+25);
    Hx11=x1+5;
    Hx12=x2+5;

    if(x1 > 900)
    {
        Hx11=50,Hy11=780,Hx12=80,Hy12=810;
    }

}

void DrawHeli()
{
    Helicopter(angle,Hx11,Hy11,Hx12,Hy12);
}






