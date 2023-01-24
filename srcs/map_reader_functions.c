/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:25:26 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/23 18:25:30 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_ants(t_data *data, char *line)
{
	int		i;
	char	*s;

	i = 0;
	ft_printf("ant line = %s\n", line);
	if (line[0] == '#')
	{
		ft_printf("# spotted\n");
		return (ft_strdel(&line));
	}
	data->dispatch = 1;
	s = ft_strtrim(line);
	ft_printf("ant line after strtrim= %s\n", line);
	if (!s)
		clean_line_all(data, line);
	while (s[i] != '\n' && s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			clean_line_array_all(data, s, line);
		i++;
	}
	data->ants = ft_atoi(s);
	if (data->ants <= 0)
		clean_line_array_all(data, s, line);
	ft_strdel(&s);
	ft_strdel(&line);
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

void	get_rooms(t_data *data, char *line)
{
	char	*new;

	data->dispatch = 2;
	if (line[0] == '#')
		return (ft_strdel(&line));
	new = ft_strnew(ft_strlen(data->rooms_list) + 1);
	if (!new)
		clean_line_all(data, line);
	new = ft_strncpy(new, data->rooms_list, ft_strlen(data->rooms_list));
	ft_strdel(&data->rooms_list);
	if (ft_strcmp(new, ""))
		new = ft_strcat(new, " ");
	data->rooms_list = ft_strjoin(new, line);
	if (!data->rooms_list)
		clean_line_array_all(data, new, line);
	ft_strdel(&new);
	validate_room(data, line);
	data->nb_rooms++;
	ft_strdel(&line);
}

void	get_links(t_data *data, char *line)
{
	char	*new;

	new = NULL;
	if (data->dispatch == 2)
		data->dispatch = 3;
	if (data->dispatch != 3)
		clean_all(data, 1);
	if (line[0] == '#')
		return (ft_strdel(&line));
	new = ft_strnew(ft_strlen(data->links) + 1);
	if (!new)
		clean_line_array_all(data, new, line);
	new = ft_strncpy(new, data->links, ft_strlen(data->links));
	ft_strdel(&data->links);
	if (ft_strcmp(new, ""))
		new = ft_strcat(new, "\n");
	data->links = ft_strjoin(new, line);
	if (!data->links)
		clean_line_array_all(data, new, line);
	ft_strdel(&new);
	ft_strdel(&line);
}
