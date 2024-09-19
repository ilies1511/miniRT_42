#include <ft_engine.h>


t_light	eng_new_light(t_f_color intensity, t_point origin)
{
	t_light	light;

	light.intensity = new_fcolor(1, 1, 1, 0);
	light.base_obj = eng_new_obj();
	light.intensity = intensity;
	light.origin = origin;
	return (light);
}
