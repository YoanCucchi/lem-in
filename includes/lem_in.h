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

typedef struct s_data {
	char	**rooms;
	int		**tab;
	char	*start;
	char	*end;
	char	*rooms_list;
	char	*ants_str;
	char	*links;
	int		*path;
	int		ants;
	int		nb_rooms;
	int		dispatch;
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
void	free_char_array(char **array);

#endif