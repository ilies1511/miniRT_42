#include <main.h>

// z axis ignored for now, only 2D

typedef struct s_projectile
{
	t_point	pos;
	t_vec	speed;
}	t_projectile;

typedef struct s_env
{
	t_vec	wind;
	t_vec	grav;
}	t_env;

t_env	new_env(void)
{
	t_env	env;

	env.wind = new_vec(0, 0, 0);
	//env.wind = norm(env.wind);
	env.grav = new_vec(0, 123, 0);
	return (env);
}

t_projectile	init_projectile(t_main *m_data)
{
	t_projectile	projectile;

	projectile.pos = new_point(0, m_data->canvas.height - 1, 0);
	projectile.speed = new_vec(100, 500, 0);
	return (projectile);
}

void	draw_projectile(void *main_data)
{
	double	d_time = 0;
	t_vec	movement;

	t_main	*m_data = (t_main *)main_data;
	const t_env env = new_env();
	static t_projectile	projectile = {.pos.x = -1.0};
	static double counter = 0;
	const t_uintcolor color = {.full = RED};

	if (projectile.pos.x == -1.0)
		projectile = init_projectile(m_data);
	else
	{
		d_time = m_data->mlx->delta_time;
		counter += d_time;
		//ignoring accurate speed calc
		projectile.speed =  add_t(projectile.speed, mult_v(env.grav, d_time));
		projectile.speed =  add_t(projectile.speed, mult_v(env.wind, d_time));
		movement = mult_v(projectile.speed, d_time);
		projectile.pos = add_t(projectile.pos, movement);
		//ft_printf("movement: \n");
		//print_tuple(1, movement);
		ft_printf("pos:\n");
		print_t(1, projectile.pos);

	}
	int y = (int)projectile.pos.y - 20;
	y = max_i(y, 0);
	int	end_y = (int)projectile.pos.y + 20;
	end_y = min_i(end_y, m_data->canvas.height - 1);
	int	start_x = (int)projectile.pos.x - 20;
	start_x = max_i(start_x, 0);
	int	end_x = (int)projectile.pos.x + 20;
	end_x = min_i(end_x, m_data->canvas.width - 1);
	uint32_t	*pixels = (uint32_t *)(m_data->canvas.img->pixels);
	while (y <= end_y)
	{
		for (int x = start_x; x <= end_x; x++)
		{
			pixels[y * m_data->canvas.width + x] = color.full;
		}
		y++;
	}
	if (counter > 3)
	{
		// store_as_plain_ppm(m_data, "test.ppm");
		counter = -40;
	}
	if (projectile.pos.x < 0)
	{
		projectile.pos.x = 0;
		if (projectile.speed.x < 0)
			projectile.speed.x *= -1;
	}
	else if (projectile.pos.x > m_data->canvas.width - 1)
	{
		projectile.pos.x = m_data->canvas.width - 1;
		if (projectile.speed.x > 0)
			projectile.speed.x *= -1;
	}
	if (projectile.pos.y < 0)
	{
		projectile.pos.y = 0;
		if (fabs(projectile.speed.y) > m_data->canvas.height / d_time / 4)
			projectile.speed.y = m_data->canvas.height / d_time / 4;
		if (projectile.speed.y < 0)
			projectile.speed.y *= -1;
		//projectile.speed.y = 0;
	}
	else if (projectile.pos.y > m_data->canvas.height - 1)
	{
		projectile.pos.y = m_data->canvas.height - 1;
		if (projectile.speed.y > 0 )
		{
			if (fabs(projectile.speed.y) > m_data->canvas.height / d_time / 4)
				projectile.speed.y = -m_data->canvas.height / d_time / 4;
			projectile.speed.y *= -1;
		}
		//projectile.speed.y = 0;
	}
}

