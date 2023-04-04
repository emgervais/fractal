/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:21:40 by egervais          #+#    #+#             */
/*   Updated: 2023/04/03 19:59:12 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int julia(int max_i, double x, double y, double cx, double cy, t_fractal *jul)
{
    int i = 0;
    double t = x;
    while(i <= max_i)
    {
        t=x;
        x=(x * x) - (y * y) + cx;
        y=(2*t*y) + cy;
        if((x * x)+(y * y) > 4)
            break;
        i++;
    }
    jul->zx = x;
    jul->zy = y;
    return(i);
}

//modification cadre
void coordinate(double x, double y, t_fractal *jul)
{
    if(x == 0)
        jul->fx = jul->cadreminx * jul->zoom  + jul->arrowx;
    else
        jul->fx = (jul->cadreminx * jul->zoom + jul->arrowx) + x * (jul->cadremaxx * jul->zoom + jul->arrowx - (jul->cadreminx * jul->zoom  + jul->arrowx)) / (WIDTH - 1);
    if(y == 0)
        jul->fy = jul->cadremaxy * jul->zoom  + jul->arrowy;
    else
        jul->fy = jul->cadreminy * jul->zoom + jul->arrowy + y * (jul->cadremaxy * jul->zoom + jul->arrowy - (jul->cadreminy * jul->zoom + jul->arrowy)) / (HEIGHT - 1);
}

//void colored(int it, mlx_image_t *img, int x, int y, t_fractal *jul)
//{
//    int p = 0, l = 0;
//    int check = jul->it / jul->color;
//    unsigned int color[] = 
//    {
//    255, //black
//    0x00007FFF, //(dark blue)
//    0x0000FFFF, //(blue)
//    0x7F00FFFF, //(purple)
//    0xFF00FFFF, //(magenta)
//    0xFF007FFF, //(pink)
//    0xFF0000FF, //(red)
//    0xFF7F00FF, //(orange)
//    0xFFFF00FF, //(yellow)
//    0xFFFFFFFF, //(white)
//    };
    
//    if(it <= check)
//        mlx_put_pixel(img, x, y, color[0]);
//    else if(it % check == 0)
//        mlx_put_pixel(img, x, y, color[it / check - 1]);
//    else
//        mlx_put_pixel(img, x, y, color[it / check]);
//}
void fractal(t_fractal* jul, mlx_image_t *img, double ox, double oy)
{
    int p = (4294967295 - 255) / (jul->it * 1000000);
    double x = 0;
    double y = 0;
    double i;
    while(y <= HEIGHT)
    {
        x = 0;
        while(x <= WIDTH)
        {
            unsigned long int c = 255;
            coordinate(x, y, jul);
            i = julia(jul->it, ((jul->fx) + ox), ((jul->fy) + oy), jul->cx, jul->cy, jul);//ox and oy to cadre
            //if(x == 700 && y == 700)
            //    printf("x %f, y %f, max %f, min %f\n", jul->fx, jul->fy, jul->cadremaxx * jul->zoom, jul->cadreminx * jul->zoom);
            if(i == jul->it + 1)
                mlx_put_pixel(img, x, y, 0x000000FF);
            else
            {
                i = i + 1 - log (log  (sqrt (jul->zx*jul->zx+jul->zy*jul->zy))) / log(2);
                i *= 1000000;
                c += (p * i);
                mlx_put_pixel(img, x, y, c);
            }
            x++;
        }
        y++;
    }
}

mlx_image_t* menu(mlx_t* mlx, int check, mlx_image_t* bro)
{
    if(check == 0)
    {
        if(!bro)
        {
            mlx_texture_t* men = mlx_load_png("menu.png");
            bro = mlx_texture_to_image(mlx, men);
            mlx_image_to_window(mlx, bro, 0, 0);
        }
        bro->enabled = 1;
    }
    else
    {
        if(!bro)
            return(bro);
        else
            bro->enabled = 0;
    }
    return(bro);
}

void hook(void* param)
{
    t_fractal *jul = param;
    static mlx_image_t* bro;

	if (mlx_is_key_down(jul->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(jul->mlx);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_RIGHT))
    {
        jul->arrowx += (0.05 * jul->zoom);
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_LEFT))
    {
        jul->arrowx -= (0.05 * jul->zoom);
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_UP))
    {
        jul->arrowy -= (0.05 * jul->zoom);
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_DOWN))
    {
        jul->arrowy += (0.05 * jul->zoom);
        fractal(jul, jul->img, 0, 0);
    }
	if (mlx_is_key_down(jul->mlx, MLX_KEY_H))
        bro = menu(jul->mlx, 0, bro);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_Q))
        bro = menu(jul->mlx, 1, bro);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_ADD))
    {
        jul->it += 10;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_SUBTRACT))
    {
        if(jul->it >= 10)
        {
            jul->it -= 10;
            fractal(jul, jul->img, 0, 0);
        }
    }
    //if (mlx_is_key_down(jul->mlx, MLX_KEY_O))
    //{
    //    jul->zoom /= 0.1;
    //    fractal(jul, jul->img, 0, 0);
    //}
    //    if (mlx_is_key_down(jul->mlx, MLX_KEY_P))
    //{
    //    jul->zoom *= 0.1;
    //    fractal(jul, jul->img, 0, 0);
    //}
}

void scroll(double xdelta, double ydelta, void *param)
{
    t_fractal *jul = param;

	if (ydelta > 2)
    {
		jul->zoom *= 1.1;
        printf("%f, %f\n", jul->offsetx, jul->offsety);
        //fractal(jul, jul->img, jul->offsetx, jul->offsety);
        fractal(jul, jul->img, 0, 0);
    }
	if (ydelta < -2)
    {
        jul->zoom /= 1.1;
        printf("%f, %f\n", jul->offsetx, jul->offsety);
        //fractal(jul, jul->img, jul->offsetx, jul->offsety);
        fractal(jul, jul->img, 0, 0);
    }
}

void mouse(double x, double y, void *param)//makes it so when mouse is scrolling and holding
{
    t_fractal *jul = param;

    if(mlx_is_mouse_down(jul->mlx, MLX_MOUSE_BUTTON_LEFT))
    {
        if(jul->pos < x)
        {
            jul->pos = x;
            jul->cx += 0.005;
            fractal(jul, jul->img, 0, 0);
        }
        else
        {
            jul->pos = x;
            jul->cx -= 0.005;
            fractal(jul, jul->img, 0, 0);
        }
    }
    if(x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
    {
        jul->mousex = x;
        jul->mousey = y;
    }
}

void co(void *param)
{
    t_fractal *jul = param;
    
    if(jul->mousex == 0)
        jul->offsetx = jul->cadreminx * jul->zoom  + jul->arrowx;
    else
        jul->offsetx = (jul->cadreminx * jul->zoom + jul->arrowx) + jul->mousex * (jul->cadremaxx * jul->zoom + jul->arrowx - (jul->cadreminx * jul->zoom  + jul->arrowx)) / (WIDTH - 1);
    if(jul->mousey == 0)
        jul->offsety = jul->cadreminy * jul->zoom  + jul->arrowx;
    else
        jul->offsety = jul->fy = jul->cadreminy * jul->zoom + jul->arrowy + jul->mousey * (jul->cadremaxy * jul->zoom + jul->arrowy - (jul->cadreminy * jul->zoom + jul->arrowy)) / (HEIGHT - 1);
}

int32_t	main(void)
{
	static t_fractal *jul;
    jul = malloc(sizeof(t_fractal));
    jul->cadreminx = -1;
    jul->cadremaxx = 1;
    jul->cadreminy = -1;
    jul->cadremaxy = 1;
    jul->arrowx = 0;
    jul->arrowy = 0;
    jul->it = 30;  //specific of fractal.
    jul->zoom = 1;
    jul->color = 10;
    jul->cx =-0.79;
    jul->cy =0.15;
	if (!(jul->mlx = mlx_init(1400, 1400, "MLX42", true)))
		return(EXIT_FAILURE);
	jul->img = mlx_new_image(jul->mlx, WIDTH, HEIGHT);
    fractal(jul, jul->img, 0, 0);
    mlx_image_to_window(jul->mlx, jul->img, 0, 0);
	mlx_loop_hook(jul->mlx, &hook, jul);
    mlx_scroll_hook(jul->mlx, &scroll, jul);
    mlx_cursor_hook(jul->mlx, &mouse, jul);
    mlx_loop_hook(jul->mlx, &co, jul);
	mlx_loop(jul->mlx);
	mlx_terminate(jul->mlx);
	return (EXIT_SUCCESS);
}
