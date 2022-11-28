/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycucchi <yoan066@yahoo.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:16:40 by ycucchi           #+#    #+#             */
/*   Updated: 2022/11/22 14:16:42 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	all_visited(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->nb_rooms - 1)
	{
		if (data->tab[i][j] && !data->rooms[j].visited)
			return (0);
	}
	return (1);
}

static int	has_multiple_links(t_data *data, int i)
{
	int	j;
	int	links;

	j = -1;
	links = 0;
	while (++j < data->nb_rooms - 1)
	{
		if (data->tab[i][j])
			links++;
	}
	ft_printf("data->tab[%d]", i);
	ft_printf("has %d links\n", links);
	if (links > 1)
		return (1);
	return (0);
}

int	solver(t_data *data, int i)
{
	// check if link
	int	j;
	
	j = -1;
	// check all link and visited to find a way to check everything without crashing
	while (++j < data->nb_rooms - 1) // we search for links from start
	{
		if (data->tab[i][j] && (!data->rooms[j].visited || data->rooms[j].visited == 2)) // there's a link
		{
			// ft_printf("i = %d\n", i);
			// ft_printf("j = %d\n", j);
			if (i == 0)
				ft_printf("[%s]", data->rooms[0].name);
			ft_printf("-[%s]", data->rooms[j].name);
			if (data->tab[i][data->nb_rooms - 1] || data->tab[j][data->nb_rooms - 1]) // we are in the last room
			{
				if (has_multiple_links(data, j) && !all_visited(data, j))
					data->rooms[j].visited = 2;
				else
					data->rooms[j].visited = 1;
				ft_printf("data->rooms[j].visited = %d\n", data->rooms[j].visited);
				ft_printf("j = %d\n", j);
				ft_printf("-[%s]", data->rooms[data->nb_rooms - 1].name);
				ft_printf("i = %d\n", i);
				ft_printf("j = %d\n", j);
				ft_printf("data->tab[j][data->nb_rooms - 1] = %d\n", data->tab[i][data->nb_rooms - 1]);
				ft_printf("data->tab[i][data->nb_rooms - 1] = %d\n", data->tab[i][data->nb_rooms - 1]);
				ft_printf("\nit's last room exit for now\n");
				// save path?
				solver(data, 0);
			}
			if (has_multiple_links(data, j) && !all_visited(data, j))
				data->rooms[j].visited = 2;
			else
				data->rooms[j].visited = 1;
			solver(data, j);
		}
	}
	return (0);
}
