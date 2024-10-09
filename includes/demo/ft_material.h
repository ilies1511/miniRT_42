/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_material.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:48 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:33:00 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATERIAL_H
# define FT_MATERIAL_H

//Includes
# include <ft_engine.h>

//Function Prototpyes
//Metal
t_material	eng_new_material_polished_metal(void);
t_material	material_silver_and_gold(void);

//Landscape
t_material	eng_blue_sky(void);
t_material	eng_water(void);
t_material	eng_sand(void);

#endif
