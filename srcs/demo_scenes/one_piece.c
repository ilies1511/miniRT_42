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

static void	create_pink_sph(t_world *world)
{
	t_sphere	sph1;
	t_sphere	sph2;

	sph1 = eng_new_sphere();
	sph2 = eng_new_sphere();
	sph1.base_obj.material.reflective = 0.5;
	eng_set_transform((t_obj_ptr) & sph1, mtx_translate(2, 3, 2));
	eng_set_transform((t_obj_ptr) & sph2, mtx_translate(2, 3, 2));
	sph2.base_obj.material.refractive_index = 1.00029;
	sph2.base_obj.material.reflective = 0.5;
	sph2.base_obj.material.transparency = 1.0;
	sph1.base_obj.material.pattern = pat_checker3d_pattern(
			fcolor_white(), fcolor_black());
	eng_set_transform((t_obj_ptr) & sph1.base_obj.material.pattern->base_obj,
		mtx_rotation_axis_angle(norm(new_vec(1, 1, 1)), M_PI_4 - 0.123));
	eng_set_transform((t_obj_ptr) & sph1.base_obj.material.pattern->base_obj,
		mtx_scale(0.2, 0.2, 0.2));
	eng_add_obj_to_world(world, (t_obj_ptr) & sph1);
	eng_add_obj_to_world(world, (t_obj_ptr) & sph2);
}

static void	room(t_world *world)
{
	t_plane		botom;
	t_plane		left_wall;
	t_light		light_1;

	botom = eng_new_plane();
	left_wall = eng_new_plane();
	botom.base_obj.material.pattern = pat_checker3d_pattern(
			fcolor_white(), fcolor_black());
	botom.base_obj.material.reflective = 0.3;
	botom.base_obj.material.specular = 0.98;
	botom.base_obj.material.diffuse = 0.7;
	eng_add_obj_to_world(world, (t_obj_ptr) & botom);
	left_wall.base_obj.material.pattern = pat_checker3d_pattern(
			fcolor_white(), fcolor_black());
	left_wall.base_obj.material.reflective = 0.3;
	left_wall.base_obj.material.diffuse = 0.2;
	eng_set_transform((t_obj *)&left_wall, mtx_rotation_z(M_PI_2));
	eng_add_obj_to_world(world, (t_obj_ptr) & botom);
	eng_add_obj_to_world(world, (t_obj_ptr) & left_wall);
	light_1 = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(1, 10, -1));
	eng_add_obj_to_world(world, (t_obj_ptr) & light_1);
}

static void	init_world(t_world *world)
{
	int			i;
	t_cylinder	cyl;

	i = -1;
	while (++i < 6)
	{
		cyl = eng_new_cylinder();
		cyl.closed = true;
		cyl.base_obj.material.reflective = 0.3;
		cyl.base_obj.material.pattern = pat_checker3d_pattern(
				new_fcolor(122.0 / 255, 33.0 / 255, 74.0 / 255, 1),
				new_fcolor(75.0 / 255, 0, 130.0 / 255, 1));
		eng_set_transform((t_obj_ptr) & cyl, mtx_translate(2 + i, 0, 20));
		eng_set_transform((t_obj_ptr) & cyl.base_obj.material.pattern->base_obj,
			mtx_scale(0.1, 0.1, 0.1));
		cyl.base_obj.material.fcolor = new_fcolor(215.0 / 255.0, 215.0 / 255, \
			215.0 / 255, 1);
		eng_set_transform((t_obj_ptr) & cyl, mtx_scale(2, 2, 2));
		cyl.base_obj.material.specular = 0.98;
		cyl.base_obj.material.reflective = 0.3;
		eng_add_obj_to_world(world, (t_obj_ptr) & cyl);
	}
	create_pink_sph(world);
	room(world);
}

static void	init_camera(t_main *m_data)
{
	t_camera	*camera;

	if (m_data->camera_type == USER_INPUT)
		return ;
	m_data->camera_type = PRESET;
	camera = &(m_data->engine.camera);
	*(camera) = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)camera, sc_transforme_view(
			new_point(1.5, 1, -5.5),
			new_point(2, 5, 2), new_vec(0, 1, 0)));
}

void	one_piece(void *main_data)
{
	t_main		*m_data;
	t_world		*world;

	m_data = (t_main *)main_data;
	init_camera(m_data);
	world = &m_data->engine.world;
	init_world(world);
}
