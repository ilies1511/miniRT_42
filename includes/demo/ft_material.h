#ifndef FT_MATERIAL_H
#define FT_MATERIAL_H

//Includes
#include <ft_engine.h>

//Function Prototpyes
//Metal
t_material	eng_new_material_polished_metal(void);
t_material	material_silver_and_gold(void);

//Landscape
t_material	eng_blue_sky(void);
t_material	eng_water(void);
t_material	eng_sand(void);

#endif
