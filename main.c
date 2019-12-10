/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:48:28 by bpole             #+#    #+#             */
/*   Updated: 2019/12/11 00:52:39 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		fdf_close(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
}

static int		fr_init(t_data *data, t_mouse *mouse, t_fractal *fractal)
{
	ft_bzero(fractal, sizeof(t_fractal));
	ft_bzero(mouse, sizeof(t_mouse));
	ft_bzero(data, sizeof(t_data));
	data->fractal = fractal;
	data->mouse = mouse;
	if (!(data->mlx = mlx_init()) ||
			!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol"))
			|| !(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	data->threads = 4;
	data->max_iteration = 30;
	data->red = 2;
	data->green = 1;
	data->blue = 3;
	data->max.re = 2.0;
	data->min = init_complex(-2, -2);
	data->k = init_complex(-0.4, 0.6);
	data->step = 20;
	data->m = 40;
	data->x_offset = WIDTH / 2;
	data->y_offset = HEIGHT / 2;
	return (1);
}

void			init_fdf(t_data *data)
{
	data->width = WIDTH / data->step - 1;
	data->height = HEIGHT / data->step - 1;
	data->zoom = FT_MIN(WIDTH / data->width, HEIGHT / data->height);
	data->size = data->width * data->height;
	if (data->dot)
		ft_memdel((void*)&data->dot);
	if (!(data->dot = (t_dot*)ft_memalloc(sizeof(t_dot) * data->size)))
		print_error("error: initialization");
}

static void		init_fractol(t_data *data, char *av)
{
	if (ft_strequ("m", av))
		data->fractal->mandelbrot = 1;
	else if (ft_strequ("j", av))
		data->fractal->julia = 1;
	else if (ft_strequ("b", av))
		data->fractal->burning_ship = 1;
	else if (ft_strequ("mbar", av))
		data->fractal->mandelbar = 1;
	else if (ft_strequ("cm", av))
		data->fractal->celtic_mandelbrot = 1;
	else
		print_error(CYN"Usage: ./fractol [m | j | b | mbar | cm]"RESET);
}

int				main(int ac, char **av)
{
	t_fractal	fractal;
	t_mouse		mouse;
	t_data		data;

	if (ac != 2)
		print_error(CYN"Usage: ./fractol [m | j | b | mbar | cm]"RESET);
	if (!fr_init(&data, &mouse, &fractal))
		print_error("error: initialization");
	init_fractol(&data, av[1]);
	init_fdf(&data);
	data.polygon = 1;
	fr_render(&data);
	mlx_key_hook(data.win, fr_hook_keydown, &data);
	mlx_hook(data.win, 17, 0, fdf_close, &data);
	mlx_hook(data.win, 4, 0, fr_mouse_press, &data);
	mlx_hook(data.win, 5, 0, fr_mouse_release, &data);
	mlx_hook(data.win, 6, 0, fr_mouse_move, &data);
	mlx_loop(&data.mlx);
	return (0);
}
