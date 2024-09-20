#include <main.h>
#include <ft_engine.h>

t_canvas	eng_new_canvas(t_main *m_data, size_t width, size_t height)
{
	t_canvas canv;

	canv.width = width;
	canv.height = height;
	canv.img = mlx_new_image(m_data->mlx, width, height);
	if (!canv.img || mlx_image_to_window(m_data->mlx, canv.img, 0, 0))
	{
		ft_error("eng_new_canvas: and mlx init fn failed",
			__FILE__, __LINE__, 1);
	}
	reset_canvas(&canv);
	return (canv);
}

void	eng_free_canvas(mlx_t *mlx, t_canvas *canvas)
{
	mlx_delete_image(mlx, canvas->img);
	canvas->img = NULL;
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

	pixels = (t_uintcolor *)(canvas->img->pixels);
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
