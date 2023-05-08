/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:05 by egervais          #+#    #+#             */
/*   Updated: 2023/04/12 17:55:18 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	xhook(void *param)
{
	t_fractal	*jul;

	jul = param;
	mlx_close_window(jul->mlx);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, &*str, 1);
		str++;
	}
}

int	main(int argc, char **argv)
{
	int			check;
	t_fractal	*jul;

	if (argc < 2)
	{
		ft_putstr("Please enter a valid fractal : Julia,\
 Mandelbrot, Burningship.\n");
		return (ERROR);
	}
	jul = malloc(sizeof(*jul));
	if (!jul)
	{
		ft_putstr("failed to allocate variable\n");
		return (ERROR);
	}
	paraminit(jul);
	check = create_fractal(jul, argc, argv);
	if (check == ERROR)
		return (ERROR);
	loop(jul);
	mlx_loop(jul->mlx);
	mlx_terminate(jul->mlx);
	free(jul);
	ft_putstr("closed with sucess\n");
	return (EXIT_SUCCESS);
}
