/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:12 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:36:14 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_material.h>
#include <ft_scene.h>
#include <main.h>

static void	create_pink_sph(t_world *world, double x, double y, double z)
{
	t_sphere	sph1;
	t_sphere	sph2;

	sph1 = eng_new_sphere();
	sph2 = eng_new_sphere();
	sph1.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj_ptr) & sph1, mtx_translate(2, 3, 2));
	eng_set_transform((t_obj_ptr) & sph2, mtx_translate(2, 3, 2));
	// eng_set_transform((t_obj *)&sph1, mtx_scale(3, 3, 3));
	sph2.base_obj.material.refractive_index = 1.00029;
	sph2.base_obj.material.reflective = 0.5;
	sph2.base_obj.material.transparency = 1.0;
	sph1.base_obj.material.pattern = pat_checker3d_pattern(fcolor_white(), fcolor_black());
	eng_set_transform((t_obj_ptr) & sph1.base_obj.material.pattern->base_obj, mtx_rotation_axis_angle(norm(new_vec(1, 1, 1)), M_PI_4 - 0.123));
	eng_set_transform((t_obj_ptr) & sph1.base_obj.material.pattern->base_obj, mtx_scale(0.2, 0.2, 0.2));
	// eng_add_obj_to_world(world, (t_obj_ptr)&sph1);
	// eng_add_obj_to_world(world, (t_obj_ptr)&sph2);
	eng_add_obj_to_world(world, (t_obj_ptr) & sph1);
	eng_add_obj_to_world(world, (t_obj_ptr) & sph2);

}

static void	create_pink_cyl(t_cylinder *cyl, t_world *world, double x, double y, double z)
{
	// cyl->min = -0.5;
	// cyl->max = ;
	cyl->closed = true;
	cyl->base_obj.material.reflective = 0.3;
	cyl->base_obj.material.pattern = pat_checker3d_pattern(new_fcolor(122.0 / 255, 33.0 / 255, 74.0 / 255, 1), new_fcolor(75.0 / 255,0,130.0 / 255, 1));
	eng_set_transform((t_obj *)cyl, mtx_translate(x, y, z));
	eng_set_transform((t_obj_ptr )&cyl->base_obj.material.pattern->base_obj, mtx_scale(0.1, 0.1, 0.1));
	cyl->base_obj.material.fcolor = new_fcolor(215.0 / 255.0, 215.0 / 255, \
		215.0 / 255, 1);
	eng_set_transform((t_obj_ptr )cyl, mtx_scale(2, 2, 2));
	// cyl->base_obj.material.fcolor = new_fcolor(148.0 / 255.0, 79.0 / 255, \
	// 	110.0 / 255, 1);
	// eng_set_transform((t_obj *)cyl, mtx_translate(2, 0, 20));
	// cyl->base_obj.material.diffuse = 0.7;
	cyl->base_obj.material.specular = 0.98;
	// cyl->base_obj.material.transparency = 0;
	cyl->base_obj.material.reflective = 0.3;
	// cyl->base_obj.material.refractive_index = 1.33;
	// return (cyl);
	eng_add_obj_to_world(world, (t_obj *)cyl);
}

static void	init_world(t_world *world)
{
	t_light		light_1 = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(1, 10, -1));
	t_plane		botom = eng_new_plane();
	t_plane		left_wall = eng_new_plane();
	t_cylinder	cyl;
	t_cylinder	cyl2;
	t_cylinder	cyl3;
	t_cylinder	cyl4;
	t_cylinder	cyl5;
	t_cylinder	cyl6;

	cyl = eng_new_cylinder();
	cyl2 = eng_new_cylinder();
	cyl3 = eng_new_cylinder();
	cyl5 = eng_new_cylinder();
	cyl6 = eng_new_cylinder();
	create_pink_sph(world, 20, 20, 20);
	create_pink_cyl(&cyl, world, 2, 0, 20);
	create_pink_cyl(&cyl2, world, 3, 0, 20);
	create_pink_cyl(&cyl3, world, 4, 0, 20);
	create_pink_cyl(&cyl4, world, 5, 0, 20);
	create_pink_cyl(&cyl5, world, 6, 0, 20);
	create_pink_cyl(&cyl6, world, 7, 0, 20);
	// cyl = eng_new_cylinder();
	// cyl.min = -0.5;
	// cyl.max = 4;
	// cyl.closed = true;
	// cyl.base_obj.material.reflective = 0.3;
	// cyl.base_obj.material.pattern = pat_checker3d_pattern(new_fcolor(122.0 / 255, 33.0 / 255, 74.0 / 255, 1), new_fcolor(75.0 / 255,0,130.0 / 255, 1));
	// eng_set_transform((t_obj *)cyl.base_obj.material.pattern, mtx_scale(0.1, 0.1, 0.1));
	// cyl.base_obj.material.fcolor = new_fcolor(215.0 / 255.0, 215.0 / 255, \
	// 	215.0 / 255, 1);
	// // cyl.base_obj.material.fcolor = new_fcolor(148.0 / 255.0, 79.0 / 255, \
	// // 	110.0 / 255, 1);
	// eng_set_transform((t_obj *)&cyl, mtx_translate(2, 0, 20));
	// // cyl.base_obj.material.diffuse = 0.7;
	// cyl.base_obj.material.specular = 0.98;
	// // cyl.base_obj.material.transparency = 0;
	// cyl.base_obj.material.reflective = 0.3;
	// // cyl.base_obj.material.refractive_index = 1.33;
	// //Botom
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
	// eng_add_obj_to_world(world, (t_obj *)&cyl);
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
	eng_set_transform((t_obj *)camera, sc_transforme_view(new_point(1.5,1,-5.5),
		new_point(2, 5, 2), new_vec(0, 1, 0)));
	// eng_set_transform((t_obj *)camera, sc_transforme_view(new_point(0, 0, -10),
	// 	new_point(0, 0, 0), new_vec(0, 1, 0)));
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
