#include "fractol.h"

void	mandelbrot(t_data *data)
{
	data->z = init_complex(
			pow(data->z.re, 2.0) - pow(data->z.im, 2.0) + data->c.re,
			2.0 * data->z.re * data->z.im + data->c.im);
}

void	julia(t_data *data)
{
	data->k = init_complex(data->k.re, data->k.im);
	data->z = init_complex(
			pow(data->z.re, 2.0) - pow(data->z.im, 2.0) + data->k.re,
			2.0 * data->z.re * data->z.im + data->k.im);
}

void	burning_ship(t_data *data)
{
	data->z = init_complex(
			pow(data->z.re, 2.0) - pow(data->z.im, 2.0) + data->c.re,
			-2.0 * fabs(data->z.re * data->z.im) + data->c.im);
}

void	mandelbar(t_data *data)
{
	data->z = init_complex(
			pow(data->z.re, 2.0) - pow(data->z.im, 2.0) + data->c.re,
			-2.0 * data->z.re * data->z.im + data->c.im);
}

void	celtic_mandelbrot(t_data *data)
{
	data->z = init_complex(
			fabs(pow(data->z.re, 2.0) - pow(data->z.im, 2.0)) + data->c.re,
			2.0 * data->z.re * data->z.im + data->c.im);
}