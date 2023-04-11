/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:47 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 20:10:32 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_strcmp(const char *s1, const char *s2)
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

static void coordinate(double x, double y, t_fractal *jul)
{
    if(x == 0)
        jul->fx = jul->cadreminx * jul->zoom  + jul->arrowx;
    else
        jul->fx = (jul->cadreminx * jul->zoom + jul->arrowx) + x * (jul->cadremaxx * jul->zoom + jul->arrowx - (jul->cadreminx * jul->zoom  + jul->arrowx)) / (WIDTH - 1);
    if(y == 0)
        jul->fy = jul->cadremaxy * jul->zoom  + jul->arrowy;
    else
        jul->fy = jul->cadreminy * jul->zoom + jul->arrowy + y * (jul->cadremaxy * jul->zoom + jul->arrowy - (jul->cadreminy * jul->zoom + jul->arrowy)) / (HEIGHT - 1);
}

static void draw_fractal(int x, int y, t_fractal *jul)
{
    int it;

    it = 0;
    coordinate(x, y, jul);
    if(jul->name == JULIA)
        it = julia(jul->it, ((jul->fx)), ((jul->fy)), jul->cx, jul->cy, jul);
    else if(jul->name == MANDELBROT)
        it = mandelbrot(jul);
    else if(jul->name == BURNINGSHIP)
        it = burningship(jul->it, jul->fx, jul->fy, jul);
    if(it == jul->it)
        mlx_put_pixel(jul->img, x, y, 0x000000FF);
    else if(it == jul->it - 1)
        mlx_put_pixel(jul->img, x, y, 0xFFFFFFFF);
    else
        //i = it + 1 - log (log  (sqrt (jul->zx*jul->zx+jul->zy*jul->zy))) / log(2);
        mlx_put_pixel(jul->img, x, y, color(it, jul));
}

void fractal(t_fractal* jul)
{
    int x = 0;
    int y = 0;
    //double i;
    while(y <= HEIGHT)
    {
        x = 0;
        while(x <= WIDTH)
        {
            draw_fractal(x, y, jul);
            x++;
        }
        y++;
    }
}