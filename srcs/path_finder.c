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

// static int	is_there_any_solution(t_data *data, int *connections)
// {
// 	int	i;

// 	i = 0;
// 	while (connections[i])
// 	{
// 		if ()
// 	}
// }

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
	if (!find_starting_links(data, connections)) // find and copy starting links
	{
		ft_printf("free\n");
		free(connections);
		return ;
	}
	if (connections[i] && connections[i] != data->nb_rooms - 1)
	{
		while (!winner && connections)
		{
			if (find_connections(data, connections) != NULL)
				connections = find_connections(data, connections);
			else
			{
				// free(connections);
				break ;
			}
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
	}
	free(connections);
	find_path(data);
}