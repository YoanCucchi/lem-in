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
	char	*start;
	int		start_found;
	char	*end;
	int		end_found;
	int		ants;
}			t_data;

typedef struct s_room {
	char	*name;
	int		x;
	int		y;
	struct t_room	**links;
	struct t_room	*next;
}			t_room;


/*
** Prototypes
*/

int	map_reader(t_data *data, t_room *room);
int	clean_all(t_data *data, t_room *room);

#endif