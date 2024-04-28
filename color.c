/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:21:40 by egervais          #+#    #+#             */
/*   Updated: 2023/04/12 17:13:28 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16
		| b << 8 | a);
}

int	color(int i, t_fractal *jul)
{
	double	t;

	t = (double)i / (double)jul->it;
	int r, g, b, a = 255;
	if (jul->color == 0)
	{
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	if (jul->color == 1)
	{
		r = (int)(8 * (1 - t) * t * t * t * 255);
		g = (int)(7 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		b = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	}
	if (jul->color == 2)
	{
		r = (int)(9 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8 * (1 - t) * t * t * t * 255);
	}
	return (get_rgba(r, g, b, a));
}
