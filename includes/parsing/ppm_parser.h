/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:43 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:34:46 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_PARSER_H
# define PPM_PARSER_H

typedef struct s_main	t_main;

# ifndef PPM_MAX_CHARS_PER_LINE
#  define PPM_MAX_CHARS_PER_LINE 70
# endif //PPM_MAX_CHARS_PER_LINE

# ifndef PPM_VAL_BLOCK_LEN
#  define PPM_VAL_BLOCK_LEN 12
# endif //PPM_VAL_BLOCK_LEN

void	store_as_plain_ppm(t_main *m_data, char *file_name);

#endif // PPM_PARSER_H
