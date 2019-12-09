#include "fractol.h"

int 	fr_color(t_data *data)
{
	double t;
	int red;
	int green;
	int blue;

	t = (double)data->iteration / (double)data->max_iteration;
	red = (int)(t * 255);
	green = (int)(t * 255);
	blue = (int)(t * 255);
	red *= data->red;
	green *= data->green;
	blue *= data->blue;
	return ((red << 16) | (green << 8) | blue);
}

void		init_size(t_data *data)
{
	data->max.im = data->min.im + (data->max.re - data->min.re) * HEIGHT / WIDTH;
	data->factor = init_complex(
			(data->max.re - data->min.re) / (WIDTH - 1),
			(data->max.im - data->min.im) / (HEIGHT - 1));
}

void		fr_creat_image(t_data *data)
{
	int		x;
	int 	y;

	y = 0;
	init_size(data);
	while (y < HEIGHT)
	{
		data->c.im = data->max.im - y * data->factor.im;
		x = 0;
		while (x < WIDTH)
		{
			data->c.re = data->min.re + x * data->factor.re;
			data->z = init_complex(data->c.re, data->c.im);
			data->iteration = 0;
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
			((int *)(data->data_addr))[y * WIDTH + x] = fr_color(data);
			x++;
		}
		y++;
	}
}