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
	char	*new;
	char	**line;
	int		i;
	int		j;

	i = 0;
	line = ft_strsplit(data->rooms_list, ' ');
	ft_strdel(&data->rooms_list2);
	data->rooms_list2 = "";
	ft_printf("data->room_list = %s\n", data->rooms_list);
	ft_printf("data->room_list2 = %s\n", data->rooms_list2);
	while (line[i])
	{
		new = ft_strnew(ft_strlen(data->rooms_list2) + 1);
		if (!new)
			clean_all(data, 1);
		new = ft_strncpy(new, data->rooms_list2, ft_strlen(data->rooms_list2));
		if (i != 0)
			ft_strdel(&data->rooms_list2);
		if (ft_strcmp(new, ""))
				new = ft_strcat(new, " ");
		data->rooms_list2 = ft_strjoin(new, line[i]);
		ft_strdel(&new);
		i += 3;
	}
	free_char_array(line);

	ft_printf("data->room_list2 end= %s\n", data->rooms_list2);
	line = ft_strsplit(data->start, ' ');
	data->trim_start = ft_strcpy(data->trim_start, line[0]);
	free_char_array(line);
	ft_printf("data->trim_start= %s\n", data->trim_start);

	line = ft_strsplit(data->end, ' ');
	data->trim_end = ft_strcpy(data->trim_end, line[0]);
	free_char_array(line);
	ft_printf("data->trim_end= %s\n", data->trim_end);
	

	data->rooms[0] = data->trim_start;
	data->rooms[data->nb_rooms - 1] = data->trim_end;
	i = -1;
	j = 1;
	line = ft_strsplit(data->rooms_list2, ' ');
	while (line[++i] && j < data->nb_rooms)
	{
		if (!ft_strcmp(data->trim_start, line[i]))
		{
			ft_printf("we found start\n");
			data->start_found++;
		}
		else if (!ft_strcmp(data->trim_end, line[i]))
		{
			ft_printf("we found end\n");
			data->end_found++;
		}
		else if (data->start_found > 1 || data->end_found > 1)
		{
			free_char_array(line);
			clean_all(data, 1);
		}
		else
		{
			data->rooms[j] = ft_strdup(line[i]);
			j++;
		}
	}
	free_char_array(line);
}
