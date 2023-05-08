/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:46:26 by egervais          #+#    #+#             */
/*   Updated: 2023/04/18 13:37:47 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	paraminit(t_fractal *jul)
{
	jul->cadreminx = -2;
	jul->cadremaxx = 2;
	jul->cadreminy = -2;
	jul->cadremaxy = 2;
	jul->arrow.x = 0;
	jul->arrow.y = 0;
	jul->it = 151;
	jul->zoom = 1;
	jul->c.x = -0.506667;
	jul->c.y = 0.520000;
	jul->color = 0;
}

void	initjul(t_fractal *jul, char **name, int argc)
{
	if (argc < 3)
		return ;
	else if (name[2][0] == '1')
	{
		jul->c.x = 0.403333;
		jul->c.y = 0.273333;
	}
	else if (name[2][0] == '2')
	{
		jul->c.x = -0.8696;
		jul->c.y = 0.26;
	}
	else if (name[2][0] == '3')
	{
		jul->c.x = -0.203333;
		jul->c.y = -0.696667;
	}
	else if (name[2][0] == '4')
	{
		jul->c.x = 0.18;
		jul->c.y = -0.566667;
	}
}

int	init_fractal(t_fractal *jul, char **name, int argc)
{
	int	i;

	i = 0;
	if (!ft_strcmp(name[1], "Mandelbrot"))
		jul->name = MANDELBROT;
	else if (!ft_strcmp(name[1], "Burningship"))
		jul->name = BURNINGSHIP;
	else if (!ft_strcmp(name[1], "Julia"))
	{
		jul->name = JULIA;
		if (name[2])
			i = ft_strlen(name[2]);
		if (i < 2)
			initjul(jul, name, argc);
	}
	else
		return (ERROR);
	return (1);
}

int	init_mlx(t_fractal *jul)
{
	jul->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!jul->mlx)
	{
		free(jul);
		ft_putstr("Failed to initiate instance\n");
		return (ERROR);
	}
	mlx_set_window_title(jul->mlx, "Fractol");
	jul->img = mlx_new_image(jul->mlx, WIDTH, HEIGHT);
	if (!jul->img)
	{
		free(jul);
		ft_putstr("Failed to create image\n");
		return (ERROR);
	}
	return (1);
}

int	create_fractal(t_fractal *jul, int argc, char **argv)
{
	int	check;

	check = init_fractal(jul, argv, argc);
	if (check == ERROR)
	{
		free(jul);
		ft_putstr("Please enter a valid fractal : Julia, \
Mandelbrot, Burningship.\n");
		return (ERROR);
	}
	check = init_mlx(jul);
	if (check == ERROR)
		return (ERROR);
	fractal(jul);
	check = mlx_image_to_window(jul->mlx, jul->img, 0, 0);
	if (check == ERROR)
	{
		free(jul);
		ft_putstr("Failed to display image\n");
		return (ERROR);
	}
	return (1);
}
