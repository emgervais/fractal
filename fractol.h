/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:18:13 by egervais          #+#    #+#             */
/*   Updated: 2023/04/05 16:12:01 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "MLX42.h"

#define HEIGHT 1400
#define WIDTH 1400

typedef struct s_complex {
    
    double x;
    double y;
	double it;
}               t_complex;

typedef struct s_fractal {
	char		*name;
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
	int			*color;
	int		mousex;
	int		mousey;
	double		offsetx;
	double		offsety;
	double		cx;
	double		cy;
	int			pos;
	double		zx;
	double		zy;
	double		ox;
	double		oy;
	double		arrowy;
	double		arrowx;
	double		zoomx;
	double		zoomy;
	int 		check;
}				t_fractal;


void fractal(t_fractal* jul, mlx_image_t *img, double ox, double oy);
int julia(int max_i, double x, double y, double cx, double cy, t_fractal *jul);
void coordinate(double x, double y, t_fractal *jul);
mlx_image_t* menu(mlx_t* mlx, int check, mlx_image_t* bro);
void hook(void* param);
void scroll(double xdelta, double ydelta, void *param);
void mouse(double x, double y, void *param);
void co(void *param);

#endif