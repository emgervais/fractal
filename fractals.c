/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:47 by egervais          #+#    #+#             */
/*   Updated: 2023/04/13 17:21:31 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

static void	coordinate(double x, double y, t_fractal *jul, double *fx, double *fy)
{
	if (x == 0)
		*fx = jul->cadreminx * jul->zoom + jul->arrow.x;
	else
		*fx = (jul->cadreminx * jul->zoom + jul->arrow.x) + x
			* (jul->cadremaxx * jul->zoom + jul->arrow.x - (jul->cadreminx
					* jul->zoom + jul->arrow.x)) / (WIDTH - 1);
	if (y == 0)
		*fy = jul->cadremaxy * jul->zoom + jul->arrow.y;
	else
		*fy = jul->cadreminy * jul->zoom + jul->arrow.y + y
			* (jul->cadremaxy * jul->zoom + jul->arrow.y - (jul->cadreminy
					* jul->zoom + jul->arrow.y)) / (HEIGHT - 1);
}

static void	draw_fractal(int x, int y, t_fractal *jul)
{
	int	it;
	double fx, fy;

	it = 0;
	coordinate(x, y, jul, &fx, &fy);
	if (jul->name == JULIA)
		it = julia(jul, fx, fy);
	else if (jul->name == MANDELBROT)
		it = mandelbrot(jul, fx, fy);
	else if (jul->name == BURNINGSHIP)
		it = burningship(jul, fx, fy);
	if (it == jul->it)
		mlx_put_pixel(jul->img, x, y, 0x000000FF);
	else if (it == jul->it - 1)
		mlx_put_pixel(jul->img, x, y, 0xFFFFFFFF);
	else
		mlx_put_pixel(jul->img, x, y, color(it, jul));
}

void	*fractal(void *data)
{
	t_thread *dat = data;
	int	x = dat->minx;
	int y = dat->miny;

	while (y < dat->maxy)
	{
		x = dat->minx;
		while (x < dat->maxx)
		{
			draw_fractal(x, y, dat->jul);
			x++;
		}
		y++;
	}
	return NULL;
}
