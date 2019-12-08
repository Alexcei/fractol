#include "fractol.h"

void			print_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

t_complex init_complex(double re, double im)
{
	t_complex complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}