/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 01:02:16 by bpole             #+#    #+#             */
/*   Updated: 2019/12/11 01:02:52 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		print_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

t_complex	init_complex(double re, double im)
{
	t_complex complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

void		fr_view_up(t_data *data)
{
	data->alpha = 0;
	data->beta = 0;
	data->threads = 4;
	data->red = 2;
	data->green = 1;
	data->blue = 3;
	data->max_iteration = 30;
	data->max.re = 2.0;
	data->min = init_complex(-2, -2);
}

void		render_menu5(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 480, 180,
			TEXT_COLOR, "MODE 3D");
	mlx_string_put(data->mlx, data->win, 320, 200,
			TEXT_COLOR, "3D on / off - Press  - \"G\"");
	mlx_string_put(data->mlx, data->win, 320, 220,
			TEXT_COLOR, "Grid on / off - Press  - \"C\"");
	mlx_string_put(data->mlx, data->win, 320, 240,
			TEXT_COLOR, "Polygon on / off - Press  - \"F\"");
	mlx_string_put(data->mlx, data->win, 320, 260,
			TEXT_COLOR, "Change step greid - UP / DOWN");
	mlx_string_put(data->mlx, data->win, 320, 280,
			TEXT_COLOR, "Change height - LEFT / RIGHT");
}
