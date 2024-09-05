
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

// for development but not allowed functions

# ifndef WIDTH
#  define WIDTH 2000
# endif
# ifndef HEIGHT
#  define HEIGHT 1500
# endif

# ifndef BLACK
#  define BLACK 0xFF000000
# endif
# ifndef RED
#  define RED 0xFF0000FF
# endif
# ifndef GREEN
#  define GREEN 0xFF00FF00
# endif
# ifndef BLUE
#  define BLUE 0xFFFF0000
# endif
# ifndef MAGENTA
#  define MAGENTA 0xFFFF00FF
# endif
# ifndef YELLOW
#  define YELLOW 0xFF00FFFF
# endif
# ifndef WHITE
#  define WHITE 0xFFFFFFFF
# endif
# ifndef CYAN
#  define CYAN 0xFF00FFFF
# endif
# ifndef PURPLE
#  define PURPLE 0xFFFF00A0
# endif
# ifndef ORANGE
#  define ORANGE 0xFF0080FF
# endif
# ifndef TEAL
#  define TEAL 0xFF808000
# endif
# ifndef PINK
#  define PINK 0xFFFF80FF
# endif
# ifndef LIME
#  define LIME 0xFF80FF00
# endif
# ifndef LIGHT_GREY
#  define LIGHT_GREY 0xFFD3D3D3
# endif
# ifndef DARK_GREY
#  define DARK_GREY 0xFFA9A9A9
# endif

typedef struct s_main
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_main;

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
