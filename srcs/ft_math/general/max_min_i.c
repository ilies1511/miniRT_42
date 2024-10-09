/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_min_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:24 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:33:25 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	max_i(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min_i(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	max_sz(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	min_sz(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}
