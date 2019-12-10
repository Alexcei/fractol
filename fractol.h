#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_printf/ft_printf.h"
# include <pthread.h>
# include <mlx.h>
# include <math.h>

# define CYN	"\x1B[36m"
# define RESET	"\x1B[0m"

# define HEIGHT				650
# define WIDTH				650
# define SIZE 				HEIGHT * WIDTH

# define FDF 		   		0xFFFFFF
# define BACKGROUND			0x0
# define TEXT_COLOR			0xEAEAEA

# define FT_MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a > b ? a : b)
# define MOD(a) (a < 0 ? -a : a)

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
# define NUM_PAD_STAR		67

# define MAIN_PAD_ESC		53
# define MAIN_PAD_A			0
# define MAIN_PAD_S			1
# define MAIN_PAD_D			2
# define MAIN_PAD_F			3
# define MAIN_PAD_H			4
# define MAIN_PAD_G			5
# define MAIN_PAD_C			8
# define MAIN_PAD_Q			12
# define MAIN_PAD_W			13
# define MAIN_PAD_E			14
# define MAIN_PAD_P			35

# define MAIN_PAD_1			18
# define MAIN_PAD_2			19
# define MAIN_PAD_3			20
# define MAIN_PAD_4			21
# define MAIN_PAD_5			23

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

typedef struct		s_dot
{
	double			x;
	double			y;
	double			z;
	int 			color;
}					t_dot;

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
	int 			threads;
	int 			red;
	int 			green;
	int 			blue;
	int 			max_iteration;
	int 			iteration;
	int 			help;
	int 			pause;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				begin;
	int				end;
	double			alpha;
	double			beta;
	int				zoom;
	double			x_offset;
	double			y_offset;
	int				fdf;
	t_dot 			*dot;
	int 			m;
	double 			ratio;
	int 			size;
	int 			step;
	int				width;
	int				height;
	int 			polygon;
	int 			color_tmp;
	int 			coord;
}					t_data;

/*
**					control.c
*/
int					fr_hook_keydown(int key, t_data *data);

/*
**					control_fractal.c
*/
void				mandelbrot_up(t_data *data);
void				julia_up(t_data *data);
void				burning_ship_up(t_data *data);
void				mandelbar_up(t_data *data);
void				celtic_mandelbrot_up(t_data *data);

/*
**					control_mouse.c
*/
int					fr_mouse_press(int button, int x, int y, void *param);
int					fr_mouse_release(int button, int x, int y, void *param);
int					fr_mouse_move(int x, int y, void *param);

/*
**					fdf.c
*/
void				fdf_create(t_data *data);

/*
**					fractol.c
*/
void				mandelbrot(t_data *data);
void				julia(t_data *data);
void				burning_ship(t_data *data);
void				mandelbar(t_data *data);
void				celtic_mandelbrot(t_data *data);

/*
**					key_control.c
*/
void				fr_key_control(int key, t_data *data);

/*
**					main.c
*/
void				init_fdf(t_data *data);

/*
**					poligon.c
*/
void				render_plane(t_dot a, t_dot b, t_dot c, t_data *data);

/*
**					render.c
*/
void				fr_render(t_data *data);

/*
**					render_fdf.c
*/
void				render_map(t_data *data);

/*
**					threads.c
*/
void 				fr_creat_image(t_data *data);
void				check_runaway(t_data *data);
void				init_size(t_data *data);

/*
**					transforma.c
*/
t_dot				transformations(t_dot dot, t_data *data);

/*
**					utils.c
*/
void				print_error(char *message);
t_complex			init_complex(double re, double im);
void				fr_view_up(t_data *data);
void				render_menu5(t_data *data);

#endif
