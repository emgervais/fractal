/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:02:36 by egervais          #+#    #+#             */
/*   Updated: 2023/04/05 17:24:13 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//int julia(int max_i, double x, double y, double cx, double cy, t_fractal *jul)
//{
//    int i = 0;
//    double t = x;
//    while(i <= max_i)
//    {
//        t=x;
//        x=(x * x) - (y * y) + cx;
//        y=(2*t*y) + cy;
//        if((x * x)+(y * y) > 4)
//            break;
//        i++;
//    }
//    if(i == max_i + 1)
//        i--;
//    jul->zx = x;
//    jul->zy = y;
//    return(i);
//}

int julia(int max_i, double x, double y, double cx, double cy, t_fractal *jul)
{
    int i = 0;
    double zx = 0, zy = 0;
    double tx, ty;
    double b = 2 - (y / jul->it);
    double a = -2 + (x/ jul->it);
while(i < max_i && zx * zx + zy * zy < 4)
{
    tx = zx * zx - zy * zy + x;
    ty = 2 * zx * zy + y;
    zx = tx;
    zy = ty;
    i++;
}
    if(i == max_i + 1)
        i--;
    jul->zx = zx;
    jul->zy = zy;
    return(i);
}