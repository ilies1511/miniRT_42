#include <main.h>
#include <ft_engine.h>

t_canvas	eng_new_canvas(t_main *m_data, size_t width, size_t height)
{
	t_canvas canv;

	canv.width = width;
	canv.height = height;
	canv.pixels = (t_uintcolor *)(m_data->cleanup_data.mlx_img->pixels);
	reset_canvas(&canv);
	return (canv);
}

void	reset_canvas(t_canvas *canvas)
{
	t_uintcolor		*pixels;
	size_t				x;
	size_t				y;
	const t_uintcolor color =
	{
		.argb.a = 0xFF,
		.argb.r = 0x00,
		.argb.g = 0x00,
		.argb.b = 0x00,
	};

	pixels = canvas->pixels;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < canvas->width)
		{
			pixels[y * canvas->width + x] = color;
			x++;
		}
		y++;
	}
}
