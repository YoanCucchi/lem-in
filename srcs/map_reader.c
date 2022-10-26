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

static int	get_ants(t_data *data, char *line)
{
	int	len;

	len = 0;
	len = ft_strlen(line);
	while (len--)
	{
		if (!ft_isdigit(line[len]))
			return (FALSE);
	}
	data->ants = ft_atoi(line);
	return(TRUE);
}

static int	get_start(t_data *data, char *line)
{
	int	ret;
	int	index;
	int	letter;

	letter = 0;
	index = 0;
	ft_strdel(&line);
	ret = get_next_line(0, &line);
	ft_printf("%s\n", line);
	if (ret <= 0)
	{
		ft_printf("ret issue\n");
		return (FALSE);
	}
	while (line[index] != '\0')
	{
		letter = line[index];
		if (letter == ' ')
			break ;
		index++;
	}
	data->start = ft_strncpy(data->start, line, index);
	data->start_found = 1;
	ft_strdel(&line);
	return (TRUE);
}

static int	get_end(t_data *data, char *line)
{
	int	ret;
	int	index;
	int	letter;

	letter = 0;
	index = 0;
	ft_strdel(&line);
	ret = get_next_line(0, &line);
	ft_printf("%s\n", line);
	if (ret <= 0)
	{
		ft_printf("ret issue\n");
		return (FALSE);
	}
	while (line[index] != '\0')
	{
		letter = line[index];
		if (letter == ' ')
			break ;
		index++;
	}
	data->end = ft_strncpy(data->end, line, index);
	data->end_found = 1;
	ft_strdel(&line);
	return (TRUE);
}

int	map_reader(t_data *data)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line(0, &line);
	if (ret <= 0)
	{
		ft_printf("ret problem \n");
		return (FALSE);
	}
	ft_printf("%s\n", line);
	if (!get_ants(data, line))
		return (FALSE);
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		if (!ft_strcmp(line, "##start") && !data->start_found)
		{
			ft_printf("start found\n");
			if (!get_start(data, line))
				return (0);
		}
		else if (!ft_strcmp(line, "##end") && !data->end_found)
		{
			ft_printf("end found\n");
			if (!get_end(data, line))
				return (0);
		}
		else if (ft_strncmp(line, "##", 2) && ft_strchr(&line[0], '#'))
		{
			ft_strdel(&line);
		}
		else if (ft_strchr(line, '-') == NULL)// we found a room
		{
			ft_printf("room found\n");
			ft_strdel(&line);
		}
		else // it's a link
		{
			ft_printf("link found\n");
			ft_strdel(&line);
		}
	}
	return (TRUE);
}