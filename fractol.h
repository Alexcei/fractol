#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_printf/ft_printf.h"
# include <mlx.h>
# include <math.h>

# define HEIGHT				800
# define WIDTH				800
# define SIZE 				HEIGHT * WIDTH

# define BACKGROUND			0xFFFFFF
# define TEXT_COLOR			0xEAEAEA

# define MOUSE_LEFT_BUTTON	1
# define MOUSE_RIGHT_BUTTON	2
# define MOUSE_THREE_BUTTON	3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

# define MAIN_PAD_ESC		53
# define MAIN_PAD_A			0
# define MAIN_PAD_S			1
# define MAIN_PAD_D			2
# define MAIN_PAD_H			4
# define MAIN_PAD_G			5
# define MAIN_PAD_Q			12
# define MAIN_PAD_W			13
# define MAIN_PAD_E			14
# define MAIN_PAD_P			35

# define MAIN_PAD_1			18
# define MAIN_PAD_2			19
# define MAIN_PAD_3			20
# define MAIN_PAD_4			21
# define MAIN_PAD_5			23
# define MAIN_PAD_6			22

# define MAIN_PAD_PLUS		24
# define MAIN_PAD_MINUS		27

typedef struct		s_mouse
{
	char			put_left;
	char			put_right;
	int				x;
	int				y;
	int				previous_x;
	int				previous_y;
}					t_mouse;

typedef struct		s_fractal
{
	int				mandelbrot;
	int				julia;
	int				burning_ship;
	int				mandelbar;
	int				celtic_mandelbrot;
}					t_fractal;

typedef struct 		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct		s_data
{
	t_fractal 		*fractal;
	t_mouse 		*mouse;
	t_complex		factor;
	t_complex		max;
	t_complex		min;
	t_complex		c;
	t_complex		z;
	t_complex		k;
	int red;
	int green;
	int blue;
	int 			max_iteration;
	int 			iteration;
	//int				width;
	int 			help;
	int 			pause;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_data;

/*
**					control.c
*/
int					fr_hook_keydown(int key, t_data *data);

/*
**					control_mouse.c
*/
int					fr_mouse_press(int button, int x, int y, void *param);
int					fr_mouse_release(int button, int x, int y, void *param);
int					fr_mouse_move(int x, int y, void *param);

/*
**					fractol.c
*/
void				mandelbrot(t_data *data);
void				julia(t_data *data);
void				burning_ship(t_data *data);
void				mandelbar(t_data *data);
void				celtic_mandelbrot(t_data *data);

/*
**					loop_key_hook.c
*/
int					fr_loop_key_hook(t_data *data);
void 				fr_creat_image(t_data *data);

/*
**					render.c
*/
void				fr_render(t_data *data);

/*
**					utils.c
*/
void				print_error(char *message);
t_complex			init_complex(double re, double im);

#endif
