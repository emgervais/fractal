#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "MLX42.h"

#define HEIGHT 800
#define WIDTH 800

enum	e_fractal{MANDELBROT, JULIA, BURNINGSHIP};

typedef struct s_complex {
    
    double x;
    double y;
	double it;
}               t_complex;

typedef struct s_fractal {
	enum e_fractal	name;
	mlx_image_t	*img;
	mlx_t		*mlx;
	double		cadreminx;
	double		cadremaxx;
	double		cadreminy;
	double		cadremaxy;
	double		fx;
	double		fy;
	double		zoom;
	int			it;
	int			color;
	int		mousex;
	int		mousey;
	double		offsetx;
	double		offsety;
	double		cx;
	double		cy;
	int			pos;
	double		zx;
	double		zy;
	double		zz;
	double		ox;
	double		oy;
	double		arrowy;
	double		arrowx;
	double		l;
	int check;
}				t_fractal;


void fractal(t_fractal* jul);
int burningship(int max_i, double x, double y, t_fractal *jul);
int julia(int max_i, double x, double y, double cx, double cy, t_fractal *jul);
int mandelbrot(t_fractal *jul);
//void fractal(t_fractal* jul);

#endif