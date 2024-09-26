#include <ft_engine.h>
#include <stdlib.h>

t_world	eng_default_world(void)
{
	t_world		def;
	t_light		light;
	t_sphere	sph;

	def = eng_new_world();
	light = eng_point_light(new_fcolor(1, 1, 1, 1), new_point(-10, 10, -10));
	eng_add_obj_to_world(&def, (t_obj *)&light);
	// printf("\nLight in eng_default_world: ");
	// print_t(2, light.origin);

	sph = eng_new_sphere();
	sph.base_obj.material.fcolor = new_fcolor(0.8, 1.0, 0.6, 1);
	sph.base_obj.material.diffuse = 0.7;
	sph.base_obj.material.specular = 0.2;
	eng_add_obj_to_world(&def, (t_obj *)&sph);

	sph = eng_new_sphere();
	eng_set_transform((t_obj *)&sph, mtx_scale(0.5, 0.5, 0.5));
	eng_add_obj_to_world(&def, (t_obj *)&sph);

	// printf("\n");
	// printf("\nLight in eng_default_world array: ");
	// printf("lights count: %lu\n", def.light_count);
	// printf("objs count: %lu\n", def.obj_count);
	// print_t(2, def.lights[0].origin);
	// printf("\n");
	// exit(1);
	return (def);
}
