#ifndef FT_ENGINE_H
# define FT_ENGINE_H

# include <MLX42.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_colors.h>
# include <stdio.h>
# include <math.h>

# ifndef ERROR_BUF_LEN
#  define ERROR_BUF_LEN 50
# endif

typedef struct s_main	t_main;

typedef struct s_canvas
{
	size_t		width;
	size_t		height;
	t_uintcolor	*pixels;
}	t_canvas;

//canvas.c
t_canvas	eng_new_canvas(t_main *m_data, size_t width, size_t height);
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

//first t_obj_type must be same as t_shape_type
typedef enum e_obj_type
{
	OBJ_DEFAULT = 0,
	OBJ_SPHERE = 1,
	OBJ_PLANE = 2,
	OBJ_RAY,
	OBJ_LIGHT,
	OBJ_CAMERA,
	OBJ_COUNT,
}	t_obj_type;

// can be cast to t_obj_type
typedef enum e_shape_type
{
	SHAPE_DEFAULT = 0,
	SHAPE_SPHERE = 1,
	SHAPE_PLANE = 2,
}	t_shape_type;

const char *eng_type_to_str(t_obj_type type, char buf[ERROR_BUF_LEN]);
bool	eng_is_shape(t_obj_type type);

typedef struct s_obj
{
	t_matrix	transform;
	t_matrix	inverse;
	t_obj_type	type;
	t_material	material;
}	t_obj;

t_obj	*eng_alloc_shape(t_shape_type type);

// camera like in Book
typedef struct s_camera_book
{
	t_obj		base_obj;
	int			hsize; // horizontel size of the canvas
	int			vsize; // vertical size of the canvas
	double		field_of_view; // angle that descibes how much camera can see
	t_matrix	transform; // describes how the world should be oriented relative to the camera
}	t_camera_book;

//improvised camera
typedef struct s_camera
{
	t_obj	base_obj;
	double	fov_x;
	//double	fov_y; //lets keep this commented in case we need it
	size_t	width; //pixel count
	size_t	height;//pixel count
	double	pixel_size;//distance a signle pixel covers in 3d space
	// lets keep these 2 also for now
	//double	pixel_width;//distance a signle pixel covers in 3d space
	//double	pixel_height;//distance a signle pixel covers in 3d space
	double	half_wall_width;
	double	half_wall_height;
}	t_camera;

typedef struct s_sphere
{
	t_obj		base_obj;
	t_point		origin;
	float		rad;
}	t_sphere;

typedef struct s_intersc
{
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

typedef struct s_world
{
	t_obj		**objs;
	size_t		obj_count;
	t_light		*lights;
	size_t		light_count;
}	t_world;

typedef struct s_engine
{
	t_canvas	canvas;
	t_camera	camera;
	t_world		world;
}	t_engine;

typedef struct s_computation
{
	float	t;
	t_obj	*obj;
	t_point	point;
	t_point	over_point;
	t_vec	eye_v;
	t_vec	normal_v;
	bool	inside;
}	t_computation;

t_computation	eng_prepare_computation(t_intersc intersc, t_ray ray);
bool			test_prepare_computation(void);

//compute/shading.c
t_fcolor	eng_shade_hit(t_world world, t_computation comp);
bool		test_shading_outside_intersection(void);
t_fcolor	eng_color_at(t_world world, t_ray ray);
bool		test_eng_color_at(void);


t_light		eng_point_light(t_fcolor intensity, t_point position);

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
void			eng_ray_intersc_world(t_ray ray, t_world world, t_intersc_arr *interscs);

//cleanup
void			eng_free_intersc_arr(t_intersc_arr *interscs);

//ft_engine/rays/ray_hit.c
t_intersc		*eng_ray_hit(t_intersc_arr *interscs);
t_point			eng_ray_pos(t_ray ray, float time);

// ft_engine/rays/utils.c
bool		eng_eq_ray(t_ray r1, t_ray r2);

// Compute Normal
t_vec		eng_normal_at(t_obj *object, t_point intersec_point);
int			test_normal_at(void);

// ft_engine/rays/test.c
bool		test_eng_ray_pos(void);
bool		test_eng_intersc_ray_sphere(void);
bool		test_eng_ray_hit(void);
bool		test_eng_ray_intersc_world(void);

//ft_engine/objs/set_transform.c
void		eng_set_transform(t_obj *obj, t_matrix transform);
void		eng_ray_set_objs_inverse(t_ray *ray, t_obj *obj);

//ft_engine/objs/transform.c
void		eng_transform(t_obj *in, t_obj *ret);

//ft_engine/objs/test.c
bool		test_eng_trasform(void);
bool		test_transformation_matrices(void);

//ft_engine/world/add_obj_to_world.c
void		eng_add_obj_to_world(t_world *world, t_obj *obj);

// ft_engine/world/cleanup_world.c
void		cleanup_world(t_world *world);

//ft_engine/world/default_world.c
t_world		eng_default_world(void);

//ft_engine/reflect.c
t_vec		eng_reflect(t_vec vec, t_vec surface_normal);
bool		test_eng_reflect(void);

// Lighting
t_fcolor	eng_lighting(t_material material, t_light light, t_point point, t_vec eyev, t_vec normalv);
t_fcolor	eng_lighting_impr(t_material material, t_light light, t_point point, t_vec eyev, t_vec normalv, bool in_shadow);
bool		test_light_with_surface_shadow();
bool		test_eng_lighting(void);

//Shadow
bool	eng_is_shadowed(t_world world, t_point point);
bool	test_shadow();
bool	test2_shadow();
bool	test3_shadow();
bool	test4_shadow();

// init_engine.c
t_world		eng_new_world(void);
void		eng_init_engine(t_main *m_data);
void		cleanup_engine(t_engine *engine);

//camera.c
t_camera	eng_new_camera(size_t width, size_t height, double fov_x);
bool		test_eng_new_camera(void);
t_ray		eng_ray_for_pixel(t_camera camera, size_t x, size_t y);
bool		test_eng_ray_for_pixel(void);

void		eng_put_pixel(t_canvas canvas, size_t x, size_t y, t_fcolor color);
void		eng_render(t_camera camera, t_world world, t_canvas canvas);
t_fcolor	eng_pixel_at(t_canvas canvas, size_t x, size_t y, size_t width);
bool		test_eng_render(void);

// Transformation view
t_matrix	sc_transforme_view(t_point from, t_point to, t_vec up);
bool		test_transformation_view_default(void);
bool		test_transformation_view_z(void);
bool		test_transformation_view_world(void);
bool		test_transformation_view_mixed(void);

#endif //FT_ENGINE_H
