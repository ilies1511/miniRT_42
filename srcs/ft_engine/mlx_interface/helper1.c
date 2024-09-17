#include <main.h>
#include <ft_colors.h>
#include <ft_engine.h>
#include <mlx_interface.h>

void	put_pixel(float x, float y, t_uint_color color, uint32_t *pixels)
{
	size_t	xi;
	size_t	yi;

	ft_assert(x >= -1 && x <= 1 && y >= -1 && y <= 1, __FILE__, __LINE__,
		"given coordinates to put_pixel() are out of range");
	y *= -1;
	xi = (size_t)((x + 1) / 2 * (WIDTH - 1));
	yi = (size_t)((y + 1) / 2 * (HEIGHT - 1));
	printf("x: %f, xi: %lu; y: %f, yi: %lu\n", x, xi, y, yi);
	pixels[yi * WIDTH + xi] = color.full;
}

