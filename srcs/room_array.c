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

static void	storing_start_end_rooms(t_data *data)
{
	data->rooms[0].name = (char *)ft_memalloc(sizeof(char) * 100);
	if (!data->rooms[0].name)
		clean_all(data, 1);
	data->rooms[0].name = ft_strcpy(data->rooms[0].name, data->trim_start);
	data->rooms[data->nb_rooms - 1].name = (char *)ft_memalloc(sizeof(char) * 100);
	if (!data->rooms[data->nb_rooms - 1].name)
		clean_all(data, 1);
	data->rooms[data->nb_rooms - 1].name = \
	ft_strcpy(data->rooms[data->nb_rooms - 1].name, data->trim_end);
}

static void	storing_rooms(t_data *data, char **line, int i, int j)
{
	while (line[++i] && j < data->nb_rooms - 1)
	{
		if (!ft_strcmp(data->trim_start, line[i]))
			data->start_found++;
		else if (!ft_strcmp(data->trim_end, line[i]))
			data->end_found++;
		else
		{
			data->rooms[j].name = (char *)ft_memalloc(sizeof(char) * 50);
			if (data->start_found > 1 || data->end_found > 1)
				free_char_array(data, line, 1);
			else
			{
				data->rooms[j].name = ft_strcpy(data->rooms[j].name, line[i]);
				if (!data->rooms[j].name)
					free_char_array(data, line, 1);
				j++;
			}
		}
	}
}

static void	trim_room_array(t_data *data, char **line, int i)
{
	char	*new;

	line = ft_strsplit(data->rooms_list, ' ');
	if (!line)
		clean_all(data, 1);
	ft_strdel(&data->rooms_trim);
	data->rooms_trim = "";
	while (line[i])
	{
		new = ft_strnew(ft_strlen(data->rooms_trim) + 1);
		if (!new)
			free_char_array(data, line, 1);
		new = ft_strncpy(new, data->rooms_trim, ft_strlen(data->rooms_trim));
		if (i != 0)
			ft_strdel(&data->rooms_trim);
		if (ft_strcmp(new, ""))
				new = ft_strcat(new, " ");
		data->rooms_trim = ft_strjoin(new, line[i]);
		ft_strdel(&new);
		if (!data->rooms_trim)
			free_char_array(data, line, 1);
		i += 3;
	}
	free_char_array(data, line, 0);
}

void	make_rooms_array(t_data *data)
{
	char	**line;
	int		i;
	int		j;

	i = 0;
	line = NULL;
	trim_room_array(data, line, i);
	line = ft_strsplit(data->rooms_trim, ' ');
	if (!line)
		clean_all(data, 1);
	i = -1;
	j = 1;
	storing_start_end_rooms(data);
	storing_rooms(data, line, i, j);
	free_char_array(data, line, 0);
}
