/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fractals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:02:36 by egervais          #+#    #+#             */
/*   Updated: 2023/04/11 16:44:53 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	burningship(t_fractal *jul, double fx, double fy)
{
	int		i;
	double	tx;
	double	ty;

	i = 0;
	double zx = 0;
	double zy = 0;
	while (i < jul->it && zx * zx + zy * zy < 4)
	{
		tx = zx * zx - zy * zy + fx;
		ty = fabs(2 * zx * zy) + fy;
		zx = tx;
		zy = ty;
		i++;
	}
	if (i == jul->it + 1)
		i--;
	return (i);
}

int	julia(t_fractal *jul, double fx, double fy)
{
	int		i;
	double	t;

	i = 0;
	t = fx;
	while (i <= jul->it)
	{
		t = fx;
		fx = (fx * fx) - (fy * fy) + jul->c.x;
		fy = (2 * t * fy) + jul->c.y;
		if ((fx * fx) + (fy * fy) > 4)
			break ;
		i++;
	}
	if (i == jul->it + 1)
		i--;
	//jul->z.x = jul->f.x;
	//jul->z.y = jul->f.y;
	return (i);
}

int	mandelbrot(t_fractal *jul, double fx, double fy)
{
	int		i;
	double	tx;
	double	ty;

	double zx = 0;
	double zy = 0;
	i = 0;
	while (i < jul->it && zx * zx + zy * zy < 4)
	{
		tx = zx * zx - zy * zy + fx;
		ty = 2 * zx * zy + fy;
		zx = tx;
		zy = ty;
		i++;
	}
	if (i == jul->it + 1)
		i--;
	return (i);
}
