/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:02 by egervais          #+#    #+#             */
/*   Updated: 2023/04/12 17:13:16 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	directionshook(void *param)
{
	t_fractal	*jul;

	jul = param;
	if (mlx_is_key_down(jul->mlx, MLX_KEY_D))
	{
		jul->arrow.x += (0.05 * jul->zoom);
		render(jul);
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_A))
	{
		jul->arrow.x -= (0.05 * jul->zoom);
		render(jul);
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_W))
	{
		jul->arrow.y -= (0.05 * jul->zoom);
		render(jul);
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_S))
	{
		jul->arrow.y += (0.05 * jul->zoom);
		render(jul);
	}
}

static void	ithook(void *param)
{
	t_fractal	*jul;

	jul = param;
	if (mlx_is_key_down(jul->mlx, MLX_KEY_M))
	{
		jul->it += 10;
		render(jul);
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_N))
	{
		if (jul->it >= 10)
		{
			jul->it -= 10;
			render(jul);
		}
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_O))
	{
		jul->zoom /= 1.1;
		render(jul);
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_P))
	{
		jul->zoom *= 1.1;
		render(jul);
	}
	if (mlx_is_key_down(jul->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(jul->mlx);
}

static void	zoomhook(mlx_key_data_t key, void *param)
{
	t_fractal	*jul;

	jul = param;
	if (key.key == MLX_KEY_C && key.action == MLX_PRESS)
	{
		jul->color++;
		if (jul->color > 2)
			jul->color = 0;
		render(jul);
	}
}

static void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*jul;

	jul = param;
	xdelta = 0;
	if (ydelta > 2)
	{
		jul->zoom *= 1.1;
		render(jul);
	}
	if (ydelta < -2)
	{
		jul->zoom /= 1.1;
		render(jul);
	}
}

void	loop(t_fractal *jul)
{
	mlx_close_hook(jul->mlx, &xhook, jul);
	mlx_key_hook(jul->mlx, &zoomhook, jul);
	mlx_scroll_hook(jul->mlx, &scrollhook, jul);
	mlx_loop_hook(jul->mlx, &directionshook, jul);
	mlx_loop_hook(jul->mlx, &ithook, jul);
}
