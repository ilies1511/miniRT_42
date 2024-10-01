#include <ft_engine.h>
#include <libft.h>
#include <main.h>

bool	test_shade_hit(void)
{
	t_world			w;
	t_light			light;
	t_sphere		s;
	t_sphere		s2;
	t_ray			ray;
	t_intersc		intersec;
	t_intersc_arr	intersecs;
	t_computation	comp;
	t_fcolor		soll_color;
	t_fcolor		ist_color;
	bool			status;

	soll_color = new_fcolor(0.1, 0.1, 0.1, 1);
	w = eng_new_world();
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(0, 0, -10));
	eng_add_obj_to_world(&w, (t_obj *)&light);
	s = eng_new_sphere();
	eng_add_obj_to_world(&w, (t_obj *)&s);
	s2 = eng_new_sphere();
	eng_set_transform((t_obj *)&s2, mtx_translate(0, 0, 10));
	eng_add_obj_to_world(&w, (t_obj *)&s2);
	intersecs = eng_new_intersc_arr();
	intersec = eng_add_intersc(&intersecs, (t_obj *)&s2, 4);
	ray = eng_new_ray(new_point(0, 0, 5), new_vec(0, 0, 1));
	eng_intersc_ray(&intersecs, ray, (t_obj *)&s2);
	comp = eng_prepare_computation(intersec, ray);
	ist_color = eng_shade_hit(w, comp);
	if (eq_fcolor(ist_color, soll_color))
		status = true;
	else
	{
		print_fcolor("SOLL:\n", soll_color);
		print_fcolor("\nIST:\n", ist_color);
		status = false;
	}
	return (eng_free_intersc_arr(&intersecs), status);
}
