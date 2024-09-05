#ifndef FT_TUPLE_H
# define FT_TUPLE_H

# include <stdbool.h>

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

bool	is_vec(t_tuple v3);
bool	is_point(t_tuple v3);

t_tuple	new_point(float x, float y, float z);
t_tuple	new_vec(float x, float y, float z);

//equal float
//(a == b) ?
bool	eq_f(float a, float b);
//equal tuple
bool	eq_t(t_tuple a, t_tuple b);

t_tuple	add_t(t_tuple a, t_tuple b);

t_tuple	sub_t(t_tuple a, t_tuple b);
// tests to verify add_t adn sub_t with special focus on w

t_tuple	negate_t(t_tuple t);
//negate_t test

t_tuple	mult_t(t_tuple t, float scalar);
t_tuple	div_t(t_tuple t, float scalar);

float	len_t(t_tuple t);




t_tuple	norm_t(t_tuple t);

int	add_i(int a, int b);



#endif
