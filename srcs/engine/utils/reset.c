#include <main.h>

void	reset_img(t_main *m_data)
{
	uint32_t		*pixels;
	int				x;
	int				y;
	const t_color color = {
		.argb.a = 0xFF,
		.argb.r = 0x00,
		.argb.g = 0xFF,
		.argb.b = 0x00,
	};

	pixels = (uint32_t *)(m_data->img->pixels);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixels[y * WIDTH + x] = color.full;
			x++;
		}
		y++;
	}
}
