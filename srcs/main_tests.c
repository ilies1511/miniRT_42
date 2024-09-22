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
	if (test_mtx_eq())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_mult_mt())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_mult_mm())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_sub_matrix())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_transpose())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_minor())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_cofactor())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_det())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_inverse())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_matrix_mult_inverse())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_matrix_translate())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_mtx_scaling())
		*passed_tests += 1;
	*total_tests += 1;
}

void	test_rays(int *total_tests, int *passed_tests)
{
	if (test_eng_ray_pos())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_intersc_ray_sphere())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_ray_hit())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_reflect())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_lighting())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_ray_intersc_world())
		*passed_tests += 1;
	*total_tests += 1;
}

void	test_objs(int *total_tests, int *passed_tests)
{
	if (test_eng_trasform())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_transformation_matrices())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_normal_at())
		*passed_tests += 1;
	*total_tests += 1;
}

void	test_scenes(int *total_tests, int *passed_tests)
{
	if (test_transformation_view_default())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_transformation_view_z())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_transformation_view_world())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_transformation_view_mixed())
		*passed_tests += 1;
	*total_tests += 1;
}

void	test_computation(int *total_tests, int *passed_tests)
{
	if (test_prepare_computation())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_shading_outside_intersection())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_color_at())
		*passed_tests += 1;
	*total_tests += 1;
	if (test_eng_new_camera())
		*passed_tests += 1;
	*total_tests += 1;
}
void	test_gc(int *total_tests, int *passed_tests)
{
	//t_garbage_collector	*gc;

	//gc = get_gc();
	if (test_gc_init())
		*passed_tests += 1;
	*total_tests += 1;
}

int	main(void)
{
	t_garbage_collector	*gc;

#ifdef NO_ASSERT
	deactivate_assert_interrupt();
#endif
	gc = get_gc();
	int	passed = 0;
	int	total = 0;
	srand(time(NULL));
	if (example_test())
		passed++;
	total++;
	tuple_tests(&total, &passed);
	test_matrixes(&total, &passed);
	test_rays(&total, &passed);
	test_gc(&total, &passed);
	test_objs(&total, &passed);
	test_scenes(&total, &passed);
	test_computation(&total, &passed);
	if (total == passed)
		printf("%s all tests passed(%d/%d)!%s\n", FT_ANSI_GREEN_BOLD, passed, total, FT_ANSI_RESET);
	else
		printf("%s%d of %d test passed%s\n", FT_ANSI_RED_BOLD, passed, total, FT_ANSI_RESET);
	//system("leaks tests.out");
	gc = get_gc();
	// printf("Im in main SIZE: %zu\n", gc->size);
	// printf("Strin im gc: %s\n", (gc->head->pointer));
	// printf("Strin im gc: %s\n", (gc->head->next->pointer));
	gc_free_all(gc);
	//system("leaks tests.out");
	return (0);
}

