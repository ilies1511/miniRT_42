/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:08 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:32:09 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

double	ft_rand(void)
{
	static uint64_t	rand_buffer[1250000];
	static bool		first = true;
	static size_t	i = 0;
	int				fd;
	int				read_return;

	if (first)
	{
		first = false;
		fd = open(RANDOM_BIN_FILE, O_RDONLY);
		if (fd < 0)
			ft_error("error opening random binary data file", __FILE__,
				__LINE__, errno);
		read_return = read(fd, rand_buffer, 1250000 * sizeof (double));
		if (read_return < 0)
			ft_error("error reading random binary data file", __FILE__,
				__LINE__, errno);
		close(fd);
	}
	return ((double)rand_buffer[i++ % 1250000] / UINT64_MAX);
}
