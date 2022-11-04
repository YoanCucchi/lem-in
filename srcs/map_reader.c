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

void	is_number(char **r, t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[0] == '-' || ft_isdigit(str[0]))
	{
		while (str[++i])
		{
			if (!ft_isdigit(str[i]))
			{
				j = -1;
				while (r[++j])
					free(r[j]);
				free(r);
				clean_all(data, 1);
			}
		}
	}
	else
	{
		j = -1;
		while (r[++j])
			free(r[j]);
		free(r);
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

	ft_strdel(&line);
	get_next_line(0, &line);
	ft_printf("line = [%s]\n", line);
	new = ft_strnew(ft_strlen(line));
	data->start = ft_strcpy(data->start, line);
	ft_strdel(&new);
	get_rooms(data, line);
}

void	get_end(t_data *data, char *line)
{
	char	*new;

	ft_strdel(&line);
	get_next_line(0, &line);
	ft_printf("line = [%s]\n", line);
	new = ft_strnew(ft_strlen(line));
	data->end = ft_strcpy(data->end, line);
	ft_strdel(&new);
	get_rooms(data, line);
}

void	map_reader(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		ft_printf("line = [%s]\n", line);
		if (is_empty(line))
			clean_all(data, 1);
		else if (!ft_strcmp(line, "##start"))
			get_start(data, line);
		else if (!ft_strcmp(line, "##end"))
			get_end(data, line);
		else if (!data->ants)
			get_ants(data, line);
		else if (ft_strchr(line, '-') || data->dispatch == 3)
			get_links(data, line);
		else if (data->dispatch == 1 || data->dispatch == 2)
			get_rooms(data, line);
	}
}
