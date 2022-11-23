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

void	map_reader(t_data *data)
{
	char	*line;
	char	**array;

	while (get_next_line(0, &line) > 0)
	{
		copy_map(data, line);
		array = ft_strsplit(line, ' ');
		if (!array)
			clean_all(data, 1);
		if (data->ants == 0)
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
