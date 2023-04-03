/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:21:40 by egervais          #+#    #+#             */
/*   Updated: 2023/03/30 18:11:14 by egervais         ###   ########.fr       */
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
        jul->fx = -1;
    else
        jul->fx = (x - WIDTH / 2.0) / HEIGHT * 2;
    if(y == 0)
        jul->fy = 1;
    else
        jul->fy = (y - HEIGHT / 2.0) / WIDTH * -2;
}

void colored(int it, mlx_image_t *img, int x, int y, t_fractal *jul)
{
    int p = 0, l = 0;
    int check = jul->it / jul->color;
    unsigned int color[] = 
    {
    255, //black
    0x00007FFF, //(dark blue)
    0x0000FFFF, //(blue)
    0x7F00FFFF, //(purple)
    0xFF00FFFF, //(magenta)
    0xFF007FFF, //(pink)
    0xFF0000FF, //(red)
    0xFF7F00FF, //(orange)
    0xFFFF00FF, //(yellow)
    0xFFFFFFFF, //(white)
    };
    
    if(it <= check)
        mlx_put_pixel(img, x, y, color[0]);
    else if(it % check == 0)
        mlx_put_pixel(img, x, y, color[it / check - 1]);
    else
        mlx_put_pixel(img, x, y, color[it / check]);
}
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
            //if(ox > 0 && x < 1)
            //    printf("%f\n", ox);
            i = julia(jul->it, ((jul->fx) * jul->zoom + jul->x + ox), ((jul->fy) * jul->zoom  + jul->y + oy), jul->cx, jul->cy, jul);//check if parameters fuck zoom
            if(i == jul->it + 1)
                mlx_put_pixel(img, x, y, 0x000000FF);
            else
            {
                i = i + 1 - log (log  (sqrt (jul->zx*jul->zx+jul->zy*jul->zy))) / log(2);
                i *= 1000000;
                c += (p * i);
                mlx_put_pixel(img, x, y, c);
            }
                //colored(i, img, x, y, jul);
            x++;
        }
        y++;
    }
}

int b = 0xFFFFFFFF;

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
        jul->x += 0.071;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_LEFT))
    {
        jul->x -= 0.071;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_UP))
    {
        jul->y += 0.071;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_DOWN))
    {
        jul->y -= 0.071;
        fractal(jul, jul->img, 0, 0);
    }
	if (mlx_is_key_down(jul->mlx, MLX_KEY_H))
        bro = menu(jul->mlx, 0, bro);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_Q))
        bro = menu(jul->mlx, 1, bro);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_ADD))
    {
        jul->it += 50;
        fractal(jul, jul->img, 0, 0);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_SUBTRACT))
    {
        if(jul->it >= 50)
        {
            jul->it -= 50;
            fractal(jul, jul->img, 0, 0);
        }
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_O))
    {
        jul->zoom /= 1.3;
        fractal(jul, jul->img, jul->offsetx, jul->offsetx);
    }
        if (mlx_is_key_down(jul->mlx, MLX_KEY_P))
    {
        jul->zoom *= 1.3;
        fractal(jul, jul->img, jul->offsetx, jul->offsetx);
    }
}

//void scroll(double xdelta, double ydelta, void *param)
//{
//    t_fractal *jul = param;

//	if (ydelta > 1)
//    {
//		jul->zoom *= 1.3;
//        //jul->height *= 1.3;
//        //jul->width *= 1.3;
//        printf("%f ; %f\n", jul->offsetx * jul->zoom, jul->offsety * jul->zoom);
//        fractal(jul, jul->img, jul->offsetx * jul->zoom, jul->offsety * jul->zoom);
//        //fractal(jul, jul->img, 0, 0);
//    }
//	if (ydelta < -1)
//    {
//        jul->zoom /= 1.3;
//        //jul->height /= 1.3;
//        //jul->width /= 1.3;
//        //fractal(jul, jul->img, 0, 0);
//        printf("%f ; %f\n", jul->offsetx * jul->zoom, jul->offsety * jul->zoom);
//        fractal(jul, jul->img, jul->offsetx * jul->zoom, jul->offsety * jul->zoom);
//    }
//}

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
        jul->offsetx = -1;
    else
        jul->offsetx = (jul->mousex  - WIDTH / 2.0) / HEIGHT * (2);
    if(jul->mousey == 0)
        jul->offsety = 1;
    else
        jul->offsety = (jul->mousey - HEIGHT / 2.0) / WIDTH * (-2);
}

int32_t	main(void)
{
	static t_fractal *jul;
    jul = malloc(sizeof(t_fractal));
    jul->x = 0;
    jul->y = 0;
    jul->it = 30;  //specific of fractal.
    jul->zoom = 1;
    jul->color = 10;
    jul->cx =-0.79;
    jul->cy =0.15;
    jul->height = HEIGHT;
    jul->width = WIDTH;
	if (!(jul->mlx = mlx_init(1400, 1400, "MLX42", true)))
		return(EXIT_FAILURE);
	jul->img = mlx_new_image(jul->mlx, WIDTH, HEIGHT);
    fractal(jul, jul->img, 0, 0);
    mlx_image_to_window(jul->mlx, jul->img, 0, 0);
	mlx_loop_hook(jul->mlx, &hook, jul);
    //mlx_scroll_hook(jul->mlx, &scroll, jul);
    mlx_cursor_hook(jul->mlx, &mouse, jul);
    mlx_loop_hook(jul->mlx, &co, jul);
	mlx_loop(jul->mlx);
	mlx_terminate(jul->mlx);
	return (EXIT_SUCCESS);
}
