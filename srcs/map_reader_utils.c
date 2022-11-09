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

void	validate_room(t_data *data, char *line)
{
	char	**r;
	int		i;

	r = ft_strsplit(line, ' ');
	if (r[0][0] == 'L' || r[3] != NULL)
	{
		i = -1;
		while (r[++i])
			free(r[i]);
		free(r);
		clean_all(data, 1);
	}
	is_number(r, data, r[1]);
	is_number(r, data, r[2]);
	i = -1;
	while (r[++i])
		free(r[i]);
	free(r);
}

void	get_rooms(t_data *data, char *line)
{
	char	*new;

	data->dispatch = 2;
	if (line[0] == '#')
	{
		ft_strdel(&line);
		return ;
	}
	new = ft_strnew(ft_strlen(data->rooms_list) + 1);
	new = ft_strncpy(new, data->rooms_list, ft_strlen(data->rooms_list));
	ft_strdel(&data->rooms_list);
	if (ft_strcmp(new, ""))
		new = ft_strcat(new, "\n");
	data->rooms_list = ft_strjoin(new, line);
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
	{
		ft_strdel(&line);
		return ;
	}
	new = ft_strnew(ft_strlen(data->links) + 1);
	new = ft_strncpy(new, data->links, ft_strlen(data->links));
	ft_strdel(&data->links);
	if (ft_strcmp(new, ""))
		new = ft_strcat(new, "\n");
	data->links = ft_strjoin(new, line);
	ft_strdel(&new);
	ft_strdel(&line);
}

void	get_ants(t_data *data, char *line)
{
	int		i;
	char	*s;

	i = 0;
	data->dispatch = 1;
	data->ants_str = ft_strcpy(data->ants_str, line);
	data->ants = ft_atoi(line);
	s = ft_strtrim(line);
	data->ants = ft_atoi(s);
	if (data->ants <= 0)
		clean_all(data, 1);
	while (s[i] != '\n' && s[i] != 0)
	{
		if (!ft_isdigit(s[i++]))
			clean_all(data, 1);
	}
	ft_strdel(&s);
	ft_strdel(&line);
}
