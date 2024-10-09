/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:35:57 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:35:58 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_engine.h>
#include <libft.h>

void	eng_free_intersc_arr(t_intersc_arr *interscs)
{
	dyn_arr_free((void **)(&interscs->arr));
	interscs->count = 0;
}