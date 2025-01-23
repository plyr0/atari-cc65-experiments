#include <atari.h>
#include <stdlib.h>

int xes[40];
int yes[40];
int i;

void plotLine(int x0, int y0, int x1, int y1);
void setpixel(int x, int y);

int main (void)
{
    srand(POKEY_READ.random);
    for(i=0; i<40; ++i){
        xes[i] = abs(rand() % 40);
        yes[i] = abs(rand() % 24);
    }

    for(i=0; i<40; i+=2){
        plotLine(xes[i], yes[i], xes[i+1], yes[i+1]);
    }

    OS.ch = 255;
    while(OS.ch == 255)
        asm volatile("");
    return 0;
}

void setpixel(int x, int y){
    OS.savmsc[y * 40 + x] = 84;
}

/* https://zingl.github.io/bresenham.html */
void plotLine(int x0, int y0, int x1, int y1)
{
   int dx = abs(x1-x0);
   int sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0);
   int sy = y0<y1 ? 1 : -1; 
   int err = dx+dy;
   int e2;
 
   for(;;){
      setpixel(x0,y0);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; }
      if (e2 <= dx) { err += dx; y0 += sy; }
   }
}