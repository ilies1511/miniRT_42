
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

// for development but not allowed functions
// # include <....h>

# ifndef WIDTH
#  define WIDTH 2000
# endif
# ifndef HEIGHT
#  define HEIGHT 1500
# endif

typedef struct s_main
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_main;

// experiments

void	draw_projectile(void *main_data);

// main.c

//******engine/******
// engine/reset.c
void	reset_img(t_main *m_data);

// init_exit/init.c
void	init_hooks(t_main *m_data);
void	main_init(t_main *m_data);

// init_exit/at_exit.c
void	main_cleanup(t_main *m_data, uint8_t exit_stat);
void	ft_error(t_main *m_data, char *msg, char *file,
			  int line, uint8_t exit_stat);

// hooks.c
void	close_handler(void *main_data);
void	main_key_hooks(mlx_key_data_t keydata, void *main_data);

#endif
