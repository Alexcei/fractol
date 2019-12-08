#include "fractol.h"

static int		fdf_close(void *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}

static int		fr_init(t_data *data, t_mouse  *mouse, t_fractal *fractal)
{
	ft_bzero(fractal, sizeof(t_fractal));
	ft_bzero(mouse, sizeof(t_mouse));
	ft_bzero(data, sizeof(t_data));
	data->fractal = fractal;
	data->mouse = mouse;
	if (!(data->mlx = mlx_init()) ||
		!(data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol")) ||
		!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
		return (0);
	data->data_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
										&data->size_line, &data->endian);
	data->max_iteration = 20;
	data->red = 2;
	data->green = 1;
	data->blue = 3;
	data->max.re = 2.0;
	data->min = init_complex(-2, -2);
	data->k = init_complex(-0.4, 0.6);
	return (1);
}

int				main(int ac, char **av)
{
	t_fractal	fractal;
	t_mouse 	mouse;
	t_data		data;

	if (ac > 1)                                               //  !!!!!!!!!!
		print_error("error: initialization");        //  !!!!!!!!!
	if (!fr_init(&data, &mouse, &fractal))
		print_error("error: initialization");
	mlx_key_hook(data.win, fr_hook_keydown, &data);
	mlx_hook(data.win, 17, 0, fdf_close, &data);
	mlx_hook(data.win, 4, 0, fr_mouse_press, &data);
	mlx_hook(data.win, 5, 0, fr_mouse_release, &data);
	mlx_hook(data.win, 6, 0, fr_mouse_move, &data);
	mlx_loop_hook(data.mlx, fr_loop_key_hook, &data);
	mlx_loop(&data.mlx);
	return (0);
}