/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:50:39 by ycucc	hi           #+#    #+#             */
/*   Updated: 2022/11/07 12:50:40 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	trim_array(t_data *data)
{
	int		i;
	char	**trim;

	i = -1;
	while (++i < data->nb_rooms)
	{
		trim = ft_strsplit(data->rooms[i], ' ');
		free(data->rooms[i]);
		// here we can add some check for trim[0] value
		data->rooms[i] = ft_strdup(trim[0]);
		free_char_array(trim);
	}
}

void	make_rooms_array(t_data *data)
{
	int		i;
	int		j;
	char	**line;

	i = -1;
	j = -1;
	line = ft_strsplit(data->rooms_list, '\n');
	while (line[++i] && ++j < data->nb_rooms)
	{
		if (j == 0)
			data->rooms[i] = ft_strdup(data->start);
		else
		{
			if (!ft_strcmp(line[i], data->end))
				j++;
			if (j < data->nb_rooms)
				data->rooms[i] = ft_strdup(line[j]);
		}
	}
	data->rooms[data->nb_rooms - 1] = ft_strdup(data->end);
	free_char_array(line);
	trim_array(data);
}
