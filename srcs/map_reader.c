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

static void	validate_room(t_data *data, char *line)
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
	char	*new;

	new = NULL;
	if (data->dispatch == 2)
		data->dispatch = 3;
	if (data->dispatch != 3)
		clean_all(data, 1);
	new = ft_strnew(ft_strlen(data->links));
	free(data->links);
	data->links = ft_strjoin(new, line);
	free(new);
}

static void	get_rooms(t_data *data, char *line)
{
	char	*new;

	data->dispatch = 2;
	new = ft_strnew(ft_strlen(data->links));
	free(data->rooms_list);
	data->rooms_list = ft_strjoin(new, line);
	free(new);
	if (line[0] == '#')
	{
		ft_printf("return it's a comment\n");
		return ;
	}
	validate_room(data, line);
	data->nb_rooms++;
}

static void	get_ants(t_data *data, char *line)
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
	free(s);
}

void	map_reader(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		ft_printf("line = [%s]\n", line);
		if (!data->ants)
		{
			ft_printf("inside first if\n");
			get_ants(data, line);
		}
		else if (ft_strchr(line, '-') || data->dispatch == 3)
		{
			ft_printf("inside first else if\n");
			get_links(data, line);
			ft_strdel(&line);
		}
		else if ((data->dispatch == 1 || data->dispatch == 2) && !is_empty(line))
		{
			ft_printf("inside second else if\n");
			get_rooms(data, line);
			ft_strdel(&line);
		}
		else
		{
			ft_printf("inside first else\n");
			ft_printf("else\n");
			clean_all(data, 1);
		}
		ft_strdel(&line);
		ft_printf("line freed\n");
	}
}
