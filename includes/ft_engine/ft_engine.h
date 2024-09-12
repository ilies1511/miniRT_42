#ifndef FT_ENGINE_H
# define FT_ENGINE_H


# include <MLX42.h>

typedef struct s_main	t_main;

// hooks.c
void	close_handler(void *main_data);
void	main_key_hooks(mlx_key_data_t keydata, void *main_data);

// ft_engine/reset.c
void	reset_img(t_main *m_data);
void	smoth_vanish(t_main *m_data);

#endif //FT_ENGINE_H
