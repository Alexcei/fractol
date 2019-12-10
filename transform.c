#include "fractol.h"

static void		rotate(t_dot *dot, double alpha, double beta)
{
	double		x;
	double		y;

	x = dot->x;
	y = dot->y;
	dot->x = cos(beta) * x + sin(beta) * dot->z;
	dot->z = -sin(beta) * x + cos(beta) * dot->z;
	dot->y = cos(alpha) * y - sin(alpha) * dot->z;
	dot->z = sin(alpha) * y + cos(alpha) * dot->z;
}

t_dot			transformations(t_dot dot, t_data *data)
{
	dot.x -= (data->width - 1) / 2;
	dot.y -= (data->height - 1) / 2;
	dot.z -= (0 + 1) / 2;
	rotate(&dot, data->alpha, data->beta);
	dot.x *= data->zoom;
	dot.y *= data->zoom;
	dot.x += data->x_offset;
	dot.y += data->y_offset;
	return (dot);
}