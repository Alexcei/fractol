#include "fractol.h"

static void		render_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 85, 20,
				   TEXT_COLOR, "MENU");
	mlx_string_put(data->mlx, data->win, 65, 40,
				   TEXT_COLOR, "Zoom - Scroll mouse");
	mlx_string_put(data->mlx, data->win, 65, 60,
				   TEXT_COLOR, "Rotate - Press left mouse and move");
	mlx_string_put(data->mlx, data->win, 65, 80,
				   TEXT_COLOR, "Move - Press right mouse and move");
	mlx_string_put(data->mlx, data->win, 65, 100,
				   TEXT_COLOR, "Reset view - Press wheel mouse");
	mlx_string_put(data->mlx, data->win, 65, 120,
				   TEXT_COLOR, "Pause - \"P\"");
}

void			fr_render(t_data *data)
{
	fr_creat_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (data->help)
		render_menu(data);
	else
		mlx_string_put(data->mlx, data->win, 85, 20,
					   TEXT_COLOR, "H");
}