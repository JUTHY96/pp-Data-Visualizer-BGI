#ifndef AREAGRAPH_H
#define AREAGRAPH_H

#include <graphics.h>
#include <cstdio>
#include "algorithms.h"

#define LEFT 100
#define RIGHT 900
#define TOP 80
#define BOTTOM 520
#define AREA_TICKS 6

inline void drawAreaGraph(int data[],int n)
{
    setbkcolor(WHITE);
    cleardevice();

    // Plot Title
    setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(400, 30, (char*)"AREA GRAPH");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    // Draw grid
    for(int gx=LEFT;gx<=RIGHT;gx+=80)
        line(gx,TOP,gx,BOTTOM);

    for(int gy=TOP;gy<=BOTTOM;gy+=80)
        line(LEFT,gy,RIGHT,gy);

    // Draw axes
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(LEFT-10,BOTTOM+10,RIGHT+10,BOTTOM+10); // X-axis
    line(LEFT-10,BOTTOM+10,LEFT-10,TOP-10);     // Y-axis
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    int max=data[0];
    for(int i=1;i<n;i++)
        if(data[i]>max) max=data[i];

    float xs=(RIGHT-LEFT)/(float)(n-1);
    float ys=(BOTTOM-TOP)/(float)max;
    char buf[50];
    
    setcolor(BLACK);
    // Y-axis labels
    for(int i=0;i<=AREA_TICKS;i++)
    {
        int val=(max*i)/AREA_TICKS;
        int py=BOTTOM-val*ys;

        line(LEFT-15,py,LEFT-10,py);
        sprintf(buf,"%d",val);
        outtextxy(LEFT-50,py-5,buf);
    }
    
    // Draw Area filling from left to right animated
    for(int i=0;i<n-1;i++)
    {
        int x1=LEFT+i*xs;
        int y1=BOTTOM-data[i]*ys;
        int x2=LEFT+(i+1)*xs;
        int y2=BOTTOM-data[i+1]*ys;

        setcolor(CYAN);
        for (int x = x1; x <= x2; x++) {
            float t = (float)(x - x1) / (x2 - x1);
            int y = y1 + t * (y2 - y1);
            line(x, BOTTOM, x, y);
            delay(2);
        }
        
        bresenhamLineAnimated(x1, y1, x2, y2, BLUE, 1);
        bresenhamCircleAnimated(x1, y1, 5, RED, 2);
    }
    bresenhamCircleAnimated(LEFT+(n-1)*xs, BOTTOM-data[n-1]*ys, 5, RED, 2);
}

#endif