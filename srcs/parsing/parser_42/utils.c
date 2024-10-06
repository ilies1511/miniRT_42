#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

static void	skip_value(char **str)
{
	if (**str == '-')
		(*str)++;
	while (**str && **str != ',')
	{
		(*str)++;
	}
	(*str)++;
}

void	str_to_tuple(char *str, t_tuple *ret, char **str_ptr, double w)
{
	ret->w = w;
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!ft_isdigit(*str) && *str != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	ret->x = str_to_float(str);
	skip_value(&str);
	if (!ft_isdigit(*str) && *str != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	ret->y = str_to_float(str);
	skip_value(&str);
	if (!ft_isdigit(*str) && *str != '-')
		parser_error("parsing error", __FILE__, __LINE__, 100);
	ret->z = str_to_float(str);
	if (*str == '-')
		str++;
	while (*str && (*str == '.' || ft_isdigit(*str)))
		str++;
	while (*str && ft_iswhitespace(*str))
		str++;
	*str_ptr = str;
}

void	str_to_fcolor(char *str, t_fcolor *ret, char **str_ptr)
{
	ret->a = 1.0;
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!ft_isdigit(*str))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	ret->r = str_to_float(str) / 255;
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	ret->g = str_to_float(str) / 255;
	while (*str && *str != ',')
		str++;
	str++;
	if (!ft_isdigit(*str))
		parser_error("parsing error", __FILE__, __LINE__, 100);
	ret->b = str_to_float(str) / 255;
	while (*str && (ft_isdigit(*str) || *str == '.'))
		str++;
	while (*str && ft_iswhitespace(*str))
		str++;
	*str_ptr = str;
}

