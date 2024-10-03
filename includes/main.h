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
# include <limits.h>

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
# include <ppm_parser.h>
# include <parser_42.h>
# include <garbage_collector.h>
# include <ft_patterns.h>
# include <ft_reflection.h>
# include <ft_refraction.h>
// for development but not allowed functions
// # include <....h>
# include <time.h>//used for tests to init rand()

# ifndef FOV_X
#  define FOV_X (60.0 / 360.0 * 2 * M_PI)
# endif

# ifndef FOV_Y
#  define FOV_Y (60.0 / 360.0 * 2 * M_PI)
# endif

# ifndef ASPECT_RATIO
//#  define ASPECT_RATIO (16.0 / 9.0)
#  define ASPECT_RATIO 1.7777777777777777
# endif

# ifndef WIDTH
#  define WIDTH 1000
# endif

# ifndef HEIGHT
#  define HEIGHT ((size_t)(WIDTH / ASPECT_RATIO))
# endif

# ifndef WALL_DIST
#  define WALL_DIST 1
# endif

# ifndef RANDOM_BIN_FILE
#  define RANDOM_BIN_FILE "rand_bin_data.bin"
# endif //RANDOM_BIN_FILE

typedef int	t_fd;

typedef struct s_cleanup
{
	mlx_image_t	*mlx_img;
	int			fd;
}	t_cleanup;

// ac(argument count) can be removed later
typedef struct s_main
{
	mlx_t		*mlx;
	t_engine	engine;
	t_cleanup	cleanup_data;
	int			ac;
}	t_mait;

typedef enum s_tuple_type
{
	COLOR,
	VECTOR,
	POINT
}	t_tuple_type;

double	ft_rand(void);

// experiments
void	draw_projectile(void *main_data);
void	sphere_test(void *main_data);

// init_exit/init.c
void	init_hooks(t_main *m_data);
void	main_init(t_main *m_data, int ac, char *av[]);
t_main	*get_m_data(void);

// init_exit/at_exit.c
void	main_cleanup(t_main *m_data, uint8_t exit_stat);
void	ft_error(char *msg, char *file,
			int line, uint8_t exit_stat);
#endif
