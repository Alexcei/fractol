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

void			fdf_create(t_data *data)
{
	int			x;
	int 		y;

	y = 0;
	init_size(data);
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