#include "fractol.h"

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

static void		threads_up(int key, t_data *data)
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

static void		help_up(t_data *data)
{
	if (data->help == 0)
		data->help = 1;
	else
		data->help = 0;
}

static void		arrow_control(t_data *data, int key)
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

void			fr_key_control(int key, t_data *data)
{
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
	if (key == MAIN_PAD_H)
		help_up(data);
	if (key == NUM_PAD_PLUS)
		data->max_iteration  += 1;
	if (key == NUM_PAD_STAR)
		data->max_iteration  *= 1.1;
	if (key == ARROW_LEFT || key == ARROW_RIGHT ||
		key == ARROW_UP || key == ARROW_DOWN)
		arrow_control(data, key);
}