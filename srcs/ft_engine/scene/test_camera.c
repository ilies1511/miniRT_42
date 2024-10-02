#include <ft_engine.h>
#include <ft_matrix.h>
#include <main.h>

bool test_eng_new_camera(void)
{
	bool ret = true;

	size_t hsize = 160;
	size_t vsize = 120;
	double field_of_view = M_PI / 2;

	t_camera c = eng_new_camera(hsize, vsize, field_of_view);

	if (c.width != hsize)
	{
		printf("Error: Expected c.width to be %zu, but got %zu. (%s: %d)\n",
			hsize, c.width, __FILE__, __LINE__);
		ret = false;
	}
	if (c.height != vsize)
	{
		printf("Error: Expected c.height to be %zu, but got %zu. (%s: %d)\n", vsize, c.height,
				__FILE__, __LINE__);
		ret = false;
	}
	if (!eq_f(c.fov_x, field_of_view))
	{
		printf("Error: Expected c.field_of_view to be %f, but got %f. (%s: %d)\n",
				field_of_view, c.fov_x, __FILE__, __LINE__);
		ret = false;
	}
	t_matrix identity = mtx_new_ident(MAT4X4);
	if (!mtx_eq(c.base_obj.transform, identity))
	{
		printf("Error: Expected c.transform to be identity matrix. (%s: %d)\n", __FILE__, __LINE__);
		ret = false;
	}

	hsize = 200;
	vsize = 125;
	field_of_view = M_PI / 2;
	c = eng_new_camera(hsize, vsize, field_of_view);
	double expected_pixel_size = 0.01;
	if (!eq_f(c.pixel_size, expected_pixel_size))
	{
		printf("Error: Expected c.pixel_width to be %f, but got %f. (%s: %d)\n",
			expected_pixel_size, c.pixel_size, __FILE__, __LINE__);
		ret = false;
	}

	hsize = 125;
	vsize = 200;
	field_of_view = M_PI / 2;
	c = eng_new_camera(hsize, vsize, field_of_view);
	expected_pixel_size = 0.01;
	if (!eq_f(c.pixel_size, expected_pixel_size))
	{
		printf("Error: Expected c.pixel_height to be %f, but got %f. (%s: %d)\n",
				expected_pixel_size, c.pixel_size, __FILE__, __LINE__);
		ret = false;
	}

	return ret;
}

bool test_eng_ray_for_pixel(void)
{
	bool ret = true;

	t_camera c = eng_new_camera(201, 101, M_PI / 2);
	t_ray r = eng_ray_for_pixel(c, 100, 50);
	t_point expected_origin = new_point(0, 0, 0);
	t_vec expected_direction = new_vec(0, 0, -1);
	if (!eq_t(r.origin, expected_origin))
	{
		printf("Error: Expected ray.origin to be point(0, 0, 0), but got "
			"point(%f, %f, %f). (%s: %d)\n", r.origin.x, r.origin.y, r.origin.z, __FILE__, __LINE__);
		ret = false;
	}
	if (!eq_t(r.direct, expected_direction))
	{
		printf("Error: Expected ray.direction to be vector(0, 0, -1), but got \
			vector(%f, %f, %f). (%s: %d)\n", r.direct.x, r.direct.y, r.direct.z, __FILE__, __LINE__);
		ret = false;
	}

	c = eng_new_camera(201, 101, M_PI / 2);
	r = eng_ray_for_pixel(c, 0, 0);
	expected_origin = new_point(0, 0, 0);
	expected_direction = new_vec(0.66519, 0.33259, -0.66851);
	if (!eq_t(r.origin, expected_origin))
	{
		printf("Error: Expected ray.origin to be point(0, 0, 0), but got \
				point(%f, %f, %f). (%s: %d)\n", r.origin.x, r.origin.y, r.origin.z, __FILE__, __LINE__);
		ret = false;
	}
	if (!eq_t(r.direct, expected_direction))
	{
		printf("Error: Expected ray.direction to be vector(0.66519, 0.33259, \
			-0.66851), but got vector(%f, %f, %f). (%s: %d)\n", r.direct.x,
			r.direct.y, r.direct.z, __FILE__, __LINE__);
		ret = false;
	}

	c = eng_new_camera(201, 101, M_PI / 2);
	t_matrix rotation = mtx_rotation_y(M_PI / 4);
	t_matrix translation = mtx_translate(0, -2, 5);
	t_matrix transform = mtx_mult_mm(rotation, translation);
	eng_set_transform((t_obj *)&c, transform);
	r = eng_ray_for_pixel(c, 100, 50);
	expected_origin = new_point(0, 2, -5);
	expected_direction = new_vec(sqrt(2) / 2, 0, -sqrt(2) / 2);
	if (!eq_t(r.origin, expected_origin))
	{
		printf("Error: Expected ray.origin to be point(0, 2, -5), but got \
			point(%f, %f, %f). (%s: %d)\n", r.origin.x, r.origin.y,
			r.origin.z, __FILE__, __LINE__);
		ret = false;
	}
	if (!eq_t(r.direct, expected_direction))
	{
		printf("Error: Expected ray.direction to be vector(%f, 0, %f), but got \
				vector(%f, %f, %f). (%s: %d)\n", sqrt(2) / 2, -sqrt(2) / 2,
				r.direct.x, r.direct.y, r.direct.z, __FILE__, __LINE__);
		ret = false;
	}
	return ret;
}
