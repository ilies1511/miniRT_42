#include <ft_engine.h>

t_material	eng_new_material(void)
{
	t_material	mat;

	mat.fcolor.r = 1;
	mat.fcolor.g = 1;
	mat.fcolor.b = 1;
	mat.fcolor.a = 1;
	mat.pattern = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200;
	mat.reflective = 0.0;
	mat.transparency = 0.0;
	mat.refractive_index = 1;
	return (mat);
}
