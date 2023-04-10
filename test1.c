#include "fractol.h"
#define MIN_DISTANCE 0.0001
#define MAX_DISTANCE 1000.0

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

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

int color(int i, t_fractal *jul)
{
    int r, g, b, a;
    double t = (double)i / (double)jul->it;
    
    if(jul->color == 0)
    {
        r = (int)(9*(1-t)*t*t*t*255);
        g = (int)(15*(1-t)*(1-t)*t*t*255);
        b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
        a = 255;
    }
    if(jul->color == 1)
    {
        r = (int)(10*(1-t)*(1-t)*t*t*255);
        g = (int)(8*(1-t)*(1-t)*(1-t)*t*255);
        b = (int)(12*(1-t)*t*t*t*255);
        a = 255;
    }
    if(jul->color == 2)
    {
        r = (int)(10*(1-t)*(1-t)*(1-t)*t*255);
        g = (int)(8*(1-t)*t*t*t*255);
        b = (int)(12*(1-t)*(1-t)*t*t*255);
        a = 255;
    }
    return (get_rgba(r, g, b, a));
}

void draw_fractal(int x, int y, t_fractal *jul)
{
    int it;
    coordinate(x, y, jul);
    if(jul->name == JULIA)
        it = julia(jul->it, ((jul->fx)), ((jul->fy)), jul->cx, jul->cy, jul);
    else if(jul->name == MANDELBROT)
        it = mandelbrot(jul);
    else if(jul->name == BURNINGSHIP)
        it = burningship(jul->it, jul->fx, jul->fy, jul);
    if(it == jul->it)
        mlx_put_pixel(jul->img, x, y, 0x000000FF);
    else if(it == jul->it - 1)
        mlx_put_pixel(jul->img, x, y, 0xFFFFFFFF);
    else
        //i = it + 1 - log (log  (sqrt (jul->zx*jul->zx+jul->zy*jul->zy))) / log(2);
        mlx_put_pixel(jul->img, x, y, color(it, jul));
}

void fractal(t_fractal* jul)
{
    int x = 0;
    int y = 0;
    //double i;
    while(y <= HEIGHT)
    {
        x = 0;
        while(x <= WIDTH)
        {
            draw_fractal(x, y, jul);
            /*coordinate(x, y, jul);
            it = julia(jul->it, ((jul->fx) + ox), ((jul->fy) + oy), jul->cx, jul->cy, jul);
            if(it == jul->it)
                mlx_put_pixel(img, x, y, 0x000000FF);
            else if(it == jul->it - 1)
                mlx_put_pixel(img, x, y, 0xFFFFFFFF);
            else
                //i = it + 1 - log (log  (sqrt (jul->zx*jul->zx+jul->zy*jul->zy))) / log(2);
                mlx_put_pixel(img, x, y, color(it, jul));*/
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
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_LEFT))
    {
        jul->arrowx -= (0.05 * jul->zoom);
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_UP))
    {
        jul->arrowy -= (0.05 * jul->zoom);
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_DOWN))
    {
        jul->arrowy += (0.05 * jul->zoom);
        fractal(jul);
    }
	if (mlx_is_key_down(jul->mlx, MLX_KEY_H))
        bro = menu(jul->mlx, 0, bro);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_Q))
        bro = menu(jul->mlx, 1, bro);
    if (mlx_is_key_down(jul->mlx, MLX_KEY_C))
    {
        jul->color++;
        if(jul->color > 2)
            jul->color = 0;
        fractal(jul); 
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_ADD))
    {
        jul->it += 10;
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_KP_SUBTRACT))
    {
        if(jul->it >= 10)
        {
            jul->it -= 10;
            fractal(jul);
        }
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_O))
    {
        jul->zoom /= 1.1;
        fractal(jul);
    }
    if (mlx_is_key_down(jul->mlx, MLX_KEY_P))
    {
        jul->zoom *= 1.1;
        fractal(jul);
    }
}

void scroll(double xdelta, double ydelta, void *param)
{
    t_fractal *jul = param;

	if (ydelta > 2)
    {
		jul->zoom *= 1.1;
        fractal(jul);
    }
	if (ydelta < -2)
    {
        jul->zoom /= 1.1;
        fractal(jul);
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
            fractal(jul);
        }
        else
        {
            jul->pos = x;
            jul->cx -= 0.005;
            fractal(jul);
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
}

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
		return (0);
	return (1);
}

int32_t	main(int argc, char **argv)
{
    int check;
    if(argc < 2)
    {
        printf("no\n");
        return (-1);
    }
	static t_fractal *jul;
    jul = malloc(sizeof(t_fractal));
    jul->color = malloc(sizeof(int) * 101);
    paraminit(jul);
    check = init_fractal(jul, argv, argc);
    if(!check)
    {
        printf("no\n");
        return (0);
    }
	if (!(jul->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return(EXIT_FAILURE);
	jul->img = mlx_new_image(jul->mlx, WIDTH, HEIGHT);
    fractal(jul);
    mlx_image_to_window(jul->mlx, jul->img, 0, 0);
	mlx_loop_hook(jul->mlx, &hook, jul);
    mlx_scroll_hook(jul->mlx, &scroll, jul);
    mlx_cursor_hook(jul->mlx, &mouse, jul);
    mlx_loop_hook(jul->mlx, &co, jul);
	mlx_loop(jul->mlx);
	mlx_terminate(jul->mlx);
	return (EXIT_SUCCESS);
}