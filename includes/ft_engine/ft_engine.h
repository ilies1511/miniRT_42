#ifndef FT_ENGINE_H
# define FT_ENGINE_H


# include <MLX42.h>
# include <ft_tuple.h>

typedef struct s_ray
{
	t_point	origin;
	t_vec	direct;
}	t_ray;

typedef struct s_sphere
{
	t_point	origin;
	float	rad;
}	t_sphere;

typedef struct s_main	t_main;

// hooks.c
void		close_handler(void *main_data);
void		main_key_hooks(mlx_key_data_t keydata, void *main_data);

// ft_engine/reset.c
void		reset_img(t_main *m_data);
void		smoth_vanish(t_main *m_data);

// ft_engine/rays/init.c
t_ray		eng_new_ray(t_point origin, t_vec direct);
t_sphere	eng_new_sphere(void);

// ft_engine/rays/intersect.c
t_point		eng_ray_pos(t_ray ray, float time);
int			eng_intersects_ray_sphere(t_ray ray, t_sphere sph,
				float **ret_intersects);
// ft_engine/rays/test.c
bool		test_eng_ray_pos(void);
bool		test_eng_intersects_ray_sphere(void);
#endif //FT_ENGINE_H
