#include <main.h>
#include <includes/ft_math/ft_colors.h>

t_f_color	create_color(float r, float g, float b, float a)
{
	t_f_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_f_color	fcol_fcol_mult(t_f_color a, t_f_color b)
{
	t_f_color	new_color;

	new_color.r = a.r * b.r;
	new_color.g = a.g * b.g;
	new_color.b = a.b * b.b;
	return (new_color);
}
