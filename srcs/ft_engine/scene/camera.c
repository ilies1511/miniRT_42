#include <ft_engine.h>
#include <main.h>

// later we can change the arguments so we can for example
// enforce an aspect ratio set as macro and/or a width set by a macro
t_camera	eng_new_camera(size_t width, size_t height, double fov_x)
{
	t_camera	camera;
	double		aspect_ratio;
	double		half_view;

	aspect_ratio = width / (float)height;

	camera.base_obj = eng_new_obj();
	camera.base_obj.transform = mtx_new_ident(MAT4X4);//not needed but to highliht written out
	camera.base_obj.type = OBJ_CAMERA;

	camera.width = width;
	camera.height = height;

	camera.fov_x = fov_x;
	//camera.fov_y = 2 * atan(tan(fov_x / 2) / aspect_ratio);lets keep this line commented in case we need it

	//camera.half_wall_width = tan(camera.fov_x / 2) * WALL_DIST;lets keep this line commented in case we need it
	//camera.half_wall_height = tan(camera.fov_y / 2) * WALL_DIST;lets keep this line commented in case we need it
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

	camera.pixel_width = camera.half_wall_width * 2 / width;
	camera.pixel_height = camera.half_wall_height * 2 / height;
	return (camera);
}

bool test_eng_new_camera(void)
{
    bool success = true;

    // Scenario 1: Constructing a camera
    {
        size_t hsize = 160;
        size_t vsize = 120;
        double field_of_view = M_PI / 2;

        t_camera c = eng_new_camera(hsize, vsize, field_of_view);

        if (c.width != hsize)
		{
            printf("Error: Expected c.width to be %zu, but got %zu. (%s: %d)\n",
				hsize, c.width, __FILE__, __LINE__);
            success = false;
        }
        if (c.height != vsize) {
            printf("Error: Expected c.height to be %zu, but got %zu. (%s: %d)\n", vsize, c.height, __FILE__, __LINE__);
            success = false;
        }
        if (!eq_f(c.fov_x, field_of_view)) {
            printf("Error: Expected c.field_of_view to be %f, but got %f. (%s: %d)\n", field_of_view, c.fov_x, __FILE__, __LINE__);
            success = false;
        }

        t_matrix identity = mtx_new_ident(MAT4X4);
        if (!mtx_eq(c.base_obj.transform, identity)) {
            printf("Error: Expected c.transform to be identity matrix. (%s: %d)\n", __FILE__, __LINE__);
            success = false;
        }
    }

    // Scenario 2: The pixel size for a horizontal canvas
    {
        size_t hsize = 200;
        size_t vsize = 125;
        double field_of_view = M_PI / 2;

        t_camera c = eng_new_camera(hsize, vsize, field_of_view);

        double expected_pixel_size = 0.01;
        if (!eq_f(c.pixel_width, expected_pixel_size)) {
            printf("Error: Expected c.pixel_width to be %f, but got %f. (%s: %d)\n", expected_pixel_size, c.pixel_width, __FILE__, __LINE__);
            success = false;
        }
    }

    // Scenario 3: The pixel size for a vertical canvas
    {
        size_t hsize = 125;
        size_t vsize = 200;
        double field_of_view = M_PI / 2;

        t_camera c = eng_new_camera(hsize, vsize, field_of_view);

        double expected_pixel_size = 0.01;
        if (!eq_f(c.pixel_height, expected_pixel_size)) {
            printf("Error: Expected c.pixel_height to be %f, but got %f. (%s: %d)\n", expected_pixel_size, c.pixel_height, __FILE__, __LINE__);
            success = false;
        }
    }

    return success;
}

