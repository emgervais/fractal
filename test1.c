/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:21:40 by egervais          #+#    #+#             */
/*   Updated: 2023/04/05 17:20:46 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

//void color(t_fractal *jul)
//{
//    int num_colors = 100;
//    int r;
//    int g;
//    int b;
//    int i = 0;
    
//    while(i < num_colors) 
//    {
//        r = i * 2;
//        g = (i * 4) % 256;
//        b = (i * 8) % 256;
//        jul->color[i] = get_rgba(r, g, b, 255);
//        i++;
//    }
//}

int color(int i, int max_i)
{
    int r, g, b, a;
    double t = (double)i / (double)max_i;
    
    r = (int)(9*(1-t)*t*t*t*255);
    g = (int)(15*(1-t)*(1-t)*t*t*255);
    b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
    a = 255;
    
    return (get_rgba(r, g, b, a));
}

void fractal(t_fractal* jul, mlx_image_t *img, double ox, double oy)
{
    double a = (double)255 / ((jul->it));
    double x = 0;
    double y = 0;
    double i;
    int it;
    int l;
    while(y <= HEIGHT)
    {
        x = 0;
        while(x <= WIDTH)
        {
            coordinate(x, y, jul);
            it = julia(jul->it, ((jul->fx) + ox), ((jul->fy) + oy), jul->cx, jul->cy, jul);//ox and oy to cadre
            if(it == jul->it)
                mlx_put_pixel(img, x, y, 0x000000FF);
            else if(it == jul->it - 1)
                mlx_put_pixel(img, x, y, 0xFFFFFFFF);
            else
            {
                i = it + 1 - log (log  (sqrt (jul->zx*jul->zx+jul->zy*jul->zy))) / log(2);
                //l = it * a;
                //printf("%f = %f\n", i, l);
                //mlx_put_pixel(img, x, y, jul->color[(it % 100)]);
                //mlx_put_pixel(img, x, y, get_rgba(0, 0, l, 255));
                mlx_put_pixel(img, x, y, color(i, jul->it));
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
    if (mlx_is_key_down(jul->mlx, MLX_KEY_O))
    {
        jul->zoom /= 1.1;
        //jul->arrowx += jul->offsetx;
        //jul->arrowy += jul->offsety;
        //fractal(jul, jul->img, jul->offsetx, jul->offsety);
        //double xdist = (jul->cadremaxx - jul->cadreminx) / (2.0 * jul->zoom);
        //double ydist = (jul->cadremaxy - jul->cadreminy) / (2.0 * jul->zoom);
        //jul->cadreminx = jul->offsetx - xdist;
        //jul->cadremaxx = jul->offsetx + xdist;
        //jul->cadreminy = jul->offsety - ydist;
        //jul->cadremaxy = jul->offsety + ydist;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_P))
    {
        jul->zoom *= 1.1;
        //jul->arrowx += jul->offsetx;
        //jul->arrowy += jul->offsety;
        //fractal(jul, jul->img, jul->offsetx, jul->offsety);
        //double xdist = (jul->cadremaxx - jul->cadreminx) / (2.0 * jul->zoom);
        //double ydist = (jul->cadremaxy - jul->cadreminy) / (2.0 * jul->zoom);
        //jul->zoomx = jul->offsetx + xdist;
        //jul->zoomy = jul->offsety + ydist;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_I))
    {
        printf("%f : %f : %f : %f\n", jul->cadreminx * jul->zoom + jul->arrowx, jul->cadremaxx * jul->zoom + jul->arrowx, jul->cadreminy * jul->zoom + jul->arrowy, jul->cadremaxy * jul->zoom + jul->arrowy);
    }
}

void scroll(double xdelta, double ydelta, void *param)
{
    t_fractal *jul = param;

	if (ydelta > 2)
    {
		jul->zoom *= 1.1;
        //jul->arrowx += jul->offsetx / 2;
        //jul->arrowy += jul->offsety / 2;
        //printf("%f, %f\n", jul->offsetx, jul->offsety);
        //fractal(jul, jul->img, jul->offsetx, jul->offsety);
        fractal(jul, jul->img, 0, 0);
    }
	if (ydelta < -2)
    {
        jul->zoom /= 1.1;
        //jul->arrowx += jul->offsetx / 2;
        //jul->arrowy += jul->offsety / 2;
        //printf("%f, %f\n", jul->offsetx, jul->offsety);
        //fractal(jul, jul->img, jul->offsetx, jul->offsety);
        fractal(jul, jul->img, 0, 0);
    }
}

void mouse(double x, double y, void *param)
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
        jul->offsetx = jul->cadreminx * jul->zoom + jul->arrowx;
    else
        jul->offsetx = (jul->cadreminx * jul->zoom + jul->arrowx) + jul->mousex * (jul->cadremaxx * jul->zoom + jul->arrowx - (jul->cadreminx * jul->zoom  + jul->arrowx)) / (WIDTH - 1);
    if(jul->mousey == 0)
        jul->offsety = jul->cadreminy * jul->zoom  + jul->arrowx;
    else
        jul->offsety = jul->cadreminy * jul->zoom + jul->arrowy + jul->mousey * (jul->cadremaxy * jul->zoom + jul->arrowy - (jul->cadreminy * jul->zoom + jul->arrowy)) / (HEIGHT - 1);
    //printf("%f : %f\n", jul->offsetx, jul->offsety);
}

int32_t	main(int argc, char **argv)
{
	static t_fractal *jul;
    jul = malloc(sizeof(t_fractal));
    jul->color = malloc(sizeof(int) * 101);
    
    jul->cadreminx = -2;
    jul->cadremaxx = 2;
    jul->cadreminy = -2;
    jul->cadremaxy = 2;
    jul->arrowx = 0;
    jul->arrowy = 0;
    jul->it = 31;
    jul->zoom = 1;
    jul->cx =-0.79;
    jul->cy =0.15;
    //color(jul);
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
