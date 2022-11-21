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
				free_char_array(data, array, 1);
		}
	}
	else
		free_char_array(data, array, 1);
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
	char	**trim;

	if (!data->ants)
		clean_line_all(data, line);
	ft_strdel(&line);
	if (get_next_line(0, &line) < 0)
		clean_all(data, 1);
	while (line[0] == '#')
	{
		ft_strdel(&line);
		if (get_next_line(0, &line) < 0)
			clean_all(data, 1);
	}
	data->start = ft_strcpy(data->start, line);
	if (!data->start)
		clean_line_all(data, line);
	trim = ft_strsplit(data->start, ' ');
	if (!trim)
		clean_line_all(data, line);
	data->trim_start = ft_strcpy(data->trim_start, trim[0]);
	free_char_array(data, trim, 0);
	if (!data->trim_start)
		clean_line_all(data, line);
	get_rooms(data, line);
}

void	get_end(t_data *data, char *line)
{
	char	**trim;

	if (!data->ants)
		clean_line_all(data, line);
	ft_strdel(&line);
	if (get_next_line(0, &line) < 0)
		clean_all(data, 1);
	while (line[0] == '#')
	{
		ft_strdel(&line);
		if (get_next_line(0, &line) < 0)
			clean_all(data, 1);
	}
	data->end = ft_strcpy(data->end, line);
	if (!data->end)
		clean_line_all(data, line);
	trim = ft_strsplit(data->end, ' ');
	if (!trim)
		clean_line_all(data, line);
	data->trim_end = ft_strcpy(data->trim_end, trim[0]);
	free_char_array(data, trim, 0);
	if (!data->trim_end)
		clean_line_all(data, line);
	get_rooms(data, line);
}

void	map_reader(t_data *data)
{
	char	*line;
	char	**array;

	while (get_next_line(0, &line) > 0)
	{
		array = ft_strsplit(line, ' ');
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
		free_char_array(data, array, 0);
	}
	if (!ft_strcmp(data->start, "") || !ft_strcmp(data->end, ""))
		clean_all(data, 1);
	data = struct_init_2(data);
}
