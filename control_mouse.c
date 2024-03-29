/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:43:01 by bpole             #+#    #+#             */
/*   Updated: 2019/12/11 00:43:30 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		zoom(int key, t_data *data, int x, int y)
{
	double		i;

	i = (data->min.re - data->max.re) / 10;
	if (key == MOUSE_SCROLL_UP)
	{
		data->min.re -= 2 * i * x / WIDTH;
		data->max.re += 2 * i * (WIDTH - x) / WIDTH;
		data->min.im -= 2 * i * (HEIGHT - y) / HEIGHT;
	}
	else if (key == MOUSE_SCROLL_DOWN)
	{
		data->min.re += 2 * i * x / WIDTH;
		data->max.re -= 2 * i * (WIDTH - x) / WIDTH;
		data->min.im += 2 * i * (HEIGHT - y) / HEIGHT;
	}
}

int				fr_mouse_press(int button, int x, int y, void *param)
{
	t_data		*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom(button, data, x, y);
	else if (button == MOUSE_LEFT_BUTTON)
		data->mouse->put_left = 1;
	else if (button == MOUSE_RIGHT_BUTTON)
		data->mouse->put_right = 1;
	else if (button == MOUSE_THREE_BUTTON)
		fr_view_up(data);
	fr_render(data);
	return (0);
}

int				fr_mouse_release(int button, int x, int y, void *param)
{
	t_data		*data;

	(void)x;
	(void)y;
	(void)button;
	data = (t_data *)param;
	data->mouse->put_left = 0;
	data->mouse->put_right = 0;
	fr_render(data);
	return (0);
}

static void		mouse_move(int x, int y, t_data *data)
{
	double		i;

	i = (data->max.re - data->min.re) / WIDTH;
	if (data->fractal->julia && !data->pause)
	{
		data->k = init_complex(
				4 * ((double)x / WIDTH - 0.5),
				4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		fr_render(data);
	}
	if (data->mouse->put_right)
	{
		data->min.re -= (x - data->mouse->previous_x) * i;
		data->max.re -= (x - data->mouse->previous_x) * i;
		data->min.im += (y - data->mouse->previous_y) * i;
		fr_render(data);
	}
}

int				fr_mouse_move(int x, int y, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	data->mouse->previous_x = data->mouse->x;
	data->mouse->previous_y = data->mouse->y;
	data->mouse->x = x;
	data->mouse->y = y;
	if (data->mouse->put_left)
	{
		data->beta += (x - data->mouse->previous_x) * 0.002;
		data->alpha -= (y - data->mouse->previous_y) * 0.002;
		fr_render(data);
	}
	mouse_move(x, y, data);
	return (0);
}
