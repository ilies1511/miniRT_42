#ifndef FT_ENGINE_H
# define FT_ENGINE_H

# include <MLX42.h>
# include <ft_tuple.h>
# include <ft_matrix.h>

typedef enum e_obj_type
{
	OBJ_DEFAULT = 0,
	OBJ_RAY,
	OBJ_SPHERE,
	OBJ_COUNT,
}	t_obj_type;

typedef struct s_obj
{
	t_matrix	transform;
	t_matrix	inverse;
	t_obj_type	type;
}	t_obj;

typedef struct s_sphere
{
	t_obj		base_obj;
	float		t;
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
	t_obj			base_obj;
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
t_obj		eng_new_obj(void);
t_sphere	eng_new_sphere(void);

// ft_engine/rays/intersect.c
void			eng_intersc_ray(t_intersc_arr *interscs, t_ray *ray, t_obj	*obj);
void			eng_sort_intersc(t_intersc_arr *interscs);
t_intersc		eng_add_intersc(t_intersc_arr *interscs, t_obj *obj, float t);
t_intersc_arr	eng_new_intersc_arr(void);

//cleanup
void			eng_free_intersc_arr(t_intersc_arr *interscs);

//ft_engine/rays/ray_hit.c
t_intersc		*eng_ray_hit(t_intersc_arr *interscs);
t_point			eng_ray_pos(t_ray ray, float time);

// ft_engine/rays/utils.c
bool	eng_eq_ray(t_ray r1, t_ray r2);

// ft_engine/rays/test.c
bool		test_eng_ray_pos(void);
bool		test_eng_intersc_ray_sphere(void);
bool		test_eng_ray_hit(void);

//ft_engine/objs/set_transform.c
void		eng_set_transform(t_obj *obj, t_matrix transform);
void		eng_ray_set_objs_inverse(t_ray *ray, t_obj *obj);

//ft_engine/objs/transform.c
void		eng_transform(t_obj *in, t_obj *ret);

//ft_engine/objs/test.c
bool		test_eng_trasform(void);
bool		test_transformation_matrices(void);

//ft_engine/reflect.c
t_vec	eng_reflect(t_vec vec, t_vec surface_normal);
bool	test_eng_reflect(void);

#endif //FT_ENGINE_H
