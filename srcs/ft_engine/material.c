#include <ft_engine.h>

t_material	eng_new_material(void)
{
	t_material	mat;

	mat.fcolor = new_fcolor(1, 1, 1, 1);
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200;
	return (mat);
}
