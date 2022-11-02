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

static void	is_number(char **r, t_data *data, char *str)
{
	int i;

	i = 0;
	if (str[0] == '-' || ft_isdigit(str[0]))
	{
		while (str[++i])
		{
			if (!ft_isdigit(str[i]))
				free_array(r, data, 1);
		}
	}
	else
		free_array(r, data, 1);
}

static void	validate_room(t_data *data, char *line)
{
	char **r;

	r = ft_strsplit(line, ' ');
	if (r[0][0] == 'L' || r[3] != NULL)
		free_array(r, data, 1);
	is_number(r, data, r[1]);
	is_number(r, data, r[2]);
	free_array(r, data, 0);
}

static char	*join_str(char *s1, char *s2)
{
	char *new_s;

	new_s = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s1[0] == 0)
		return (s2);
	ft_strcat(new_s, s1);
	ft_strcat(new_s, "\n");
	ft_strcat(new_s, s2);
	ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	return (new_s);
}

static int	is_empty(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

static void	get_links(t_data *data, char *line)
{
	if (data->dispatch == 2)
		data->dispatch = 3;
	if (data->dispatch != 3)
		clean_all(data, 1);
	data->links = join_str(data->links, line);
}

static void	get_rooms(t_data *data, char *line)
{
	data->dispatch = 2;
	data->rooms_list = join_str(data->rooms_list, line);
	if (line[0] == '#')
		return ;
	validate_room(data, line);
	data->nb_rooms++;
}

static void	get_ants(t_data *data, char *line)
{
	int	len;

	len = 0;
	len = ft_strlen(line);
	while (len--)
	{
		if (!ft_isdigit(line[len]))
			clean_all(data, 1);
	}
	data->ants = ft_atoi(line);
	ft_printf("ants = %d\n", data->ants);
}

void	map_reader(t_data *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (!data->ants)
			get_ants(data, line);
		else if (ft_strchr(line, '-') || data->dispatch == 3)
			get_links(data, line);
		else if ((data->dispatch == 1 || data->dispatch == 2) && !is_empty(line))
			get_rooms(data, line);
		else
		{
			ft_printf("else\n");
			clean_all(data, 1);
		}
	}
}
