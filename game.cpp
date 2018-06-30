#include<GL/gl.h>
#include<GL/glut.h>
#include "game.h"
#include <ctime>
#include<iostream>

int prev_num=-1;
int gridX;
int gridY;
extern bool gameOver;
extern int score;

bool change=true;

int flag=0;
int posX=12,posY=30;

int posBarX[NOB]={55,70,85,100,115,130,145,160,175,190};
int posBarY[NOB]={24,-1,-1,-1,-1,-1,-1,-1,-1,-1};

void initGrid(int x,int y)
{
    gridX=x;
    gridY=y;
}

/*
void unit(int,int);
void drawGrid()
{
    for(int x=0;x<gridX;x++)
        for(int y=0;y<gridY;y++)
            unit(x,y);
}
*/

/*
void unit(int x,int y)
{
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1)
    {
        glLineWidth(2.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }

    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}
*/

void drawBall()
{
    glColor3f(0.0,1.0,0.0);
    glRectf(posX,posY,posX+1,posY+1);
    if(posY==0 || posY==gridX-1)
    {
        gameOver=true;
    }
    if(posX==posBarX[0] && (posY<=posBarY[0] || posY>=posBarY[0]+12))
    {
        gameOver=true;
    }
    else if(posX==posBarX[0])
    {
        score++;
    }
}

void drawBars()
{
    srand(time(NULL));
    if(flag==0)
    {
        for(int i=1;i<NOB;i++)
        {
            int num;
            random(num);
            posBarY[i]=num;
        }
        change=false;
        flag=1;
    }
    glColor3f(1.0,0.0,0.0);
    for(int i=0;i<NOB;i++)
    {
        for(int j=0;j<posBarY[i];j++)
        {
            glRectd(posBarX[i],j,posBarX[i]+1,j+1);
        }
        for(int j=posBarY[i]+12;j<gridY;j++)
        {
            glRectd(posBarX[i],j,posBarX[i]+1,j+1);
        }
    }
    for(int i=0;i<NOB;i++)
    {
        posBarX[i]--;
    }
    if(posBarX[0]==0)
    {
        for(int i=0;i<NOB-1;i++)
        {
            posBarX[i]=posBarX[i+1];
            posBarY[i]=posBarY[i+1];
        }
        posBarX[NOB-1]=posBarX[NOB-2]+15;
        change=true;
    }
    if(change==true)
    {
        int num;
        random(num);
        if(num>10)
            posBarY[NOB-1]=num;
        else
            posBarY[NOB-1]=num+12;
        change=false;
    }
}

void random(int &num)
{
    int _max=gridY-12;
    int _min=1;
    num=_min + rand()%(_max - _min);
    std::cout<<num<<std::endl;
    if(num==prev_num+3)
    {
        if(num>6)
        {
            num+=6;
        }
        else
        {
            num-=5;
        }
    }
    else if(num==prev_num+4)
    {
        if(num>8)
        {
            num+=8;
        }
        else
        {
            num-=7;
        }
    }
    prev_num=num;
}
