#ifndef FT_ENGINE_H
# define FT_ENGINE_H

# include <MLX42.h>
# include <ft_tuple.h>

typedef enum e_obj_type
{
	OB_SPHERE = 1,
	OB_COUNT,
}	t_obj_type;

typedef struct s_obj
{
	t_obj_type	type;
	uint8_t		typed_data[];
}	t_obj;

typedef struct s_sphere
{
	t_obj_type	type; // always first so this can be cast to t_ob
	t_point		origin;
	float		rad;
}	t_sphere;

typedef struct s_intersc
{
	t_obj_type	type;
	float		t;
	t_obj		*obj;
}	t_intersc;

typedef struct s_intersc_arr
{
	size_t		count;
	t_intersc	*arr;
}	t_intersc_arr;

typedef struct s_ray
{
	t_point			origin;
	t_vec			direct;
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
int			eng_intersc_ray_sphere(t_ray *ray, t_sphere *sph);

t_intersc_arr	*eng_get_intersc(void);
void			eng_free_intersc(void);
void			eng_sort_intersc(void);
void			eng_new_intersc(t_obj *obj, float t);

//ft_engine/rays/ray_hit.c
t_intersc		*eng_ray_hit(void);

// ft_engine/rays/test.c
bool		test_eng_ray_pos(void);
bool		test_eng_intersc_ray_sphere(void);
bool		test_eng_ray_hit(void);
#endif //FT_ENGINE_H
