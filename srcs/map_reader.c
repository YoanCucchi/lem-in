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

}

static void	get_rooms(t_data *data, char *line)
{

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
}

int	map_reader(t_data *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (is_empty(line))
			clean_all(data, 1);
		if (!data->ants)
			get_ants(data, line);
		else if (ft_strchr(line, '-') || data->dispatch == 3)
			get_links(data, line);
		else if ((data->dispatch == 1 || data->dispatch == 2))
			get_rooms(data, line);
		else
			clean_all(data, 1);
	}
	return (TRUE);
}
