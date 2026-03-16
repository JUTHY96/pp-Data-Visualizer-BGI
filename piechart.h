#ifndef PIECHART_H
#define PIECHART_H

#include <graphics.h>
#include <cmath>
#include <cstdio>
#include "algorithms.h"

inline void drawPieChart3D(int data[],int n)
{
    setbkcolor(WHITE);
    cleardevice();

    // Plot Title
    setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(400, 30, (char*)"3D PIE CHART");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    int cx=500,cy=280,r=150,depth=25;
    int colors[10]={RED,GREEN,BLUE,YELLOW,CYAN,MAGENTA,LIGHTRED,LIGHTBLUE,LIGHTGREEN,BROWN};
    int total=0;

    for(int i=0;i<n;i++)
        total+=data[i];

    int start=0;
    char buf[50];

    for(int i=0;i<n;i++)
    {
        int angle=(data[i]*360)/total;

        for(int d=depth;d>=0;d--)
        {
            setfillstyle(SOLID_FILL,colors[i%10]);
            pieslice(cx,cy+d,start,start+angle,r);
            delay(2);
        }

        int mid=start+angle/2;
        float rad=mid*3.1416/180;

        int edge_x=cx+cos(rad)*r;
        int edge_y=cy+sin(rad)*r;

        int lx=cx+cos(rad)*(r+40);
        int ly=cy+sin(rad)*(r+40);

        bresenhamLineAnimated(edge_x, edge_y, lx, ly, BLACK, 1);

        int percent=(data[i]*100)/total;

        setcolor(BLACK);
        sprintf(buf,"%d (%d%%)",data[i],percent);

        // Adjust text to be centered
        int text_x = lx + (cos(rad) > 0 ? 5 : -textwidth(buf) - 5);
        int text_y = ly - 5;
        
        outtextxy(text_x, text_y, buf);

        start+=angle;
        delay(200);
    }
}

#endif