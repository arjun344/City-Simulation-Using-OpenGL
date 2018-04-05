#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

void initGrid(int,int);
void DrawGrid();
void UnitSquare(int,int);
void print(int, int,char);
float round_value(float);
void DrawLine(float,float,float,float,float);
void DrawTriangle(float,float,float,float,float,float);
void plot(float , float ,float ,float, float );
void DrawCircle(float ,float,float, float);
void edgedetect(float ,float ,float ,float ,int*,int*);
void drawpixel(int ,int ,float );
void scanfill(float,float ,float ,float ,float ,float,float ,float ,float );
void Rectangle(float,float,float,float);
void pavement(float ,float ,float ,float );
void DrawRoad();
void glRoad(float,float,float,float);
void DrawZebraCrossingV(float,float,float,float);
void DrawZebraCrossingH(float,float,float,float);
void DrawCar();
void RandomCar();
void DrawRandomCar(int,bool,int,int,int[],int[],float);
void BackGround();
void Buildings(float,float,float,float);
void Mountains();
void tree(int,int,float,int);
void EnvironMent1();
void Boat(int, float ,float ,float ,float ,float ,float ,float ,float ,float ,float ,float);
void DrawBoat();
void Helicopter(float,float,float,float,float);
void DrawHeli();




#endif // GAME_H_INCLUDED
