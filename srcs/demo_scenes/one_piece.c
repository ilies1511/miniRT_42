#include <ft_material.h>
#include <ft_scene.h>
#include <main.h>


static void	init_world(t_world *world)
{
	t_light		light_1 = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(1, 10, -1));
	t_plane		botom = eng_new_plane();
	t_plane		left_wall = eng_new_plane();

	//Botom
	botom.base_obj.material.pattern = pat_checker3d_pattern(fcolor_white(), fcolor_black());
	botom.base_obj.material.reflective = 0.3;
	botom.base_obj.material.specular = 0.98;
	botom.base_obj.material.diffuse = 0.7;
	eng_add_obj_to_world(world, (t_obj *)&botom);
	eng_add_obj_to_world(world, (t_obj *)&light_1);
	//Left Wall
	left_wall.base_obj.material.pattern = pat_checker3d_pattern(fcolor_white(), fcolor_black());
	left_wall.base_obj.material.reflective = 0.3;
	// left_wall.base_obj.material.specular = 0.98;
	left_wall.base_obj.material.diffuse = 0.2;
	eng_set_transform((t_obj *)&left_wall, mtx_rotation_z(M_PI_2));
	eng_add_obj_to_world(world, (t_obj *)&botom);
	eng_add_obj_to_world(world, (t_obj *)&left_wall);
	// eng_add_obj_to_world(world, (t_obj *)&light_1);
}
static void	init_camera(t_main *m_data)
{
t_camera	*camera;

	if (m_data->camera_type == USER_INPUT)
		return ;
	m_data->camera_type = PRESET;
camera = &(m_data->engine.camera);
*(camera) = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)camera, sc_transforme_view(new_point(0, 0, -10),
		new_point(0, 0, 0), new_vec(0, 1, 0)));
}

void	one_piece(void *main_data)
{
	t_main		*m_data = (t_main *)main_data;
	t_canvas	canvas = m_data->engine.canvas;
	t_world		*world;


	init_camera(m_data);
	world = &m_data->engine.world;
	init_world(world);
	//store_as_plain_ppm(m_data, "asd.ppm");
}
