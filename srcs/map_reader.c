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

// static int	is_start(t_data *data, char *line)
// {
// 	ft_printf("inside start line = [%s]\n");
// 	if (!ft_strcmp(line, "##start"))
// 	{
// 		ft_printf("it's a match\n");
// 		data->start = "yolo";
// 		data->start_found = 1;
// 		return(TRUE);
// 	}
// 	return(FALSE);
// }

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
	get_ants(data, line);
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	return (TRUE);
}