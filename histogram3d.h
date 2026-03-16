#ifndef HISTOGRAM3D_H
#define HISTOGRAM3D_H
#define HIST_TICKS 5

#include <graphics.h>
#include <cstdio>

#define LEFT 100
#define RIGHT 900
#define TOP 80
#define BOTTOM 520

inline void drawHistogram3D(int data[],int n)
{
    setbkcolor(WHITE);
    cleardevice();

    // Plot Title
    setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(400, 30, (char*)"3D HISTOGRAM");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    for(int x=LEFT;x<=RIGHT;x+=80)
        line(x,TOP,x,BOTTOM);

    for(int y=TOP;y<=BOTTOM;y+=80)
        line(LEFT,y,RIGHT,y);

    // Draw axes
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(LEFT-10,BOTTOM+10,RIGHT+10,BOTTOM+10); // X-axis
    line(LEFT-10,BOTTOM+10,LEFT-10,TOP-10);     // Y-axis
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    int max=data[0];

    for(int i=1;i<n;i++)
        if(data[i]>max)
            max=data[i];

    float barWidth=(RIGHT-LEFT)/(float)n;
    float scale=(BOTTOM-TOP)/(float)max;

    char buf[20];

    setcolor(BLACK);
    for(int i=0;i<=HIST_TICKS;i++)
    {
        int val=(max*i)/HIST_TICKS;
        int py=BOTTOM-val*scale;

        line(LEFT-15,py,LEFT-10,py);

        sprintf(buf,"%d",val);
        outtextxy(LEFT-50,py-5,buf);
    }

    for(int i=0;i<n;i++)
    {
        int left=LEFT+i*barWidth+10;
        int right=LEFT+(i+1)*barWidth-10;

        int h=data[i]*scale;

        for(int j=0;j<=h;j+=4)
        {
            setfillstyle(SOLID_FILL,BLUE);
            bar3d(left,BOTTOM-j,right,BOTTOM,15,1);
            delay(5);
        }

        setcolor(BLACK);
        sprintf(buf,"%d",data[i]);
        outtextxy((left+right)/2-10,BOTTOM-h-20,buf);

        sprintf(buf,"V%d",i+1);
        outtextxy((left+right)/2-5,BOTTOM+15,buf);
    }
}

#endif