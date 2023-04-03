/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:18:13 by egervais          #+#    #+#             */
/*   Updated: 2023/03/30 17:40:12 by egervais         ###   ########.fr       */
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
	double		fx;
	double		fy;
	double		zoom;
	double		x;
	double		y;
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
	double		width;
	double		height;
	int check;
}				t_fractal;


void fractal(t_fractal* jul, mlx_image_t *img, double ox, double oy);
//void fractal(t_fractal* jul);

#endif