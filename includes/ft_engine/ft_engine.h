/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:18 by iziane            #+#    #+#             */
/*   Updated: 2024/10/10 15:51:44 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENGINE_H
# define FT_ENGINE_H

# include <MLX42.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_colors.h>
# include <stdio.h>
# include <math.h>

# ifndef REFLECTION_COUNT
#  error "REFLECTION_COUNT not defined by makefile"
# endif

# ifndef ERROR_BUF_LEN
#  define ERROR_BUF_LEN 50
# endif

// in case the user compiled with 'make SHADOWS=SOFT' instead of
// 'make SHADOWS=SMOOTH'
//#define HARD_SHADOWS

# ifdef SOFT_SHADOWS
#  undef SOFT_SHADOWS
#  define SMOOTH_SHADOWS
# endif //SOFT_SHADOWS

# ifndef HARD_SHADOWS
#  ifndef SMOOTH_SHADOWS
#   define SMOOTH_SHADOWS
#  endif //SMOOTH_SHADOWS
# endif //HARD_SHADOWS

# ifdef HARD_SHDOWS
#  undef SMOOTH_SHADOWS
# endif //HARD_SHADOWS

typedef struct s_main		t_main;
typedef struct s_obj		t_obj;
typedef t_obj *				t_obj_ptr __attribute__((may_alias));
typedef struct s_pattern	t_pattern;
typedef struct s_bump		t_bump;
typedef struct s_canvas
{
	size_t		width;
	size_t		height;
	t_uintcolor	*pixels;
}	t_canvas;

typedef struct s_cone_norm
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	y0;
	double	y1;
	double	sqrt_discriminant;
	double	two_a;
	double	t0;
	double	t1;
}			t_cone_norm;

//Lokal in Funktion selbst
// t_fcolor	result;
typedef struct s_cylinder_norm
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	y0;
	double	y1;
	double	sqrt_discriminant;
	double	two_a;
	double	t0;
	double	t1;
}			t_cylinder_norm;

//Lokal in Funktion selbst
// t_fcolor	result;
typedef struct s_lighting_norm
{
	t_fcolor	effective_color;
	t_fcolor	ambient_c;
	t_vec		lightv;
	t_vec		reflectv;
	t_tuple		light_direction;
	double		light_dot_normal;
	double		reflect_dot_eye;
	double		factor;
	t_fcolor	diffuse_c;
	t_fcolor	specular_c;
}				t_lighting_norm;

//canvas.c
t_canvas		eng_new_canvas(t_main *m_data, size_t width, size_t height);
void			reset_canvas(t_canvas *canvas);
typedef struct s_material
{
	t_pattern	*pattern;
	t_fcolor	fcolor;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
	t_bump		*bump;
}	t_material;

t_material		eng_new_material(void);

//first t_obj_type must be same as t_shape_type
typedef enum e_obj_type
{
	OBJ_DEFAULT = 0,
	OBJ_SPHERE = 1,
	OBJ_PLANE = 2,
	OBJ_CYLINDER = 3,
	OBJ_CONE = 4,
	OBJ_RAY,
	OBJ_LIGHT,
	OBJ_CAMERA,
	OBJ_PATTERN,
	OBJ_BUMP,
	OBJ_COUNT,
}	t_obj_type;

const char		*eng_type_to_str(t_obj_type type, char buf[ERROR_BUF_LEN]);
bool			eng_is_shape(t_obj_type type);

typedef struct s_obj
{
	t_matrix	transform;
	t_matrix	inverse;
	t_obj_type	type;
	t_material	material;
}__attribute__((may_alias))	t_obj;

typedef enum e_bump_type
{
	BUMP_DEFAULT = 0,
	BUMP_WAVE,
}	t_bump_type;

typedef struct s_bump
{
	t_obj			base_obj;
	t_bump_type		type;
} __attribute__((may_alias))	t_bump;

typedef enum e_pattern_type
{
	PAT_DEFAULT = 0,
	PAT_STRIPE,
	PAT_CHECKER_2D,
	PAT_CHECKER_3D,
	PAT_SQUARE_3D
}	t_pattern_type;

typedef struct s_pattern
{
	t_obj			base_obj;
	t_pattern_type	type;
	t_fcolor		*colors;
	size_t			color_count;
} __attribute__((may_alias))	t_pattern;

t_obj_ptr		eng_alloc_shape(t_obj_type type);

/*
 * width/height in pixels
 a pixel_size: distance a signle pixel covers in 3d space
*/
typedef struct s_camera
{
	t_obj	base_obj;
	double	fov_x;
	size_t	width;
	size_t	height;
	double	pixel_size;
	double	half_wall_width;
	double	half_wall_height;
} __attribute__((may_alias))	t_camera;

typedef struct s_sphere
{
	t_obj		base_obj;
} __attribute__((may_alias))	t_sphere;

typedef struct s_plane
{
	t_obj		base_obj;
} __attribute__((may_alias))	t_plane;

t_plane			eng_new_plane(void);

typedef struct s_cone
{
	t_obj		base_obj;
	double		min;
	double		max;
	bool		closed;
} __attribute__((may_alias))	t_cone;

t_cone			eng_new_cone(void);

typedef struct s_cylinder
{
	t_obj		base_obj;
	double		min;
	double		max;
	bool		closed;
} __attribute__((may_alias))	t_cylinder;

t_cylinder		eng_new_cylinder(void);

typedef struct s_intersc
{
	double		t;
	t_obj_ptr	obj;
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
} __attribute__((may_alias))	t_ray;

typedef struct s_refracted_color_norm
{
	double		cos_vecs;
	double		ratio;
	double		sin_sqr;
	double		cos_val;
	t_vec		direct;
	t_ray		refract;
	t_fcolor	color;
}	t_refracted_color_norm;

typedef enum e_light_type
{
	POINT_LIGHT,
	SPOT_LIGHT,
}	t_light_type;

typedef struct s_light
{
	t_obj			base_obj;
	t_point			origin;
	t_fcolor		intensity;
	double			radius;
	t_light_type	type;
	t_vec			direct;
	double			cosine_range;
} __attribute__((may_alias))	t_light;

typedef struct s_shade_hit_norm
{
	int			i;
	t_fcolor	color;
	t_fcolor	surface;
	t_fcolor	reflected;
	t_fcolor	refracted;
	t_light		light;
	double		reflactance;
	bool		in_shadow;
}				t_shade_hit_norm;

typedef struct s_world
{
	t_obj_ptr	*objs;
	size_t		obj_count;
	t_light		*lights;
	size_t		light_count;
	t_fcolor	ambient42;
}	t_world;

typedef struct s_engine
{
	t_canvas	canvas;
	t_camera	camera;
	t_world		world;
}	t_engine;

typedef struct s_computation
{
	double		t;
	t_obj_ptr	obj;
	t_point		point;
	t_point		over_point;
	t_point		under_point;
	t_vec		eye_v;
	t_vec		normal_v;
	bool		inside;
	t_vec		reflection;
	double		n1;
	double		n2;
	t_fcolor	color_at;
}	t_computation;

t_computation	eng_prepare_computation(t_intersc hit, t_ray ray,
					t_intersc_arr interscs);

//compute/shading.c
void			calculate_color(t_shade_hit_norm *n);
bool			in_light_fov(t_light light, t_point point);
t_light			adjust_light(t_light light);
t_fcolor		eng_ambient42(t_world world, t_fcolor color_at);
t_fcolor		eng_shade_hit42(t_world world, t_computation comp, \
					size_t remaining_reflects);
t_fcolor		eng_shade_hit(t_world world, t_computation comp,
					size_t remaining_reflects);
t_fcolor		eng_color_at(t_world world, t_ray ray,
					size_t remaining_reflects);

t_light			eng_point_light(t_fcolor intensity, t_point position);
t_light			eng_spot_light(t_fcolor intensity, t_point position,
					t_point look_at, double fov_360);

// hooks.c
void			close_handler(void *main_data);
void			main_key_hooks(mlx_key_data_t keydata, void *main_data);

// ft_engine/reset.c
void			reset_canvas(t_canvas *canvas);

// ft_engine/rays/init.c
t_ray			eng_new_ray(t_point origin, t_vec direct);
t_obj			eng_new_obj(void);
t_sphere		eng_new_sphere(void);
t_sphere		eng_new_glass_sphere(void);
t_cylinder		eng_new_cylinder(void);

// ft_engine/rays/intersect.c
void			eng_intersc_ray(t_intersc_arr *interscs, t_ray ray,
					t_obj_ptr obj);
void			eng_sort_intersc(t_intersc_arr *interscs);
t_intersc		eng_add_intersc(t_intersc_arr *interscs, t_obj_ptr obj, \
					double t);
t_intersc_arr	eng_new_intersc_arr(void);
void			eng_ray_intersc_world(t_ray ray, t_world world,
					t_intersc_arr *interscs);
void			eng_intersc_ray_cylinder(t_intersc_arr *intersecs, t_ray ray,
					t_cylinder *cylinder);

//Intersect Ray-Cone
void			eng_intersc_ray_cone(t_intersc_arr *intersecs, t_ray ray,
					t_cone *cone);
void			add_intersects(t_cone_norm *n, t_intersc_arr *intersecs, \
					t_ray ray, t_cone *cone);
void			swap_double_co(t_cone_norm *n);
void			cal_intesects(t_cone_norm *n);
void			cal_abc(t_cone_norm *n, t_ray ray);
void			cal_disc_sqrt(t_cone_norm *n);
void			eng_intersc_ray_cone_caps(t_intersc_arr *intersecs, t_ray ray, \
						t_cone *cone);
bool			check_cap_cone(t_ray ray, double t, double y);
//End Cone

t_vec			compute_normal_cone(t_cone *cone, t_point object_point);
t_vec			compute_normal_cylinder(t_cylinder *cylinder,
					t_point object_point);

//Normal_at_types
t_vec			compute_normal_sphere(t_point object_point);
t_vec			compute_normal_plane(t_point object_point);
t_vec			compute_normal_cylinder(t_cylinder *cylinder, \
					t_point object_point);
t_vec			compute_normal_cone(t_cone *cone, t_point object_point);

//cleanup
void			eng_free_intersc_arr(t_intersc_arr *interscs);

//ft_engine/rays/ray_hit.c
t_intersc		*eng_ray_hit(t_intersc_arr *interscs);
t_point			eng_ray_pos(t_ray ray, double time);

// ft_engine/rays/utils.c
bool			eng_eq_ray(t_ray r1, t_ray r2);

// Compute Normal
t_vec			eng_normal_at(t_obj_ptr object, t_point intersec_point);

//ft_engine/objs/set_transform.c
void			eng_set_transform(t_obj_ptr obj, t_matrix transform);
void			eng_ray_set_objs_inverse(t_ray *ray, t_obj_ptr obj);

//ft_engine/objs/transform.c
void			eng_transform(t_obj_ptr in, t_obj_ptr ret);

//ft_engine/world/add_obj_to_world.c
void			eng_add_obj_to_world(t_world *world, t_obj_ptr obj);

//ft_engine/world/default_world.c
t_world			eng_default_world(void);

//print_world
void			eng_print_light(char *str, t_light light);
void			eng_print_world(t_world world);

// Lighting
t_fcolor		eng_lighting(t_computation comp, t_light light, bool in_shadow);
t_fcolor		eng_lighting42(t_computation comp, t_light light);
t_fcolor		eng_lighting42(t_computation comp, t_light light);
// t_fcolor	eng_lighting(t_obj obj, t_material material, t_light light,
//					t_point point, t_vec eyev, t_vec normalv, bool in_shadow);
// t_fcolor	eng_lighting(t_obj obj, t_computation comp, t_light light,
//				bool in_shadow);
// t_fcolor	eng_lighting(t_obj obj, t_computation *comp, t_light light,
//				bool in_shadow);

//Shadow
bool			eng_is_shadowed(t_world world, t_point point, t_light light);

// init_engine.c
t_world			eng_new_world(void);
void			eng_init_engine(t_main *m_data, int ac, char *av[]);
void			cleanup_engine(t_engine *engine);

//camera.c
t_camera		eng_new_camera(size_t width, size_t height, double fov_x);
t_ray			eng_ray_for_pixel(t_camera camera, size_t x, size_t y);

size_t			eng_put_pixel(t_canvas canvas, size_t x, size_t y,
					t_fcolor color);
void			eng_render(t_camera camera, t_world world, t_canvas canvas);

// Transformation view
t_matrix		sc_transforme_view(t_point from, t_point to, t_vec up);
#endif //FT_ENGINE_H
