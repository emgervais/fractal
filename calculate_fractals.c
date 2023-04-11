/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fractals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:02:36 by egervais          #+#    #+#             */
/*   Updated: 2023/04/10 21:32:23 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int burningship(t_fractal *jul)
{
    int i;
    double tx;
    double ty;

    i = 0;
    jul->z.x = 0;
    jul->z.y = 0;
    while(i < jul->it && jul->z.x * jul->z.x + jul->z.y * jul->z.y < 4)
    {
        tx = jul->z.x * jul->z.x - jul->z.y * jul->z.y + jul->f.x;
        ty = fabs(2 * jul->z.x * jul->z.y) + jul->f.y;
        jul->z.x = tx;
        jul->z.y = ty;
        i++;
    }
    if(i == jul->it + 1)
        i--;
    return(i);
 }

int julia(t_fractal *jul)
{
    int i = 0;
    double t = jul->f.x;
    while(i <= jul->it)
    {
        t=jul->f.x;
        jul->f.x=(jul->f.x * jul->f.x) - (jul->f.y * jul->f.y) + jul->c.x;
        jul->f.y=(2*t*jul->f.y) + jul->c.y;
        if((jul->f.x * jul->f.x)+(jul->f.y * jul->f.y) > 4)
            break;
       i++;
    }
    if(i == jul->it + 1)
        i--;
    jul->z.x = jul->f.x;
    jul->z.y = jul->f.y;
    return(i);
}

int mandelbrot(t_fractal *jul)
{
    int i;
    double tx;
    double ty;
   
    jul->z.x = 0;
    jul->z.y = 0;
    i = 0;
    while(i < jul->it && jul->z.x * jul->z.x + jul->z.y * jul->z.y < 4)
    {
        tx = jul->z.x * jul->z.x - jul->z.y * jul->z.y + jul->f.x;
        ty = 2 * jul->z.x * jul->z.y + jul->f.y;
        jul->z.x = tx;
        jul->z.y = ty;
        i++;
    }
    if(i == jul->it + 1)
        i--;
    return(i);
}