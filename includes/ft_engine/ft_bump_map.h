#ifndef FT_BUMP_MAP_H
# define FT_BUMP_MAP_H

//INCLUDES
# include <stdlib.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_engine.h>

typedef struct s_bump_norm
{
	double		wavelength[5];
	double		amplitude[5];
	double		directions[5][2];
	double		phases[5];
	double		cos_dot;
	double		sin_dot;
	int			i;
	double		x;
	double		z;
	double		k;
	double		dir_x;
	double		dir_z;
	double		d_dx;
	double		d_dy;
	double		d_dz;
	t_vec		perturbed_normal;
	double		dot;
	double		dir_length;
	const int	num_waves;
}				t_bump_norm;

//Source Files
//Frame for Bump Map Logic
t_bump		*bump_new_bump(void);
t_vec		bump_normal_at(t_obj obj, t_bump bump_map, t_point world_point, t_vec normal_base);

//Bump map type (specific maps)
t_bump		*bump_wave(void);
t_vec		bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal);

#endif
