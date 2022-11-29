/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:22:14 by ycucchi           #+#    #+#             */
/*   Updated: 2022/10/25 15:22:16 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** Headers
*/

# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/*
** define
*/

/*
** Structures
*/

typedef struct s_rooms {
	char	*name;
	int		visited;
}			t_rooms;

typedef struct s_data {
	t_rooms	*rooms;
	int		**tab;
	char	*start;
	char	*end;
	char	*trim_start;
	char	*trim_end;
	char	*rooms_list;
	char	*rooms_trim;
	char	*links;
	char	*map;
	int		*path;
	int		start_found;
	int		end_found;
	int		ants;
	int		nb_rooms;
	int		dispatch;

	int		next_room;
	int		curr_room;
	int		p_ind;
	int		init_2;
}			t_data;

/*
** Prototypes
*/

void	map_reader(t_data *data);
void	clean_all(t_data *data, int error);
t_data	*struct_init(t_data *data);
void	validate_room(t_data *data, char *line);
void	get_rooms(t_data *data, char *line);
void	get_start(t_data *data, char *line);
void	get_end(t_data *data, char *line);
void	get_links(t_data *data, char *line);
void	get_ants(t_data *data, char *line);
void	is_number(char **array, char *str, t_data *data);
int		is_empty(char *str);
void	make_rooms_array(t_data *data);
t_data	*struct_init_2(t_data *data);
void	tab_array(t_data *data);
void	free_char_array(t_data *data, char **array, int leave);
void	print_matrix(t_data *data);
void	clean_line_all(t_data *data, char *line);
void	free_tab_array(t_data *data, int **tab);
void	clean_line_array_all(t_data *data, char *s, char *line);
void	result(t_data *data);
void	copy_map(t_data *data, char *line);
int		solver(t_data *data, int current_room);
void	nb_links(t_data *data);

#endif