/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:50:39 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/07 12:50:40 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_rooms_array(t_data *data)
{
	int		i;
	int		j;
	char	**line;
	// char	**splitter;

	i = 0;
	j = 0;
	line = ft_strsplit(data->rooms_list, '\n');
	while (line[i] && j < data->nb_rooms)
	{
		// splitter = ft_strsplit(line[i], ' ');
		ft_printf("line[i] = %s\n", line[i]);
		ft_printf("[i] = %d\n", i);
		ft_printf("[j] = %d\n", j);
		if (j == 0)
		{
			ft_printf("in first if start\n");
			data->rooms[i] = ft_strdup(data->start);
			i++;
			j++;
		}
		else
		{
			ft_printf("inside else\n");
			if (!ft_strcmp(line[i], data->end))
				j++;
			data->rooms[i] = ft_strdup(line[j]);
			i++;
			j++;
		}
	}
	data->rooms[data->nb_rooms - 1] = ft_strdup(data->end);
	free_char_array(data, line);
}
