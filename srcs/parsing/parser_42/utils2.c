/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:31:18 by frapp             #+#    #+#             */
/*   Updated: 2024/10/09 22:31:19 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <ft_engine.h>
#include <parser_42.h>

//to comply with supject error message
noreturn void	parser_error(char *str, char *file, int line, int exit_stat)
{
	printf("Error\n");
	ft_error(str, file, line, exit_stat);
}

void	skip_whitespace(char **str)
{
	while (*str && **str && ft_iswhitespace(**str))
		(*str)++;
}

void	skip_float(char **str)
{
	if (!str || !*str)
		return ;
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	skip_whitespace(str);
}
