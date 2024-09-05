#include <main.h>

void	reset_img(t_main *m_data)
{
	uint32_t	*pixels;
	int			x;
	int			y;

	pixels = (uint32_t *)(m_data->img->pixels);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixels[y * WIDTH + x] = BLACK;
			x++;
		}
		y++;
	}
}
