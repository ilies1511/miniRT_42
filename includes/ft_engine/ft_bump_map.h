#ifndef FT_BUMP_MAP_H
# define FT_BUMP_MAP_H

//INCLUDES
# include <stdlib.h>
# include <ft_tuple.h>
# include <ft_matrix.h>
# include <ft_engine.h>
//Source Files
t_bump		*bump_new_bump(void);
t_vec		bump_normal_at(t_obj obj, t_bump bump_map, t_point world_point);















#endif
