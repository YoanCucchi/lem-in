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

static void	trim_room_array(t_data *data) // need to add extra malloc protection
{
	char	**line;
	char	*new;
	int		i;

	i = 0;
	line = ft_strsplit(data->rooms_list, ' ');
	if (!line)
		clean_all(data, 1);
	ft_strdel(&data->rooms_trim);
	data->rooms_trim = "";
	while (line[i])
	{
		new = ft_strnew(ft_strlen(data->rooms_trim) + 1);
		if (!new)
			clean_all(data, 1);
		new = ft_strncpy(new, data->rooms_trim, ft_strlen(data->rooms_trim));
		if (i != 0)
			ft_strdel(&data->rooms_trim);
		if (ft_strcmp(new, ""))
				new = ft_strcat(new, " ");
		data->rooms_trim = ft_strjoin(new, line[i]);
		ft_strdel(&new);
		i += 3;
	}
	free_char_array(line);
}

void	make_rooms_array(t_data *data) // need to add extra malloc protection
{
	char	**line;
	int		i;
	int		j;

	trim_room_array(data);
	data->rooms[0] = ft_strdup(data->trim_start);
	data->rooms[data->nb_rooms - 1] = ft_strdup(data->trim_end);
	line = ft_strsplit(data->rooms_trim, ' ');
	i = -1;
	j = 1;
	while (line[++i] && j < data->nb_rooms)
	{
		ft_printf("line[i] = %s\n", line[i]);

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
	ft_printf("data->rooms[0] = %s\n", data->rooms[0]);
}
