/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:18:13 by egervais          #+#    #+#             */
/*   Updated: 2023/04/12 17:45:46 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define HEIGHT 1400
# define WIDTH 1400
# define ERROR -1

enum				e_fractal
{
	MANDELBROT,
	JULIA,
	BURNINGSHIP
};

typedef struct s_complex
{
	double			x;
	double			y;
}					t_complex;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}			t_color;

typedef struct s_fractal
{
	enum e_fractal	name;
	mlx_image_t		*img;
	mlx_image_t		*men;
	mlx_t			*mlx;
	t_complex		f;
	t_complex		offset;
	t_complex		c;
	t_complex		z;
	t_complex		arrow;
	double			cadreminx;
	double			cadremaxx;
	double			cadreminy;
	double			cadremaxy;
	double			zoom;
	int				it;
	int				color;
	t_color			rgba;
	int				pos;
	int				check;
}					t_fractal;

//int		mousex;
//int		mousey;

void				fractal(t_fractal *jul);
int					burningship(t_fractal *jul);
int					julia(t_fractal *jul);
int					mandelbrot(t_fractal *jul);
void				loop(t_fractal *jul);
void				paraminit(t_fractal *jul);
void				initjul(t_fractal *jul, char **name, int argc);
int					init_fractal(t_fractal *jul, char **name, int argc);
int					init_mlx(t_fractal *jul);
int					create_fractal(t_fractal *jul, int argc, char **argv);
int					ft_strcmp(const char *s1, const char *s2);
int					color(int i, t_fractal *jul);
void				xhook(void *param);
void				ft_putstr(char *str);
int					ft_strlen(char *str);

#endif