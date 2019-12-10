#include "fractol.h"

static int		get_color(t_data *data)
{
	double		ratio;
	int			red;
	int			green;
	int			blue;

	ratio = (double)data->iteration / (double)data->max_iteration;
	red = (int)(ratio * 255);
	green = (int)(ratio * 255);
	blue = (int)(ratio * 255);
	red *= data->red;
	green *= data->green;
	blue *= data->blue;
	return ((red << 16) | (green << 8) | blue);
}

static void		init_size(t_data *data)
{
	data->max.im = data->min.im + (data->max.re - data->min.re) * HEIGHT / WIDTH;
	data->factor = init_complex(
			(data->max.re - data->min.re) / (WIDTH - 1),
			(data->max.im - data->min.im) / (HEIGHT - 1));
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

static void		*creat_image(t_data *data)
{
	int			x;

	while (++data->begin < data->end)
	{
		data->c.im = data->max.im - data->begin * data->factor.im;
		x = 0;
		while (x < WIDTH)
		{
			data->c.re = data->min.re + x * data->factor.re;
			data->z = init_complex(data->c.re, data->c.im);
			data->iteration = 0;
			check_runaway(data);
			if (data->begin >= HEIGHT || x >= HEIGHT || x < 0 || data->begin < 0)
				return (NULL);
			((int *)(data->data_addr))[(int)(data->begin * WIDTH + x)] = get_color(data);
			x++;
		}
	}
	pthread_exit(NULL);
}

void			fr_creat_image(t_data *data)
{
	t_data		data_arr[data->threads];
	pthread_t	id[data->threads];
	int i;

	i = -1;
	init_size(data);
	ft_memset(id, 0, sizeof(pthread_t) * data->threads);
	while (++i < data->threads)
	{
		data_arr[i] = *data;
		data_arr[i].begin = ((HEIGHT / data->threads) * i) - 1;
		data_arr[i].end = (HEIGHT / data->threads) * (i + 1) + 1;
		pthread_create(id + i, NULL, (void*)creat_image, &data_arr[i]);
	}
	while (i--)
		pthread_join(id[i], NULL);
}