#ifndef FT_BUMP_MAP_H
# define FT_BUMP_MAP_H

//INCLUDES
# include <stdlib.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_engine.h>


			//Source Files
//Frame for Bump Map Logic
t_bump		*bump_new_bump(void);
t_vec		bump_normal_at(t_obj obj, t_bump bump_map, t_point world_point, t_vec normal_base);

//Bump map type (specific maps)
t_bump		*bump_wave(void);
t_vec		bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal);














#endif
