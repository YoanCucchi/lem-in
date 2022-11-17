/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:45:05 by ycucchi           #+#    #+#             */
/*   Updated: 2022/10/25 16:45:06 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	is_number(char **array, char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[0] == '-' || ft_isdigit(str[0]))
	{
		while (str[++i])
		{
			if (!ft_isdigit(str[i]))
			{
				free_char_array(array);
				clean_all(data, 1);
			}
		}
	}
	else
	{
		free_char_array(array);
		clean_all(data, 1);
	}
}

int	is_empty(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

void	get_start(t_data *data, char *line)
{
	char	*new;

	ft_printf("in start\n");
	if (!data->ants)
	{
		ft_strdel(&line);
		clean_all(data, 1);
	}
	ft_strdel(&line);
	// need to find a way to handle multiple comments before end info room
	if (get_next_line(0, &line) < 0)
		clean_all(data, 1);
	new = ft_strnew(ft_strlen(line));
	if (!new)
		clean_all(data, 1);
	data->start = ft_strcpy(data->start, line);
	ft_strdel(&new);
	get_rooms(data, line);
}

void	get_end(t_data *data, char *line)
{
	char	*new;
	ft_printf("in end\n");
	if (!data->ants)
	{
		ft_strdel(&line);
		clean_all(data, 1);
	}
	ft_strdel(&line);
	// need to find a way to handle multiple comments before end info room
	if (get_next_line(0, &line) < 0)
		clean_all(data, 1);
	new = ft_strnew(ft_strlen(line));
	if (!new)
		clean_all(data, 1);
	data->end = ft_strcpy(data->end, line);
	ft_strdel(&new);
	get_rooms(data, line);
}

void	map_reader(t_data *data)
{
	char	*line;
	char	**array;

	ft_printf("starting map reader \n");
	while (get_next_line(0, &line) > 0)
	{
		array = ft_strsplit(line, ' ');
		ft_printf("line = %s\n", line);
		if (!array || is_empty(line))
			clean_all(data, 1);
		else if (data->ants == 0)
			get_ants(data, line);
		else if (!ft_strcmp("##start", line))
			get_start(data, line);
		else if (!ft_strcmp("##end", line))
			get_end(data, line);
		else if ((ft_strchr(line, '-') && !array[1]) || data->dispatch == 3)
			get_links(data, line);
		else if (data->dispatch == 1 || data->dispatch == 2)
			get_rooms(data, line);
		free_char_array(array);
	}
	if (!data->start || !data->end)
		clean_all(data, 1);
	data = struct_init_2(data);
}
