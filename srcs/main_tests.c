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

int	main(void)
{
#ifdef NO_ASSERT
	deactivate_assert_interrupt();
#endif
	int	passed = 0;
	int	total = 0;
	if (example_test())
		passed++;
	total++;
	if (total == passed)
		printf("all tests passed!\n");
	else
		printf("%d of %d test passed\n", passed, total);
	return (0);
}
