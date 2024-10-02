#include <ft_engine.h>
#include <ft_matrix.h>
#include <main.h>

// later we can change the arguments so we can for example
// enforce an aspect ratio set as macro and/or a width set by a macro
t_camera	eng_new_camera(size_t width, size_t height, double fov_x)
{
	t_camera	camera;
	double		aspect_ratio;
	double		half_view;

	aspect_ratio = width / (double)height;
	camera.base_obj = eng_new_obj();
	camera.base_obj.transform = mtx_new_ident(MAT4X4);
	camera.base_obj.type = OBJ_CAMERA;
	camera.width = width;
	camera.height = height;
	camera.fov_x = fov_x;
	half_view = tan(camera.fov_x / 2);
	if (aspect_ratio >= 1)
	{
		camera.half_wall_width = half_view;
		camera.half_wall_height = half_view / aspect_ratio;
	}
	else
	{
		camera.half_wall_width = half_view * aspect_ratio;
		camera.half_wall_height = half_view;
	}
	camera.pixel_size = camera.half_wall_width * 2 / camera.width;
	return (camera);
}

// canvas at z = -1
t_ray	eng_ray_for_pixel(t_camera camera, size_t x, size_t y)
{
	double	world_x;
	double	world_y;
	t_point	pixel3d;
	t_point	origin;
	t_vec	direct;

	world_x = camera.half_wall_width - (x + 0.5) * camera.pixel_size;
	world_y = camera.half_wall_height - (y + 0.5) * camera.pixel_size;
	pixel3d = mtx_mult_mt(camera.base_obj.inverse,
			new_point(world_x, world_y, -1));
	origin = mtx_mult_mt(camera.base_obj.inverse, new_point(0, 0, 0));
	direct = norm(sub_t(pixel3d, origin));
	return (eng_new_ray(origin, direct));
}
