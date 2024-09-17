#include <main.h>

void	sphere_test(void *main_data)
{
	t_main	*m_data = (t_main *)main_data;
	t_uint_color	color;

	color.full = RED;
	for (float y = 0.8; y <= 1; y += 0.01)
	{
	for (float x = -1; x <= 1; x += 0.001)
		put_pixel(x, y, color, (uint32_t *)(m_data->img->pixels));
	}
}

