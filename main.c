/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:05 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 20:26:41 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	int			check;
	t_fractal	*jul;

	if (argc < 2)
	{
		printf("Please enter a valid fractal : Julia,\
 Mandelbrot, Burningship.\n");
		return (ERROR);
	}
	jul = malloc(sizeof(t_fractal));
	if (!jul)
	{
		printf("failed to allocate variable\n");
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
	return (EXIT_SUCCESS);
}
