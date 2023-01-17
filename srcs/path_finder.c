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

static void	reset_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->path[i][1] || data->path[i][2])
	{
		j = 0;
		while (j++ < data->nb_rooms)
			data->path[i][j] = 0;
		i++;
	}
}

static void	reset_visited(t_data *data)
{
	int	i;
	int	j;
	int	path_index;

	i = 0;
	j = 0;
	while (i++ < data->nb_rooms)
		data->rooms[i].visited = 0;
	path_index = data->path_counter;
	while (path_index-- > 0)
	{
		j = 0;
		while (j++ < data->nb_rooms)
		{
			if (data->final_path[path_index][j] && data->final_path[path_index][j] != data->nb_rooms - 1)
				data->rooms[data->final_path[path_index][j]].visited = 1;
		}
	}
}

static void	store_final_path(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->nb_rooms)
	{
		data->final_path[data->path_counter][j] = data->path[i][j];
		j++;
	}
	data->path_counter++;
}

void	find_path(t_data *data)
{
	int	*connections;
	int	i;
	int	winner;

	connections = (int *)malloc(sizeof(int) * data->nb_rooms); // malloc protec
	i = 0;
	winner = 0;
	// then for each connection check how much connection there is
	// and act accordingly (1 = perfect, >1 = dup path, 0 = drop)
	ft_printf("DEBUT FIND PATH\n\n\n");
	if (!find_starting_links(data, connections)) // find and copy starting links
	{
		free(connections);
		return ;
	}
	if (connections[i] && connections[i] != data->nb_rooms - 1)
	{
		while (!winner)
		{
			connections = find_connections(data, connections);
			i = 0;
			while (connections[i])
			{
				if (connections[i] == data->nb_rooms - 1)
				{
					ft_printf("winner = %d\n", i);
					winner = 1;
					store_final_path(data, i);
					reset_visited(data);
					reset_connections(data, connections);
				}
				i++;
			}
		}
		reset_path(data);
		ft_printf("connections => \n");
		ft_printf("connections[0] = %d\n", connections[0]);
		ft_printf("connections[1] = %d\n", connections[1]);
		ft_printf("connections[2] = %d\n", connections[2]);
		ft_printf("connections[3] = %d\n", connections[3]);
		ft_printf("connections[4] = %d\n", connections[4]);
		ft_printf("connections[5] = %d\n", connections[5]);
		ft_printf("data->rooms[0].visited = %d\n", data->rooms[0].visited);
		ft_printf("data->rooms[1].visited = %d\n", data->rooms[1].visited);
		ft_printf("data->rooms[2].visited = %d\n", data->rooms[2].visited);
		ft_printf("data->rooms[3].visited = %d\n", data->rooms[3].visited);
		ft_printf("data->rooms[4].visited = %d\n", data->rooms[4].visited);
		ft_printf("data->rooms[5].visited = %d\n", data->rooms[5].visited);
		ft_printf("data->rooms[6].visited = %d\n", data->rooms[6].visited);
		ft_printf("data->rooms[7].visited = %d\n", data->rooms[7].visited);
		ft_printf("data->rooms[8].visited = %d\n", data->rooms[8].visited);
		ft_printf("data->rooms[9].visited = %d\n", data->rooms[9].visited);
		// store winner in final path, increase path number ++
		// clear all paths, reset visited++
		// recommencer xd
	}
	free(connections);
	find_path(data);
}