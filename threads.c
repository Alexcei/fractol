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

void		*creat_image(t_data *data)
{
	int		x;

	while (++data->begin < data->end)
	{
		data->c.im = data->max.im - data->begin * data->factor.im;
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
			((int *)(data->data_addr))[data->begin * WIDTH + x] = fr_color(data);
			x++;
		}
	}
	pthread_exit(NULL);
}

void		fr_creat_image(t_data *data)
{
	t_data		o[data->threads];
	pthread_t	t[data->threads];
	int i;

	i = -1;
	init_size(data);
	ft_memset(t, 0, sizeof(pthread_t) * data->threads);
	while (++i < data->threads)
	{
		o[i] = *data;
		o[i].begin = ((HEIGHT / data->threads) * i) - 1;
		o[i].end = (HEIGHT / data->threads) * (i + 1) + 1;
		pthread_create(t + i, NULL, (void*)creat_image, &o[i]);
	}
	while (i--)
		pthread_join(t[i], NULL);
}

/*
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
*/

/*
#include <stdio.h>
void 	*m(t_pthread *pthread)
{
	int		x;
	t_data	*data;

	data = pthread->data;
	//init_size(data);
	ft_printf("%d\n", pthread->begin);
	ft_printf("%d\n", pthread->end);
	ft_printf("f - %f %f\n", data->factor.re, data->factor.im);
	while (++pthread->begin < pthread->end)
	{
		data->c.im = data->max.im - pthread->begin * data->factor.im;
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
			//printf("%d %d %d %d\n", pthread->begin, pthread->end, x, WIDTH);
			((int *)(data->data_addr))[pthread->begin * WIDTH + x] = fr_color(data);
			x++;
		}
		pthread->begin++;
	}
	pthread_exit(NULL);
}

static void	*fractal(void)
{
	return (m);
}

void		fr_creat_image(t_data *data)
{
	t_pthread	o[THREADS];
	pthread_t	t[THREADS];
	int			i;

	i = -1;
	init_size(data);
	ft_printf("f - %f %f\n", data->factor.re, data->factor.im);
	ft_memset(t, 0, sizeof(pthread_t) * THREADS);
	while (++i < THREADS)
	{
		o[i].data = data;
		o[i].begin = ((HEIGHT / THREADS) * i) - 1;
		o[i].end = (HEIGHT / THREADS) * (i + 1) + 1;
		ft_printf("<%d\n", o[i].begin);
		ft_printf("<%d\n", o[i].end);
		pthread_create(t + i, NULL, fractal(), o + i);
		ft_printf("!\n");
	}
	while (i--)
		pthread_join(t[i], NULL);
}*/