#ifndef FT_ENGINE_H
# define FT_ENGINE_H

# include <MLX42.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_colors.h>
# include <stdio.h>
# include <math.h>

typedef struct s_main	t_main;

typedef struct s_canvas
{
	size_t		width;
	size_t		height;
	mlx_image_t	*img;
}	t_canvas;

//canvas.c
t_canvas	eng_new_canvas(t_main *m_data, size_t width, size_t height);
void		eng_free_canvas(mlx_t *mlx, t_canvas *canvas);
void		reset_canvas(t_canvas *canvas);

typedef struct s_material
{
	t_fcolor	fcolor;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
}	t_material;

t_material	eng_new_material(void);

typedef enum e_obj_type
{
	OBJ_DEFAULT = 0,
	OBJ_RAY,
	OBJ_SPHERE,
	OBJ_LIGHT,
	OBJ_CAMERA,
	OBJ_COUNT,
}	t_obj_type;

typedef struct s_obj
{
	t_matrix	transform;
	t_matrix	inverse;
	t_obj_type	type;
}	t_obj;

//improvised camera
typedef struct s_camera
{
	t_obj	base_obj;
	t_point	p;
	double	wall_dist;
	double	wall_width;
	double	wall_height;
	double	fov_x;
	double	fov_y;
	double	aspect_ratio;
	double	wall_pixel_width;
	double	wall_pixel_height;
}	t_camera;

typedef struct s_sphere
{
	t_obj		base_obj;
	t_point		origin;
	float		rad;
	t_material	material;
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

typedef struct s_light
{
	t_obj			base_obj;
	t_point			origin;
	t_fcolor		intensity;
}	t_light;

t_light	eng_point_light(t_fcolor intensity, t_point position);

// hooks.c
void		close_handler(void *main_data);
void		main_key_hooks(mlx_key_data_t keydata, void *main_data);

// ft_engine/reset.c
void		reset_canvas(t_canvas *canvas);
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

// Compute Normal
t_vec		eng_normal_at(t_obj *object, t_point intersec_point);
int			test_normal_at(void);

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

// Lighting
t_fcolor	eng_lighting(t_material material, t_light light, t_point point, t_vec eyev, t_vec normalv);
bool		test_eng_lighting(void);

// Transformation view
t_matrix	sc_transforme_view(t_point from, t_point to, t_vec up);
bool		test_transformation_view_default(void);
bool		test_transformation_view_z(void);
bool		test_transformation_view_world(void);
bool		test_transformation_view_mixed(void);


#endif //FT_ENGINE_H
