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

void	find_path(t_data *data)
{
	int	*connections;
	int	i;
	int	winner;

	connections = (int *)malloc(sizeof(int) * data->nb_rooms);
	i = 0;
	winner = 0;
	// then for each connection check how much connection there is
	// and act accordingly (1 = perfect, >1 = dup path, 0 = drop)
	find_starting_links(data, connections); // find and copy starting links
	if (connections[i])
	{
		while (!winner)
		{
			connections = find_connections(data, connections);
			i = 0;
			while (connections[i++])
			{
				if (connections[i] == data->nb_rooms - 1)
				{
					ft_printf("winner = %d\n", i);
					winner = 1;
				}
			}
		}
		free(connections);
		// store winner in final path, increase path number ++
		// clear all paths, reset visited++
		// recommencer xd
	}
}