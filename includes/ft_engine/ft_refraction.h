/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refraction.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:40 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:33:46 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REFRACTION_H
# define FT_REFRACTION_H

# include <stdbool.h>
# include <ft_tuple.h>
# include <ft_colors.h>
# include <ft_engine.h>

t_fcolor	refracted_color(t_world world, t_computation comp,
				size_t remaining);
double		ref_schlick(t_computation comp);
#endif //FT_REFRACTION_H
