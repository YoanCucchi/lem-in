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

void	reset_int_array(t_data *data, int *connections, int full)
{
	int	i;

	i = -1;
	while (++i < data->nb_rooms)
		connections[i] = 0;
	if (full)
	free(connections);
}

void	reset_path(t_data *data)
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

void	reset_visited(t_data *data)
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
	i = 0;
	while (i < data->connections_index)
	{
		ft_printf("i = %d\n", i);
		ft_printf("data->dead_connections[i] = %d\n", data->dead_connections[i]);
		data->rooms[data->dead_connections[i]].visited = 1;
		i++;
	}
	ft_printf("after visited reset \n");
}

void	store_final_path(t_data *data, int i)
{
	int	j;

	j = 0;
	ft_printf(" STORE IN FINAL PATH\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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

	connections = (int *)malloc(sizeof(int) * data->nb_rooms * 200); // malloc protec
	reset_int_array(data, connections, 0);
	i = 0;
	winner = 0;
	if (!find_starting_links(data, connections)) // find and copy starting links
	{
		reset_int_array(data, connections, 1);
		ft_printf("free avant return\n");
		return ;
	}
	if (connections[i] && connections[i] != data->nb_rooms - 1)
	{
		while (!winner && connections)
		{
			if (data->over == 1)
			{	
				ft_printf("data over TOUJOURS = à 1\n");
				break ;
			}
			connections = find_connections(data, connections);
			if (data->over == 1)
			{
				ft_printf("data->over bien de passer a 1\n");
				ft_printf("on reset et on break\n");
				data->over = 0;
				break ;
			}
			i = 0;
			while (connections[i] && !data->over)
			{
				if (connections[i] == data->nb_rooms - 1)
				{
					ft_printf("winner = %d\n", i);
					winner = 1;
					store_final_path(data, i);
					reset_visited(data);
					reset_int_array(data, connections, 0);
				}
				i++;
			}
		}
		reset_path(data);
	}
	ft_printf("juste avant free\n");
	print_connections(connections);
	reset_int_array(data, connections, 1);
	ft_printf("connections a été free\n");
	find_path(data);
}