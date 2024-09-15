#ifndef FT_ENGINE_H
# define FT_ENGINE_H

# include <MLX42.h>
# include <ft_tuple.h>

typedef struct s_sphere
{
	t_point	origin;
	float	rad;
}	t_sphere;

typedef enum e_obj_type
{
	OB_SPHERE = 1,
	OB_COUNT,
}	t_obj_type;

typedef struct s_intersc
{
	float		t;
	t_obj_type	type;
	void		*obj;
}	t_intersc;

typedef struct s_ray
{
	t_point			origin;
	t_vec			direct;
	t_intersc		*interscs;
	int				interscs_count;
}	t_ray;

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
int			eng_interscs_ray_sphere(t_ray *ray, t_sphere *sph);
void		eng_sort_interscs(t_ray *ray);

// ft_engine/rays/test.c
bool		test_eng_ray_pos(void);
bool		test_eng_interscs_ray_sphere(void);
#endif //FT_ENGINE_H
