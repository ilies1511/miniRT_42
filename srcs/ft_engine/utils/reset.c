#include <main.h>



//// outdated t_main structer prevents compiling
//void	smoth_vanish(t_main *m_data)
//{
//	t_uint_color		*pixels;
//	int				x;
//	int				y;
//	static double time_sum = 0;
//
//	time_sum += m_data->mlx->delta_time;
//	const t_uint_color soll = {
//		.argb.a = 0xFF,
//		.argb.r = 0x00,
//		.argb.g = 0xFF,
//		.argb.b = 0x00,
//	};
//	t_uint_color ist = {
//		.argb.a = 0xFF,
//		.argb.r = 0x00,
//		.argb.g = 0xFF,
//		.argb.b = 0x00,
//	};
//
//	pixels = (t_uint_color *)(m_data->img->pixels);
//	y = 0;
//	if (time_sum < 0.9)
//		return ;
//	time_sum = 0;
//	while (y < HEIGHT)
//	{
//		x = 0;
//		while (x < WIDTH)
//		{
//			ist = pixels[y * WIDTH + x];
//			//t_uint_color green = {.full = GREEN};
//			//t_uint_color diff =
//			//{
//			//	.argb.a = soll.argb.a - ist.argb.a,
//			//	.argb.r = soll.argb.r - ist.argb.r,
//			//	.argb.g = soll.argb.g - ist.argb.g,
//			//	.argb.b = soll.argb.b - ist.argb.b
//			//};
//			//int a_diff = soll.argb.a - ist.argb.a;
//			int r_diff = soll.argb.r - ist.argb.r;
//			//int g_diff = soll.argb.g - ist.argb.g;
//			//int b_diff = soll.argb.b - ist.argb.b;
//			if (r_diff > 0)
//			{
//				pixels[y * WIDTH + x].argb.r++;
//				pixels[y * WIDTH + x].argb.g--;
//			}
//			if (r_diff < 0)
//			{
//				pixels[y * WIDTH + x].argb.r--;
//				pixels[y * WIDTH + x].argb.g++;
//			}
//			//float factor = m_data->mlx->delta_time / 20;
//			x++;
//		}
//		y++;
//	}
//}
