/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:46 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:34:54 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <ft_tuple.h>

bool	eng_eq_ray(t_ray r1, t_ray r2)
{
	return (eq_t(r1.origin, r2.origin) && eq_t(r1.direct, r2.direct));
}
