#include "fractol.h"

static void		render_background(t_data *data)
{
	int 		i;

	i = 0;
	ft_bzero(data->data_addr, sizeof(char) * SIZE);
	while (i < SIZE)
		((int*)(data->data_addr))[i++] = BACKGROUND;
}

static int		get_color(t_data *data)
{
	double		ratio;
	int			red;
	int			green;
	int			blue;

	ratio = (double)data->iteration / (double)data->max_iteration;
	data->ratio = ratio * data->m;
	red = (int)(ratio * 255);
	green = (int)(ratio * 255);
	blue = (int)(ratio * 255);
	red *= data->red;
	green *= data->green;
	blue *= data->blue;
	return ((red << 16) | (green << 8) | blue);
}

static void		check_runaway(t_data *data)
{
	while (pow(data->z.re, 2.0) + pow(data->z.im, 2.0) <= 4
		   && data->iteration < data->max_iteration)
	{
		if (data->fractal->mandelbrot)
			mandelbrot(data);
		else if (data->fractal->julia)
			julia(data);
		else if (data->fractal->burning_ship)
			burning_ship(data);
		else if (data->fractal->mandelbar)
			mandelbar(data);
		else if (data->fractal->celtic_mandelbrot)
			celtic_mandelbrot(data);
		else
			data->z = init_complex(5, 5);
		data->iteration++;
	}
}

void		rotate(t_dot *dot, double alpha, double beta)
{
	double		x;
	double		y;

	x = dot->x;
	y = dot->y;
	dot->x = cos(beta) * x + sin(beta) * dot->z;
	dot->z = -sin(beta) * x + cos(beta) * dot->z;
	dot->y = cos(alpha) * y - sin(alpha) * dot->z;
	dot->z = sin(alpha) * y + cos(alpha) * dot->z;
}

t_dot			transformations(t_dot dot, t_data *data)
{
	dot.x -= (data->width - 1) / 2;
	dot.y -= (data->height - 1) / 2;
	dot.z -= (0 + 1) / 2;
	rotate(&dot, data->alpha, data->beta);
	dot.x *= data->zoom;
	dot.y *= data->zoom;
	dot.x += data->x_offset;
	dot.y += data->y_offset;
	return (dot);
}

static void		paint_point(int x, int y, t_data *data, int color_default)
{
	int			i;

	(void)color_default;
	i = x + y * WIDTH;
	if (0 < x && x < WIDTH && 0 < y && y < HEIGHT)
		((int *)(data->data_addr))[i] = FDF;
}

void			render_line(t_dot a, t_dot b, t_data *data)
{
	double		x_step;
	double		y_step;
	int 		max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		paint_point((int)a.x, (int)a.y, data, a.color);
		a.x += x_step;
		a.y += y_step;
	}
}

static void		paint_plane(int x, int y, t_data *data, int color_default)
{
	int			i;

	i = x + y * WIDTH;
	if (0 < x && x < WIDTH && 0 < y && y < HEIGHT)
	{
		((int *)(data->data_addr))[i] = color_default;
	}
}

static void		render_line_plane(t_dot a, t_dot b, t_data *data)
{
	double 		x_step;
	double 		y_step;
	int 		max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		paint_plane((int)a.x, (int)a.y, data, data->color_tmp);
		a.x += x_step;
		a.y += y_step;
	}
}

void			render_plane(t_dot a, t_dot b, t_dot c, t_data *data)
{
	double		x_step;
	double		y_step;
	int			max;

	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		render_line_plane(a, c, data);
		a.x += x_step;
		a.y += y_step;
	}
}

static void		init_dot_c_d(int i, t_dot *dot_c, t_dot *dot_d, t_data *data)
{
	if (i + data->width < data->size)
		*dot_c = transformations(data->dot[i + data->width], data);
	if (i + data->width + 1 < data->size)
		*dot_d = transformations(data->dot[i + data->width + 1], data);
}

static void		render_map(t_data *data)
{
	t_dot		dots[4];
	int 		i;

	i = -1;
	while (++i < data->size)
	{
		dots[0] = transformations(data->dot[i], data);
		if (i + 1 < data->size)
			dots[1] = transformations(data->dot[i + 1], data);
		init_dot_c_d(i, &dots[2], &dots[3], data);
		if ((i + 1) % data->width != 0)
		{
			if (dots[0].color && data->polygon &&
				i / data->width != data->height - 1)
			{
				data->color_tmp = dots[0].color;
				render_plane(dots[0], dots[1], dots[2], data);
				render_plane(dots[1], dots[2], dots[3], data);
			}
			render_line(dots[0], dots[1], data);
		}
		if (i / data->width != data->height - 1)
			render_line(dots[0], dots[2], data);
	}
}

void		fdf_create(t_data *data)
{
	int			x;
	int 		y;

	y = 0;
	while (y < data->height)
	{
		data->c.im = data->max.im - y * data->step * data->factor.im;
		x = 0;
		while (x < data->width)
		{
			data->c.re = data->min.re + x * data->step * data->factor.re;
			data->z = init_complex(data->c.re, data->c.im);
			data->iteration = 0;
			check_runaway(data);
			data->dot[y * data->width + x].color = get_color(data);
			data->dot[y * data->width + x].z = (double)data->ratio;
			data->dot[y * data->width + x].x = (double)x;
			data->dot[y * data->width + x].y = (double)y;
			x++;
		}
		y++;
	}
	render_background(data);
	render_map(data);
}