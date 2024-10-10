/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iziane <iziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:39 by iziane            #+#    #+#             */
/*   Updated: 2024/10/09 22:47:49 by iziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_42_H
# define PARSER_42_H

# include <stdlib.h>
# include <ft_scene.h>
# include <stdint.h>
# include <ft_tuple.h>
# include <ft_colors.h>
# include <stdnoreturn.h>

# ifndef PARSER_OFFSET_SPHERE
#  define PARSER_OFFSET_SPHERE 0.0003
# endif //PARSER_OFFSET_SPHERE
# ifndef PARSER_OFFSET_PLANE
#  define PARSER_OFFSET_PLANE 0.0005
# endif //PARSER_OFFSET_PLANE
# ifndef PARSER_OFFSET_LIGHT
#  define PARSER_OFFSET_LIGHT 0.0007
# endif //PARSER_OFFSET_LIGHT
# ifndef PARSER_OFFSET_CAMERA
#  define PARSER_OFFSET_CAMERA 0.00011
# endif //PARSER_OFFSET_CAMERA
# ifndef PARSER_OFFSET_CYLINDER
#  define PARSER_OFFSET_CYLINDER 0.00013
# endif //PARSER_OFFSET_CYLINDER

# ifndef PARSER_MEM_SIZE
#  define PARSER_MEM_SIZE 10000
# endif //PARSER_MEM_SIZE
# ifndef PARSER_HASH_PRIME
#  define PARSER_HASH_PRIME 31
# endif //PARSER_HASH_PRIME
# ifndef PARSER_HASH_SCALAR
#  define PARSER_HASH_SCALAR 1000
# endif //PARSER_HASH_SCALAR

typedef struct s_trans_cy_norm
{
	t_matrix	rotation;
	t_matrix	scaleing_radius;
	t_matrix	translation;
	t_matrix	transformation;
	t_vec		rot_axis;
	double		angle;
}				t_trans_cy_norm;

typedef struct s_main	t_main;

void			parser(t_main *m_data, char *path);

void			parse_camera(t_main *m_data, char *line);
void			parse_light(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
void			parse_plane(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
void			parse_sphere(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
void			parse_cylinder(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
//Cone
void			parse_cone(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
void			parse_double_cone(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
void			parse_spot_light(t_main *m_data, char *line,
					size_t mem_points[PARSER_MEM_SIZE]);
void			str_to_fcolor(char *str, t_fcolor *ret, char **str_ptr);
void			str_to_tuple(char *str, t_tuple *ret, char **str_ptr, double w);

size_t			parser_hash_point(t_point point);
size_t			parser_get_mem_count(size_t mem[PARSER_MEM_SIZE], \
					t_point point);
void			parser_inc_mem(size_t mem[PARSER_MEM_SIZE], t_point point);
t_point			handle_point_collision(size_t mem_points[PARSER_MEM_SIZE],
					t_point point, double obj_modulo_prime);
void			parse_ambient(t_main *m_data, char *line);

noreturn void	parser_error(char *str, char *file, int line, int exit_stat);
void			skip_whitespace(char **str);
void			skip_float(char **str);

//better parser
void			better_parser(t_main *m_data, char *setup_file);

#endif //PARSER_42_H
