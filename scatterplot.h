#ifndef SCATTERPLOT_H
#define SCATTERPLOT_H

#include <graphics.h>
#include <cstdio>
#include "algorithms.h"

#define LEFT 100
#define RIGHT 900
#define TOP 80
#define BOTTOM 520
#define SCATTER_TICKS 6

inline void drawScatterPlot(int x[],int y[],int n)
{
    setbkcolor(WHITE);
    cleardevice();

    // Plot Title
    setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(400, 30, (char*)"SCATTER PLOT");
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

    int maxX=x[0],maxY=y[0];

    for(int i=1;i<n;i++)
    {
        if(x[i]>maxX) maxX=x[i];
        if(y[i]>maxY) maxY=y[i];
    }

    float xs=(RIGHT-LEFT)/(float)maxX;
    float ys=(BOTTOM-TOP)/(float)maxY;
    char buf[50];
    
    setcolor(BLACK);
    // X-axis labels
    for(int i=0;i<=SCATTER_TICKS;i++)
    {
        int val=(maxX*i)/SCATTER_TICKS;
        int px=LEFT+val*xs;

        line(px,BOTTOM+10,px,BOTTOM+15);
        sprintf(buf,"%d",val);
        outtextxy(px-10,BOTTOM+20,buf);
    }

    // Y-axis labels
    for(int i=0;i<=SCATTER_TICKS;i++)
    {
        int val=(maxY*i)/SCATTER_TICKS;
        int py=BOTTOM-val*ys;

        line(LEFT-15,py,LEFT-10,py);
        sprintf(buf,"%d",val);
        outtextxy(LEFT-50,py-5,buf);
    }

    for(int i=0;i<n;i++)
    {
        int px=LEFT+x[i]*xs;
        int py=BOTTOM-y[i]*ys;

        bresenhamCircleAnimated(px,py,6,BLUE,6);

        setcolor(BLACK);
        sprintf(buf,"(%d,%d)",x[i],y[i]);
        outtextxy(px+8,py-15,buf);

        delay(150);
    }
}

#endif