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

static void	destroy_links(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->nb_rooms)
	{
		data->tab[i][j] = 0;
	}
}

void	nb_links(t_data *data)
{
	int	i;
	int	j;
	int	links;

	i = -1;
	j = -1;
	links = 0;
	while (++i < data->nb_rooms - 1)
	{
		j = -1;
		links = 0;
		while (++j < data->nb_rooms - 1)
		{
			if (data->tab[i][j])
				links++;
		}
		ft_printf("data->tab[%d]", i);
		ft_printf("has %d links\n", links);
		data->rooms[i].visited = links;
	}
}

// static int	all_visited(t_data *data, int i)
// {
// 	int	j;

// 	j = -1;
// 	while (++j < data->nb_rooms - 1)
// 	{
// 		if (data->tab[i][j] && !data->rooms[j].visited)
// 			return (0);
// 	}
// 	return (1);
// }

int	solver(t_data *data, int i)
{
	// check if link
	int	j;
	
	j = -1;
	// ft_printf("i = %d\n", i);
	data->p_ind = i;
	// check all link and visited to find a way to check everything without crashing
	while (++j < data->nb_rooms - 1) // we search for links from start
	{
		// ft_printf("j = %d\n", j);
		if (data->tab[i][j] && (data->rooms[j].visited)) // there's a link
		{
			if (i == 0)
				ft_printf("[%s]", data->rooms[0].name);
			ft_printf("-[%s]", data->rooms[j].name);
			// ft_printf("i = %d\n", i);
			// ft_printf("j = %d\n", j);
			if (data->tab[i][data->nb_rooms - 1] || data->tab[j][data->nb_rooms - 1]) // we are in the last room
			{
				// ft_printf("i = %d\n", i);
				// ft_printf("j = %d\n", j);
				// ft_printf("data->p ind = %d\n", data->p_ind);
				data->rooms[data->p_ind].visited = 0;
				data->rooms[j].visited = 0;
				destroy_links(data, j);
				data->p_ind = i;
				// ft_printf("links left = %d\n", data->rooms[j].visited);
				// ft_printf("links R1 = %d\n", data->rooms[1].visited);
				ft_printf("-[%s]", data->rooms[data->nb_rooms - 1].name);
				ft_printf("\n\n");
				// save path?
				solver(data, 0);
			}
			// data->rooms[j].visited--;
			// ft_printf("data visited -- \n");
			solver(data, j);
		}
	}
	return (0);
}
