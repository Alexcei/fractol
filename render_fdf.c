/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:54:35 by bpole             #+#    #+#             */
/*   Updated: 2019/12/11 00:55:23 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		paint_point(int x, int y, t_data *data, int color_default)
{
	int			i;

	(void)color_default;
	i = x + y * WIDTH;
	if (0 < x && x < WIDTH && 0 < y && y < HEIGHT)
		((int *)(data->data_addr))[i] = FDF;
}

static void		render_line(t_dot a, t_dot b, t_data *data)
{
	double		x_step;
	double		y_step;
	int			max;

	if (!data->coord)
		return ;
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

static void		init_dot_c_d(int i, t_dot *dot_c, t_dot *dot_d, t_data *data)
{
	if (i + data->width < data->size)
		*dot_c = transformations(data->dot[i + data->width], data);
	if (i + data->width + 1 < data->size)
		*dot_d = transformations(data->dot[i + data->width + 1], data);
}

void			render_map(t_data *data)
{
	t_dot		dots[4];
	int			i;

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
