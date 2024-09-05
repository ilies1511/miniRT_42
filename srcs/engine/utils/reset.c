#include <main.h>

void	reset_img(t_main *m_data)
{
	uint32_t		*pixels;
	int				x;
	int				y;
	const int32_t	color = 0xFF0000FF;

	pixels = (uint32_t *)(m_data->img->pixels);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixels[y * WIDTH + x] = color;
			x++;
		}
		y++;
	}
}
