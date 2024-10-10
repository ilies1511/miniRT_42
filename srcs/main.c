/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:26:21 by frapp             #+#    #+#             */
/*   Updated: 2024/10/10 15:06:28 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

int	main(int ac, char *av[])
{
	t_main	*m_data;

	m_data = get_m_data();
	main_init(m_data, ac, av);
	rt_assert(0, "end of main should never be reached", __LINE__, __FILE__);
	__builtin_unreachable();
	return (0);
}
