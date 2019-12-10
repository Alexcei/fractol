/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:53:53 by bpole             #+#    #+#             */
/*   Updated: 2019/12/11 00:54:28 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		render_menu1(t_data *data)
{
	char	*fractol;

	if (data->fractal->mandelbrot)
		fractol = "Mandelbrot";
	else if (data->fractal->julia)
		fractol = "Julia";
	else if (data->fractal->burning_ship)
		fractol = "Burning_ship";
	else if (data->fractal->mandelbar)
		fractol = "Mandelbar";
	else if (data->fractal->celtic_mandelbrot)
		fractol = "Celtic_mandelbrot";
	else
		fractol = "not selected";
	mlx_string_put(data->mlx, data->win, 150, 20,
			TEXT_COLOR, "Current fractal - ");
	mlx_string_put(data->mlx, data->win, 330, 20,
			TEXT_COLOR, fractol);
}

static void		render_menu2(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 45, 40,
			TEXT_COLOR, "MENU");
	mlx_string_put(data->mlx, data->win, 25, 60,
			TEXT_COLOR, "Zoom - Scroll mouse");
	mlx_string_put(data->mlx, data->win, 25, 80,
			TEXT_COLOR, "Move - Press right mouse and move");
	mlx_string_put(data->mlx, data->win, 25, 100,
			TEXT_COLOR, "Turn Julia - Move mouse");
	mlx_string_put(data->mlx, data->win, 25, 120,
			TEXT_COLOR, "Julia stop - \"P\"");
	mlx_string_put(data->mlx, data->win, 25, 140,
			TEXT_COLOR, "Reset view - Press wheel mouse");
	mlx_string_put(data->mlx, data->win, 400, 40,
			TEXT_COLOR, "Change fractal - Press:");
	mlx_string_put(data->mlx, data->win, 420, 60,
			TEXT_COLOR, "Mandelbrot - 1");
	mlx_string_put(data->mlx, data->win, 420, 80,
			TEXT_COLOR, "Julia - 2");
	mlx_string_put(data->mlx, data->win, 420, 100,
			TEXT_COLOR, "Burning ship - 3");
	mlx_string_put(data->mlx, data->win, 420, 120,
			TEXT_COLOR, "Mandelbar - 4");
	mlx_string_put(data->mlx, data->win, 420, 140,
			TEXT_COLOR, "Celtic mandelbrot - 5");
}

static void		render_menu3(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 45, 550,
			TEXT_COLOR, "Change color");
	mlx_string_put(data->mlx, data->win, 25, 570,
			TEXT_COLOR, "Red +/- Press \"Q\" / \"A\"");
	mlx_string_put(data->mlx, data->win, 25, 590,
			TEXT_COLOR, "Green +/- Press \"W\" / \"S\"");
	mlx_string_put(data->mlx, data->win, 25, 610,
			TEXT_COLOR, "Blue +/- Press \"E\" / \"D\"");
}

static void		render_menu4(t_data *data)
{
	char		*iterations;
	char		*threads;

	iterations = ft_itoa(data->max_iteration);
	threads = ft_itoa(data->threads);
	mlx_string_put(data->mlx, data->win, 380, 510,
			TEXT_COLOR, "System");
	mlx_string_put(data->mlx, data->win, 340, 530,
			TEXT_COLOR, "Change iterations +/- num pad");
	mlx_string_put(data->mlx, data->win, 340, 550,
			TEXT_COLOR, "Change iterations X10 Press *");
	mlx_string_put(data->mlx, data->win, 340, 570,
			TEXT_COLOR, "Current iterations - ");
	mlx_string_put(data->mlx, data->win, 550, 570,
			TEXT_COLOR, iterations);
	mlx_string_put(data->mlx, data->win, 340, 590,
			TEXT_COLOR, "Change threads +/- main pad");
	mlx_string_put(data->mlx, data->win, 340, 610,
			TEXT_COLOR, "Current threads - ");
	mlx_string_put(data->mlx, data->win, 520, 610,
			TEXT_COLOR, threads);
	ft_strdel(&iterations);
	ft_strdel(&threads);
}

void			fr_render(t_data *data)
{
	if (data->fdf)
		fdf_create(data);
	else
		fr_creat_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (data->help)
	{
		render_menu1(data);
		render_menu2(data);
		render_menu3(data);
		render_menu4(data);
		render_menu5(data);
	}
	else
		mlx_string_put(data->mlx, data->win, 45, 40,
				TEXT_COLOR, "H");
}
