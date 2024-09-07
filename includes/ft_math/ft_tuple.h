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

typedef t_tuple	t_vec;
typedef t_tuple	t_point;

// for vecs w == 0
bool	is_vec(t_tuple tuple);
// for points w == 1
bool	is_point(t_tuple tuple);

t_point	new_point(float x, float y, float z);
t_vec	new_vec(float x, float y, float z);

//equal tuple
bool	eq_t(t_tuple a, t_tuple b);

t_tuple	add_t(t_tuple a, t_tuple b);

t_tuple	sub_t(t_tuple a, t_tuple b);
// tests to verify add_t adn sub_t with special focus on w

t_vec	negate_v(t_vec v);
//negate_t test

t_vec	mult_v(t_vec v, float scalar);
t_vec	div_v(t_vec v, float scalar);

//len/magnitude
float	len_v(t_vec v);

//creates uint vector (len == 1)
t_vec	norm(t_vec v);

float	dot_prod(t_vec a, t_vec b);
t_vec	cross_prod(t_vec a, t_vec b);

//******tests**********

void	print_tuple(int fd, t_tuple t);

bool	is_point_test(void);
bool	is_vec_test(void);

#endif
