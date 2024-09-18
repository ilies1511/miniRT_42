
#ifndef MAIN_H
# define MAIN_H

// for allowed functions
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

// MLX and libft
# include <MLX42.h>
# include <libft.h>

// our headers
# include <ft_tuple.h>
# include <ft_floats.h>
# include <ft_colors.h>
# include <ft_math.h>
# include <ft_matrix.h>
# include <ft_engine.h>
# include <mlx_interface.h>
# include <ppm_parser.h>
# include <parser_42.h>
# include <garbage_collector.h>
// for development but not allowed functions
// # include <....h>
# include <time.h>//used for tests to init rand()

# ifndef FOV_X
#  define FOV_X (60.0 / 360.0 * 2 * M_PI)
# endif
# ifndef FOV_Y
#  define FOV_Y (60.0 / 360.0 * 2 * M_PI)
# endif
# ifndef WIDTH
#  define WIDTH 500
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif

typedef int	t_fd;

typedef struct s_main
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_main;

typedef enum s_tuple_type
{
	COLOR,
	VECTOR,
	POINT
}	t_tuple_type;

// experiments
void	draw_projectile(void *main_data);
void	sphere_test(void *main_data);

// main.c

//******engine/******

// init_exit/init.c
void	init_hooks(t_main *m_data);
void	main_init(t_main *m_data);
t_main	*get_m_data();


// init_exit/at_exit.c
void	main_cleanup(t_main *m_data, uint8_t exit_stat);
void	ft_error(char *msg, char *file,
			  int line, uint8_t exit_stat);


#endif
