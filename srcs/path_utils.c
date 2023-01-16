/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:29:09 by ycucchi           #+#    #+#             */
/*   Updated: 2023/01/04 19:29:11 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_starting_links(t_data *data, int *connections)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// first fonction to check connections with start and create paths
	while (!data->rooms[j].visited && j < data->nb_rooms)
	{
		if (data->tab[0][j])
		{
			connections[i] = j;
			data->rooms[j].visited = 1;
			data->path[data->path_i++][data->path_j] = j;
			i++;
		}
		j++;
	}
	data->path_j++;
}

void	reset_connections(t_data *data, int *connections)
{
	int	i;

	i = 0;
	while (i++ < data->nb_rooms)
		connections[i] = 0;
}

int	*find_connections(t_data *data, int *connections)
{
	int	i;
	int	j;
	int	k;
	int	*save;

	save = (int *)malloc(sizeof(int) * data->nb_rooms);
	i = 0;
	k = 0;
	data->path_i = 0;
	while (connections[i])
	{
		j = 0;
		while(j < data->nb_rooms)
		{
			if (data->tab[connections[i]][j] && !data->rooms[j].visited)
			{
				ft_printf("j = %d\n", j);
				data->rooms[j].visited = 1;
				data->path[data->path_i][data->path_j] = j;
				data->path_i++;
				save[k] = j;
				k++;
			}
			j++;
		}
		i++;
	}
	reset_connections(data, connections);
	i = 0;
	while (i < data->nb_rooms)
	{
		if (save[i])
			connections[i] = save[i];
		i++;
	}
	free(save);
	return (connections);
}