/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_fractal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:42:30 by bpole             #+#    #+#             */
/*   Updated: 2019/12/11 00:42:52 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
