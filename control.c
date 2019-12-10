#include "fractol.h"

static void		put_pause(t_data *data)
{
	if (data->pause == 0)
		data->pause = 1;
	else
		data->pause = 0;
}

static void		fdf_up(t_data *data)
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

static void 	coord_up(t_data *data)
{
	if (data->coord == 0)
		data->coord = 1;
	else
		data->coord = 0;
}

static void		polygon_up(t_data *data)
{
	if (data->polygon == 0)
		data->polygon = 1;
	else
		data->polygon = 0;
}

int				fr_hook_keydown(int key, t_data *data)
{
	if (key == MAIN_PAD_ESC)
		exit(EXIT_SUCCESS);
	if (key == MAIN_PAD_P)
		put_pause(data);
	if (key == MAIN_PAD_F)
		polygon_up(data);
	if (key == MAIN_PAD_G)
		fdf_up(data);
	if (key == MAIN_PAD_C)
		coord_up(data);
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
	fr_key_control(key, data);
	fr_render(data);
	return (0);
}