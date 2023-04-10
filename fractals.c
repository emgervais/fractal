#include "fractol.h"

int burningship(int max_i, double x, double y, t_fractal *jul)
{
     int i = 0;
     double zx = 0, zy = 0;
     double b = 2 - (y / jul->it);
     double a = -2 + (x/ jul->it);
 while(i < max_i && zx * zx + zy * zy < 4)
 {
    double xtemp = zx * zx - zy * zy + x;
    double ytemp = fabs(2 * zx * zy) + y;
    zx = xtemp;
    zy = ytemp;
    i++;
 }
  if(i == max_i + 1)
         i--;
     jul->zx = zx;
     jul->zy = zy;
     return(i);
 }

int julia(int max_i, double x, double y, double cx, double cy, t_fractal *jul)
{
    int i = 0;
    double t = x;
    while(i <= max_i)
    {
        t=x;
        x=(x * x) - (y * y) + cx;
        y=(2*t*y) + cy;
        if((x * x)+(y * y) > 4)
            break;
       i++;
    }
    if(i == max_i + 1)
        i--;
    jul->zx = x;
    jul->zy = y;
    return(i);
}

int mandelbrot(t_fractal *jul)
 {
     int i = 0;
     double zx = 0, zy = 0;
     double tx, ty;
     double b = 2 - (jul->fy / jul->it);
     double a = -2 + (jul->fx / jul->it);
 while(i < jul->it && zx * zx + zy * zy < 4)
 {
     tx = zx * zx - zy * zy + jul->fx;
     ty = 2 * zx * zy + jul->fy;
     zx = tx;
     zy = ty;
     i++;
 }
  if(i == jul->it + 1)
         i--;
     jul->zx = zx;
     jul->zy = zy;
     return(i);
 }