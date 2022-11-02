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

# define TRUE 1
# define FALSE 0

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
	int		start_found;
	int		end_found;
	int		ants;
	int		nb_rooms;
	int		dispatch;
	int		curr_room;
	int		p_ind;
	int		good[2];
	int		new_line;
	int		init_2;
}			t_data;

/*
** Prototypes
*/

void	map_reader(t_data *data);
void	clean_all(t_data *data, int error);
t_data	*struct_init(void);
void	free_array(char **array, t_data *data, int error);

#endif