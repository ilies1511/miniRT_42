#include <main.h>
#include <ft_floats.h>
#include <ft_colors.h>

t_fcolor	new_fcolor(double r, double g, double b, double a)
{
	t_fcolor	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 1;
	(void)a;
	return (color);
}

t_uintcolor	fcolor_to_uintcolor(t_fcolor fcolor)
{
	t_uintcolor	ret;

	ret.argb.r = (uint8_t)(0xFF * clamp_f(fcolor.r, 0, 1));
	ret.argb.g = (uint8_t)(0xFF * clamp_f(fcolor.g, 0, 1));
	ret.argb.b = (uint8_t)(0xFF * clamp_f(fcolor.b, 0, 1));
	ret.argb.a = 0xFF;
	return (ret);
}

t_fcolor	mult_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	new_color;

	new_color.r = a.r * b.r;
	new_color.g = a.g * b.g;
	new_color.b = a.b * b.b;
	new_color.a = 1.0;
	return (new_color);
}

t_fcolor	add_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	sum;

	sum.r = a.r + b.r;
	sum.g = a.g + b.g;
	sum.b = a.b + b.b;
	sum.a = 1.0;
	return (sum);
}

/*
	Subtraction of two tuples
*/
t_fcolor	sub_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	dif;

	dif.r = a.r - b.r;
	dif.g = a.g - b.g;
	dif.b = a.b - b.b;
	dif.a = 1.0;
	return (dif);
}

t_fcolor	scale_fcolor(t_fcolor c, double scalar)
{
	t_fcolor	res;

	res.r = c.r * scalar;
	res.g = c.g * scalar;
	res.b = c.b * scalar;
	res.a = 1.0;
	return (res);
}

bool	eq_fcolor(t_fcolor a, t_fcolor b)
{
	return (eq_f(a.r, b.r) && eq_f(a.g, b.g)
			&& eq_f(a.b, b.b) && eq_f(a.a, b.a));
}

void	print_fcolor(char *str, t_fcolor col)
{
	printf("%sr:%f; g: %f; b: %f; a: %f\n", str, col.r, col.g, col.b, col.a);
}

