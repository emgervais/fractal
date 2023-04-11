/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:18:13 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 20:02:35 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "./MLX42/include/MLX42/MLX42.h"

#define HEIGHT 1400
#define WIDTH 1400
#define ERROR -1

enum	e_fractal{MANDELBROT, JULIA, BURNINGSHIP};

typedef struct s_complex {
    
    double x;
    double y;
	double it;
}               t_complex;

typedef struct s_fractal {
	enum e_fractal	name;
	mlx_image_t	*img;
	mlx_image_t* men;
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
	//int		mousex;
	//int		mousey;
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
void loop(t_fractal *jul);
void menu(mlx_t* mlx, int check, mlx_image_t* bro);
void paraminit(t_fractal *jul);
void initjul(t_fractal *jul, char **name, int argc);
int	init_fractal(t_fractal *jul, char **name, int argc);
int init_mlx(t_fractal *jul);
int create_fractal(t_fractal *jul, int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
void fractal(t_fractal* jul);
int color(int i, t_fractal *jul);

#endif