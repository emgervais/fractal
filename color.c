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

static int	get_rgba(t_fractal *jul)
{
	return (jul->rgba.r << 24 | jul->rgba.g << 16
		| jul->rgba.b << 8 | jul->rgba.a);
}

int	color(int i, t_fractal *jul)
{
	double	t;

	t = (double)i / (double)jul->it;
	if (jul->color == 0)
	{
		jul->rgba.r = (int)(9 * (1 - t) * t * t * t * 255);
		jul->rgba.g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		jul->rgba.b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		jul->rgba.a = 255;
	}
	if (jul->color == 1)
	{
		jul->rgba.r = (int)(8 * (1 - t) * t * t * t * 255);
		jul->rgba.g = (int)(7 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		jul->rgba.b = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		jul->rgba.a = 255;
	}
	if (jul->color == 2)
	{
		jul->rgba.r = (int)(9 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		jul->rgba.g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		jul->rgba.b = (int)(8 * (1 - t) * t * t * t * 255);
		jul->rgba.a = 255;
	}
	return (get_rgba(jul));
}
