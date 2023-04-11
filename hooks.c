/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:02 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 20:09:38 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void directionshook(void *param)
{
    t_fractal *jul;
    jul = param;

    if (mlx_is_key_down(jul->mlx, MLX_KEY_RIGHT))
    {
        jul->arrowx += (0.05 * jul->zoom);
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_LEFT))
    {
        jul->arrowx -= (0.05 * jul->zoom);
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_UP))
    {
        jul->arrowy -= (0.05 * jul->zoom);
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_DOWN))
    {
        jul->arrowy += (0.05 * jul->zoom);
        fractal(jul);
    }
}

static void ithook(void* param)
{
    t_fractal *jul;
    jul = param;

    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_ADD))
    {
        jul->it += 10;
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_SUBTRACT))
    {
        if(jul->it >= 10)
        {
            jul->it -= 10;
            fractal(jul);
        }
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(jul->mlx);
}
static void zoomhook(void* param)
{
    t_fractal *jul;
    jul = param;

    if (mlx_is_key_down(jul->mlx, MLX_KEY_C))
    {
        jul->color++;
        if(jul->color > 2)
            jul->color = 0;
        fractal(jul); 
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_O))
    {
        jul->zoom /= 1.1;
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_P))
    {
        jul->zoom *= 1.1;
        fractal(jul);
    }
}

static void scrollhook(double xdelta, double ydelta, void *param)
{
    t_fractal *jul;
    jul = param;

    xdelta = 0;
	if (ydelta > 2)
    {
		jul->zoom *= 1.1;
        fractal(jul);
    }
	if (ydelta < -2)
    {
        jul->zoom /= 1.1;
        fractal(jul);
    }
}

void loop(t_fractal *jul)
{
	mlx_loop_hook(jul->mlx, &zoomhook, jul);
    mlx_scroll_hook(jul->mlx, &scrollhook, jul);
    //mlx_cursor_hook(jul->mlx, &mouse, jul);
    mlx_loop_hook(jul->mlx, &directionshook, jul);
    mlx_loop_hook(jul->mlx, &ithook, jul);
}