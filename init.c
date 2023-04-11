/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:46:26 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 19:54:07 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void paraminit(t_fractal *jul)
{
    jul->cadreminx = -2;
    jul->cadremaxx = 2;
    jul->cadreminy = -2;
    jul->cadremaxy = 2;
    jul->arrowx = 0;
    jul->arrowy = 0;
    jul->it = 31;
    jul->zoom = 1;
    jul->cx = -0.506667;
    jul->cy = 0.520000;
    jul->zz = 0;
    jul->color = 0;
}

void initjul(t_fractal *jul, char **name, int argc)
{
    if(argc < 3)
        return ;
    else if(name[2][0] == '1')
    {
        jul->cx = 0.403333;
        jul->cy = 0.273333;
    }
    else if(name[2][0] == '2')
    {
        jul->cx = 0.386667;
        jul->cy = 0.103333;
    }
    else if(name[2][0] == '3')
    {
        jul->cx = -0.203333;
        jul->cy = -0.696667;
    }
    else if(name[2][0] == '4')
    {
        jul->cx = 0.18;
        jul->cy = -0.566667;
    }
}

int		init_fractal(t_fractal *jul, char **name, int argc)
{
	if (!ft_strcmp(name[1], "Mandelbrot"))
		jul->name = MANDELBROT;
	else if (!ft_strcmp(name[1], "Burningship"))
		jul->name = BURNINGSHIP;
	else if (!ft_strcmp(name[1], "Julia"))
    {
		jul->name = JULIA;
        initjul(jul, name, argc);
    }
	else
		return (ERROR);
	return (1);
}

int init_mlx(t_fractal *jul)
{
	jul->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if(!jul->mlx)
    {
        free(jul);
        printf("Failed to initiate instance\n");
        return (ERROR);
    }
	jul->img = mlx_new_image(jul->mlx, WIDTH, HEIGHT);
    if(!jul->img)
    {
        free(jul);
        printf("Failed to create image\n");
        return(ERROR);
    }
    return(1);
}


int create_fractal(t_fractal *jul, int argc, char **argv)
{
    int check;
    check = init_fractal(jul, argv, argc);
    if(check == ERROR)
    {
        free(jul);
        printf("Please enter a valid fractal : Julia, Mandelbrot, Burningship.\n");
        return (ERROR);
    }
    check = init_mlx(jul);
    if(check == ERROR)
        return (ERROR);
    fractal(jul);
    check = mlx_image_to_window(jul->mlx, jul->img, 0, 0);
    if(check == ERROR)
    {
        free(jul);
        printf("Failed to display image\n");
        return (ERROR);
    }
    return (1);
}