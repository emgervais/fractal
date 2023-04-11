/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:05 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 19:50:15 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Please enter a valid fractal : Julia, Mandelbrot, Burningship.\n");
        return (ERROR);
    }
    int check;
	static t_fractal *jul;
    jul = malloc(sizeof(t_fractal));
    if(!jul)
    {
        printf("failed to allocate variable\n");
        return (ERROR);
    }
    paraminit(jul);
    check = create_fractal(jul, argc, argv);
    if(check == ERROR)
        return(ERROR);
    loop(jul);
	mlx_loop(jul->mlx);
	mlx_terminate(jul->mlx);
    free(jul);
	return (EXIT_SUCCESS);
}