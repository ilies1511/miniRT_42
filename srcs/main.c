#include <main.h>

int	main(int ac, char *av[])
{
	t_main	*m_data;

	m_data = get_m_data();
	main_init(m_data, ac, av);
	ft_assert(0, "end of main should never be reached", __LINE__, __FILE__);
	__builtin_unreachable();
	return (0);
}
