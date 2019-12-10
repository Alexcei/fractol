#include "fractol.h"

//static void		zoom_down(t_data *data)
//{
//	(void)data;
//	data->camera->zoom  -= 1;
//	if (data->camera->zoom  < 1)
//		data->camera->zoom = 1;
//}

static void		put_pause(t_data *data)
{
	if (data->pause == 0)
		data->pause = 1;
	else
		data->pause = 0;
}

static void		help_up(t_data *data)
{
	if (data->help == 0)
		data->help = 1;
	else
		data->help = 0;
}

static void		color_up(int	*color, int key)
{
	if (key == MAIN_PAD_A || key == MAIN_PAD_S ||  key == MAIN_PAD_D)
	{
		if (*color == 0)
			*color = 0;
		else
			*color -= 1;
	}
	else
	{
		if (*color == 10)
			*color = 10;
		else
			*color += 1;
	}
}

void	mandelbrot_up(t_data *data)
{
	if (!data->fractal->mandelbrot)
	{
		data->fractal->mandelbrot = 1;
		data->fractal->julia = 0;
		data->fractal->burning_ship = 0;
		data->fractal->mandelbar = 0;
		data->fractal->celtic_mandelbrot = 0;
	}
	else
		data->fractal->mandelbrot = 0;
	fr_view_up(data);
}

void	julia_up(t_data *data)
{
	if (!data->fractal->julia)
	{
		data->fractal->mandelbrot = 0;
		data->fractal->julia = 1;
		data->fractal->burning_ship = 0;
		data->fractal->mandelbar = 0;
		data->fractal->celtic_mandelbrot = 0;
	}
	else
		data->fractal->julia = 0;
	fr_view_up(data);
}

void	burning_ship_up(t_data *data)
{
	if (!data->fractal->burning_ship)
	{
		data->fractal->mandelbrot = 0;
		data->fractal->julia = 0;
		data->fractal->burning_ship = 1;
		data->fractal->mandelbar = 0;
		data->fractal->celtic_mandelbrot = 0;
	}
	else
		data->fractal->burning_ship = 0;
	fr_view_up(data);
}

void	mandelbar_up(t_data *data)
{
	if (!data->fractal->mandelbar)
	{
		data->fractal->mandelbrot = 0;
		data->fractal->julia = 0;
		data->fractal->burning_ship = 0;
		data->fractal->mandelbar = 1;
		data->fractal->celtic_mandelbrot = 0;
	}
	else
		data->fractal->mandelbar = 0;
	fr_view_up(data);
}

void	celtic_mandelbrot_up(t_data *data)
{
	if (!data->fractal->celtic_mandelbrot)
	{
		data->fractal->mandelbrot = 0;
		data->fractal->julia = 0;
		data->fractal->burning_ship = 0;
		data->fractal->mandelbar = 0;
		data->fractal->celtic_mandelbrot = 1;
	}
	else
		data->fractal->celtic_mandelbrot = 0;
	fr_view_up(data);
}

void	threads_up(int key, t_data *data)
{
	if (key == MAIN_PAD_PLUS)
	{
		if (data->threads == 4)
			data->threads = 4;
		else
			data->threads++;
	}
	if (key == MAIN_PAD_MINUS)
	{
		if (data->threads == 1)
			data->threads = 1;
		else
			data->threads--;
	}
}

void	fdf_up(t_data *data)
{
	if (data->fdf == 0)
	{
		data->threads = 1;
		data->fdf = 1;
	}
	else
	{
		data->threads = 4;
		data->fdf = 0;
	}
	data->alpha = 0;
	data->beta = 0;
}

void	polygon_up(t_data *data)
{
	if (data->polygon == 0)
		data->polygon = 1;
	else
		data->polygon = 0;
}

void	arrow_control(t_data *data, int key)
{
	if (key == ARROW_LEFT)
	{
		if (data->step == 1)
			data->step = 1;
		else
			data->step--;
	}
	else if (key == ARROW_RIGHT)
	{
		if (data->step == 100)
			data->step = 100;
		else
			data->step++;
	}
	else if (key == ARROW_UP)
		data->m += 1;
	else if (key == ARROW_DOWN)
		data->m -= 1;
	init_fdf(data);
}

int				fr_hook_keydown(int key, t_data *data)
{
	if (key == MAIN_PAD_ESC)
		exit(EXIT_SUCCESS);
	if (key == MAIN_PAD_P)
		put_pause(data);
	if (key == MAIN_PAD_H)
		help_up(data);

	if (key == MAIN_PAD_F)
		polygon_up(data);

	if (key == MAIN_PAD_G)
		fdf_up(data);

	if (key == MAIN_PAD_1)
		mandelbrot_up(data);
	if (key == MAIN_PAD_2)
		julia_up(data);
	if (key == MAIN_PAD_3)
		burning_ship_up(data);
	if (key == MAIN_PAD_4)
		mandelbar_up(data);
	if (key == MAIN_PAD_5)
		celtic_mandelbrot_up(data);

	if (key == 91)
		data->k.re += 0.1;
	if (key == 84)
		data->k.re -= 0.1;
	if (key == 86)
		data->k.im -= 0.1;
	if (key == 88)
		data->k.im += 0.1;

	if (key == MAIN_PAD_PLUS || key == MAIN_PAD_MINUS)
		threads_up(key, data);

	if (key == MAIN_PAD_A || key == MAIN_PAD_Q)
		color_up(&data->red, key);

	if (key == MAIN_PAD_S || key == MAIN_PAD_W)
		color_up(&data->green, key);

	if (key == MAIN_PAD_D || key == MAIN_PAD_E)
		color_up(&data->blue, key);

	if (key == NUM_PAD_MINUS)
	{
		if (data->max_iteration == 2)
			data->max_iteration = 2;
		else
			data->max_iteration -= 1;
	}
	if (key == NUM_PAD_PLUS)
		data->max_iteration  += 1;
	if (key == ARROW_LEFT || key == ARROW_RIGHT ||
	key == ARROW_UP || key == ARROW_DOWN)
		arrow_control(data, key);
	fr_render(data);
	return (0);
}