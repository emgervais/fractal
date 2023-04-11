/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:21:40 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 22:06:59 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_rgba(t_fractal *jul)
{
	return (jul->rgba.r << 24 | jul->rgba.g << 16 | jul->rgba.b << 8 | jul->rgba.a);
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

//void mouse(double x, double y, void *param)
//{
//    t_fractal *jul;
//    jul = param;

//    if(mlx_is_mouse_down(jul->mlx, MLX_MOUSE_BUTTON_LEFT))
//    {
//        if(jul->pos < x)
//        {
//            jul->pos = x;
//            jul->cx += 0.005;
//            fractal(jul);
//        }
//        else
//        {
//            jul->pos = x;
//            jul->cx -= 0.005;
//            fractal(jul);
//        }
//    }
//    //if(x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
//    //{
//    //    jul->mousex = x;
//    //    jul->mousey = y;
//    //}
//}

//void co(void *param)
//{
//    t_fractal *jul = param;

//    if(jul->mousex == 0)
//        jul->offsetx = jul->cadreminx * jul->zoom + jul->arrowx;
//    else
//        jul->offsetx = (jul->cadreminx * jul->zoom + jul->arrowx)
	//+ jul->mousex * (jul->cadremaxx * jul->zoom + jul->arrowx - (jul->cadreminx
	//		* jul->zoom  + jul->arrowx)) / (WIDTH - 1);
//    if(jul->mousey == 0)
//        jul->offsety = jul->cadreminy * jul->zoom  + jul->arrowx;
//    else
//        jul->offsety = jul->cadreminy * jul->zoom + jul->arrowy + jul->mousey
	//* (jul->cadremaxy * jul->zoom + jul->arrowy - (jul->cadreminy * jul->zoom
	//		+ jul->arrowy)) / (HEIGHT - 1);
//}
