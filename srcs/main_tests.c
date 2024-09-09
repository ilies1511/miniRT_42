#include <main.h>

#ifdef NO_ASSERT
void	do_nothing(int sig)
{
	(void) sig;
	return ;
}

// to deactivate assert interrupt
// comment later duo to unallowed fn
#include <signal.h>
void	deactivate_assert_interrupt(void)
{
	printf("dactivating assert interrupt\n");
	struct sigaction sig_data = {0};
	sig_data.sa_handler = do_nothing;
	sigemptyset(&sig_data.sa_mask);
	sig_data.sa_mask = 0;
	sigaction(SIGTRAP, &sig_data, 0);
	raise(SIGTRAP);//test
}
#endif //NO_ASSERT











int	example_add(int a, int b)
{
	return (a + b);
}

bool	example_test(void)
{
	const int	tests[5][3] = {
		{1, 1, 2},          // 1 + 1 = 2
		{-2, 10, 8},        // -2 + 10 = 8
		{0, 0, 0},          // 0 + 0 = 0
		{100, -100, 0},     // 100 - 100 = 0
		{-5, -5, -10}       // -5 + -5 = -10
	};
	const int	a = 0;
	const int 	b = 1;
	const int 	expected = 2;
	bool		all_tests_passed;
	size_t		i;

	i = 0;
	all_tests_passed = true;
	while (i < sizeof tests / sizeof tests[0])
	{
		int actual = example_add(tests[i][a], tests[i][b]);
		bool test_passed = actual == tests[i][expected];
		ft_assert(test_passed, "a + b != result", __LINE__, __FILE__);
		if (!test_passed)
			all_tests_passed = false;
		i++;
	}
	return (all_tests_passed);
}

void	tuple_tests(int *total_tests, int *passed_tests)
{

	if (is_point_test())
		*passed_tests += 1;
	*total_tests += 1;
	if (is_vec_test())
		*passed_tests += 1;
	*total_tests += 1;
}

void	test_matrixes(int *total_tests, int *passed_tests)
{
		if (test_eq_m())
			*passed_tests += 1;
		*total_tests += 1;
	if (test_mult_mt())
		*passed_tests += 1;
	*total_tests += 1;
}

int	main(void)
{
#ifdef NO_ASSERT
	deactivate_assert_interrupt();
#endif
	int	passed = 0;
	int	total = 0;
	srand(time(NULL));
	if (example_test())
		passed++;
	total++;
	tuple_tests(&total, &passed);
	test_matrixes(&total, &passed);
	if (total == passed)
		printf("all tests passed(%d/%d)!\n", passed, total);
	else
		printf("%d of %d test passed\n", passed, total);
	return (0);
}
