#include <ft_engine.h>

t_material	eng_new_material(void)
{
	t_material	mat;

	mat.fcolor = fcolor_white();
	mat.pattern = NULL;
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200;
	mat.reflective = 0.0;
	return (mat);
}

