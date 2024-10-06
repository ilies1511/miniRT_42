#ifndef FT_BUMP_MAP_H
# define FT_BUMP_MAP_H

//INCLUDES
# include <stdlib.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_engine.h>

typedef struct s_bump_norm
{
	double		x;
	int			i;
	double		time;
	double		d_dx;
	double		d_dy;
	double		d_dz;
	double		z;
	double		amplitude;
	double		wavelength;
	double		speed;
	double		phase;
	double		k;
	double		omega;
	double		dir_x;
	double		dir_z;
	double		dir_length;
	double		dot;
	double		cos_dot;
	double		sin_dot;
	t_vec		perturbed_normal;
	const int	num_waves;
	double		amplitudes[6];
	double		wavelengths[6];
	double		directions[6][2];
}				t_bump_norm;

//Source Files
//Frame for Bump Map Logic
t_bump		*bump_new_bump(void);
t_vec		bump_normal_at(t_obj obj, t_bump bump_map, t_point world_point,
				t_vec normal_base);

//Bump map type (specific maps)
t_bump		*bump_wave(void);
t_vec		bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal);

#endif
