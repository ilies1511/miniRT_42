#include <main.h>

int	main(void)
{
	t_main	m_data;
	printf("hi\n");
	main_init(&m_data);
	// this should never be reached sicne the mlx loop called in main_init()
	// goes until main_cleanup() is called();
	ft_assert(0, "end of main should never be reached", __LINE__, __FILE__);
	__builtin_unreachable();
	return (0);
}

