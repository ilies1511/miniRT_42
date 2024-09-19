#include <main.h>

typedef struct s_camera
{
	t_point	p;
	t_vec	direct;
	double	wall_dist;
	double	wall_width;
	double	wall_height;
	double	fov_x;
	double	fov_y;
	double	aspect_ratio;
}	t_camera;

t_camera	eng_new_camera(double fov_x, t_point p, t_vec direct, double wall_dist)
{
	t_camera camera;

	camera.p = p;
	camera.direct = direct;
	camera.fov_x = fov_x;
	camera.aspect_ratio = ASPECT_RATIO;
	camera.fov_y = 2 * atan(tan(fov_x / 2) / ASPECT_RATIO);
	camera.wall_width = 2.0 * tan(camera.fov_x / 2) * camera.wall_dist;
	camera.wall_height = 2.0 * tan(camera.fov_y / 2) * camera.wall_dist;

	return (camera);
}


void	pixel_to_vall(t_canvas *canvas, t_camera *camera, size_t pixel_x, size_t pixel_y,
			size_t *wall_x, size_t *wall_y)
{
}

void	sphere_test(void *main_data)
{
	t_ray		ray = eng_new_ray(new_point(0, 0, -5), new_vec(0, 0, 1));
	t_point		wall_p = new_point(0, 0, 10);
	t_sphere	sph = eng_new_sphere();
}
