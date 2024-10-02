#include <ft_tuple.h>
#include <ft_floats.h>
#include <libft.h>

bool	testloop_bool_tuple(bool (*fn)(t_tuple), const bool expected[],
		const t_tuple tests[],
		size_t test_count)
{
	size_t	i;
	bool	return_val;

	return_val = true;
	i = 0;
	while (i < test_count)
	{
		if (fn(tests[i]) != expected[i])
		{
			return_val = false;
			ft_fprintf(2, "got bool: %d for:\n", !expected[i]);
			print_t(2, tests[i]);
		}
		i++;
	}
	return (return_val);
}

bool	is_vec_test(void)
{
	const bool			expected[] = {
		false, true, true, true, };
	const t_tuple	tests[] = {
		{.x = 1.0, .y=1.0, .z=1.0, .w=3.1},
		{.x = 0.0, .y=1.0, .z=1.0, .w=0.0},
		{.x = 0.0, .y=1.0, .z=1.0, .w=0.0 - (EPSILON) * 0.99},
		{.x = 0.0, .y=1.0, .z=1.0, .w=0.0 + (EPSILON) * 0.99},
	};
	const size_t	test_count = sizeof expected / sizeof expected[0];

	ft_assert(test_count == sizeof tests / sizeof tests[0],
			__FILE__, __LINE__,
			"test result count for 'is_vec_test()' do not match test cases'");
	if (!testloop_bool_tuple(is_vec, expected, tests, test_count))
	{
		ft_fprintf(2, "is_vec() failed\n");
		return (false);
	}
	return (true);
}

bool	is_point_test(void)
{
	const bool			expected[] = {
		false, false, false, false, true, true,};
	const t_tuple	tests[] = {
		{.x = 1.0, .y = 1.0, .z = 1.0, .w = 3.1},
		{.x = 0.0, .y = 1.0, .z = 1.0, .w = 0.0},
		{.x = 0.0, .y = 1.0, .z = 1.0, .w = 0.0 - (EPSILON) * 0.99},
		{.x = 0.0, .y = 1.0, .z = 1.0, .w = 0.0 + (EPSILON) * 0.99},
		{.x = 0.0, .y = 1.0, .z = 1.0, .w = 1.0 - (EPSILON) * 0.99},
		{.x = 0.0, .y = 1.0, .z = 1.0, .w = 1.0 + (EPSILON) * 0.99},
	};
	const size_t	test_count = sizeof expected / sizeof expected[0];

	ft_assert(test_count == sizeof tests / sizeof tests[0],
			__FILE__, __LINE__,
			"test result count for 'is_vec_test()' do not match test cases'");
	if (!testloop_bool_tuple(is_point, expected, tests, test_count))
	{
		ft_fprintf(2, "is_point() failed\n");
		return (false);
	}
	return (true);
}

t_point	new_point(double x, double y, double z);
t_vec	new_vec(double x, double y, double z);
bool	eq_t(t_tuple a, t_tuple b);


