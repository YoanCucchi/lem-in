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

void	make_rooms_array(t_data *data)
{
	int		i;
	int		j;
	char	**rooms_name;
	char	**rooms_trim;

	i = -1;
	j = 0;
	rooms_name = ft_strsplit(data->rooms_list, '\n');
	ft_printf("data->start = %s\n", data->start);
	if (!rooms_name)
		clean_all(data, 1);ft_printf("--------------------------------------------------------\n");
	while (rooms_name[++i] && j <= data->nb_rooms)
	{
		ft_printf("--------------------------------------------------------\n");
		ft_printf("rooms_name i = %s\n", rooms_name[i]);
		rooms_trim = ft_strsplit(rooms_name[i], ' ');
		ft_printf("rooms_trim[0] = %s\n", rooms_trim[0]);
		ft_printf("i = %d\n", i);
		ft_printf("j = %d\n", j);
		if (!ft_strcmp(rooms_name[i], data->start))
		{
			ft_printf("start found\n");
			data->rooms[0] = ft_strdup(rooms_trim[0]);
			ft_printf("we stored : %s\n", data->rooms[j]);
			ft_printf(" in data->rooms[%d]\n", j);
		}
		else if (!ft_strcmp(rooms_name[i], data->end))
		{
			ft_printf("end found\n");
			data->rooms[data->nb_rooms - 1] = ft_strdup(rooms_trim[0]);
			ft_printf("we stored : %s\n", data->rooms[j]);
		}
		else
		{
			ft_printf("in else \n");
			if (j == 0)
				j++;
			else if (j == data->nb_rooms)
				j--;
			data->rooms[j] = ft_strdup(rooms_trim[0]);
			// data->rooms[j] = rooms_trim[0];
			ft_printf("we stored : %s", data->rooms[j]);
			ft_printf(" in data->rooms[%d]\n", j);
			if (!data->rooms[j])
			{
				free_char_array(rooms_name);
				clean_all(data, 1);
			}
			j++;
			ft_printf("--------------------------------------------------------\n");
		}
		free_char_array(rooms_trim);
	}
	free_char_array(rooms_name);
}
