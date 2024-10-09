/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_demo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:36:18 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:36:20 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_material.h>
#include <ft_scene.h>

static void	light_mid_left(t_world *world)
{
	t_sphere	sph_mid;
	t_sphere	sph_left;
	t_light		light;

	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(9, 8, -5));
	light.radius = 0.4;
	eng_add_obj_to_world(world, (t_obj_ptr) & light);
	sph_mid = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr) & sph_mid, mtx_translate(-0.5, 2, -3));
	sph_mid.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_mid.base_obj.material.diffuse = 0.7;
	sph_mid.base_obj.material.specular = 0.3;
	sph_mid.base_obj.material.transparency = 0;
	sph_mid.base_obj.material.reflective = 0.4;
	sph_mid.base_obj.material.refractive_index = 1.33;
	eng_add_obj_to_world(world, (t_obj_ptr) & sph_mid);
	sph_left = eng_new_sphere();
	eng_set_transform((t_obj_ptr) & sph_left, mtx_translate(-1.5, 0.33, -0.75));
	eng_set_transform((t_obj_ptr) & sph_left, mtx_scale(0.33, 0.33, 0.33));
	sph_left.base_obj.material.fcolor = new_fcolor(1, 0.83984375, 0, 1);
	sph_left.base_obj.material.diffuse = 0.7;
	sph_left.base_obj.material.specular = 0.98;
	sph_left.base_obj.material.reflective = 0.7;
	eng_add_obj_to_world(world, (t_obj_ptr) & sph_left);
}

static void	cyl_right(t_world *world)
{
	t_cylinder	cyl;
	t_sphere	sph_right;

	sph_right = eng_new_glass_sphere();
	eng_set_transform((t_obj_ptr) & sph_right, mtx_translate(1.5, 0.5, -0.5));
	eng_set_transform((t_obj_ptr) & sph_right, mtx_scale(0.5, 0.5, 0.5));
	sph_right.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	sph_right.base_obj.material.diffuse = 0.7;
	sph_right.base_obj.material.specular = 0.3;
	sph_right.base_obj.material.pattern = pat_checker3d_pattern(
			new_fcolor(1, 1, 1, 1), new_fcolor(0, 0, 0, 1));
	eng_set_transform((t_obj_ptr)sph_right.base_obj.material.pattern,
		mtx_scale(0.1, 0.1, 0.1));
	eng_add_obj_to_world(world, (t_obj_ptr) & sph_right);
	cyl = eng_new_cylinder();
	cyl.min = -0.5;
	cyl.max = 2;
	cyl.closed = true;
	cyl.base_obj.material.reflective = 0.3;
	eng_set_transform((t_obj_ptr) & cyl, mtx_translate(2, 0, -2));
	eng_add_obj_to_world(world, (t_obj_ptr) & cyl);
}

static void	init_world(t_world *world)
{
	t_plane		ceil;
	t_plane		top;
	t_plane		left_top;

	ceil = eng_new_plane();
	ceil.base_obj.material.fcolor = new_fcolor(0, 0, 1, 1);
	ceil.base_obj.material.pattern = pat_square3d_pattern(
			new_fcolor(1, 1, 0, 1), new_fcolor(0, 1, 1, 1));
	ceil.base_obj.material.reflective = 0.3;
	eng_add_obj_to_world(world, (t_obj_ptr) & ceil);
	top = eng_new_plane();
	top.base_obj.material.fcolor = new_fcolor(1, 1, 1, 1);
	top.base_obj.material.reflective = 0.3;
	top.base_obj.material.pattern = pat_checker2d_pattern(
			new_fcolor(1, 0, 0, 1), new_fcolor(0, 0, 1, 1));
	eng_set_transform((t_obj_ptr) & top, mtx_rotation_x(M_PI_2));
	eng_set_transform((t_obj_ptr) & top, mtx_translate(0, 0, 4));
	eng_add_obj_to_world(world, (t_obj_ptr) & top);
	left_top = eng_new_plane();
	left_top.base_obj.material.fcolor = new_fcolor(0, 1, 0, 1);
	eng_set_transform((t_obj_ptr) & left_top, mtx_rotation_x(M_PI_2));
	eng_set_transform((t_obj_ptr) & left_top, mtx_rotation_y(5.49778714378));
	eng_set_transform((t_obj_ptr) & left_top, mtx_translate(-5, 0, 0));
	light_mid_left(world);
	cyl_right(world);
}

static void	init_camera(t_main *m_data)
{
	t_camera	*camera;

	if (m_data->camera_type == USER_INPUT)
		return ;
	m_data->camera_type = PRESET;
	camera = &(m_data->engine.camera);
	*(camera) = eng_new_camera(WIDTH, HEIGHT, M_PI / 3);
	eng_set_transform((t_obj *)camera, sc_transforme_view(new_point(5, 5, -5),
			new_point(0, 0, 0), new_vec(0.3, 0.3, 0.3)));
}

void	reflection_demo(void *main_data)
{
	t_main		*m_data;
	t_world		*world;

	m_data = (t_main *)main_data;
	init_camera(m_data);
	world = &m_data->engine.world;
	init_world(world);
}
