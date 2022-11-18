/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:57 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/04 18:33:59 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clean_line_array_all(t_data *data, char *s, char *line)
{
	if (s)
		ft_strdel(&s);
	if (line)
		ft_strdel(&line);
	clean_all(data, 1);
}

void	validate_room(t_data *data, char *line)
{
	char	**r;

	r = ft_strsplit(line, ' ');
	if (r[0][0] == 'L' || r[3] != NULL)
	{
		free_char_array(r);
		clean_all(data, 1);
	}
	is_number(r, r[1], data);
	is_number(r, r[2], data);
	free_char_array(r);
}

void	get_rooms(t_data *data, char *line)
{
	char	*new;

	data->dispatch = 2;
	if (line[0] == '#')
		return (ft_strdel(&line));
	new = ft_strnew(ft_strlen(data->rooms_list) + 1);
	if (!new)
		clean_all(data, 1);
	new = ft_strncpy(new, data->rooms_list, ft_strlen(data->rooms_list));
	ft_strdel(&data->rooms_list);
	if (ft_strcmp(new, ""))
		new = ft_strcat(new, " ");
	ft_printf("new room = %s\n", new);
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
	ft_printf("inside links\n");
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

void	get_ants(t_data *data, char *line)
{
	int		i;
	char	*s;

	i = -1;
	ft_printf("line for ants %s\n", line);
	if (line[0] == '#')
		return (ft_strdel(&line));
	s = ft_strtrim(line);
	ft_printf("s = %s\n", s);
	if (!s)
	{
		ft_strdel(&line);
		clean_all(data, 1);
	}
	while (s[++i] != '\n' && s[++i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			clean_line_array_all(data, s, line);
	}
	data->ants = ft_atoi(s);
	ft_printf("ants = %d\n", data->ants);
	if (data->ants <= 0)
		clean_line_array_all(data, s, line);
	ft_strdel(&s);
	ft_strdel(&line);
}
