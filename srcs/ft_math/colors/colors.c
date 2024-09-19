#include <main.h>
#include <ft_floats.h>
#include <ft_colors.h>

t_f_color	fcol_new(float r, float g, float b, float a)
{
	t_f_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_uint_color	fcolor_to_uintcolor(t_f_color fcolor)
{
	t_uint_color	ret;

	ret.argb.a = (uint8_t)(0xFF * clamp_f(fcolor.a, 0, 1));
	ret.argb.r = (uint8_t)(0xFF * clamp_f(fcolor.r, 0, 1));
	ret.argb.g = (uint8_t)(0xFF * clamp_f(fcolor.g, 0, 1));
	ret.argb.b = (uint8_t)(0xFF * clamp_f(fcolor.b, 0, 1));
	return (ret);
}

t_f_color	fcol_mult(t_f_color a, t_f_color b)
{
	t_f_color	new_color;

	new_color.r = a.r * b.r;
	new_color.g = a.g * b.g;
	new_color.b = a.b * b.b;
	return (new_color);
}

t_f_color	f_col_add(t_f_color a, t_f_color b)
{
	t_f_color	sum;

	sum.r = a.r + b.r;
	sum.g = a.g + b.g;
	sum.b = a.b + b.b;
	sum.a = a.a + b.a;
	return (sum);
}

/*
	Subtraction of two tuples
*/
t_f_color	f_col_sub(t_f_color a, t_f_color b)
{
	t_f_color	dif;

	dif.r = a.r - b.r;
	dif.g = a.g - b.g;
	dif.b = a.b - b.b;
	dif.a = a.a - b.a;
	return (dif);
}

t_f_color	f_col_scale(t_f_color c, float scalar)
{
	t_f_color	res;

	res.r = c.r * scalar;
	res.g = c.g * scalar;
	res.b = c.b * scalar;
	res.a = c.a * scalar;
	return (res);
}
