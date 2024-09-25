#include <main.h>

int	main(int ac, char *av[])
{
	t_main		*m_data;

	m_data = get_m_data();
	main_init(m_data, ac, av);
	// this should never be reached sicne the mlx loop called in main_init()
	// goes until main_cleanup() is called();
	ft_assert(0, "end of main should never be reached", __LINE__, __FILE__);
	__builtin_unreachable();
	return (0);
}

