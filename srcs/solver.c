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

// static void	destroy_links(t_data *data, int i)
// {
// 	int	j;

// 	j = -1;
// 	while (++j < data->nb_rooms)
// 	{
// 		ft_printf("i = %d", i);
// 		data->tab[i][j] = 0;
// 	}
// }

static int	already_in_path(t_data *data, int j)
{
	int	test;

	// i = 4 j = 1
	ft_printf("------------------------------------------------------------\n");
	ft_printf("j already in path = %d\n", j);
	test = data->path_j;
	ft_printf("test = %d\n", test);
	while (test--)
	{
		ft_printf("data->path[data->path_i][test] = %d\n", data->path[data->path_i][test]);
		if (data->path[data->path_i][test] == j)
			return(1);
	}
	ft_printf("------------------------------------------------------------\n");
	return (0);
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
	// problem car tab[2][x] = 0 du coup il atteint un j trop grand et go avec 
	// i = 0 et rentre dans R3 
	int	j;
	
	j = -1;
	// ft_printf("i = %d\n", i);
	data->p_ind = i;
	// check all link and visited to find a way to check everything without crashing
	while (++j < data->nb_rooms - 1 && data->path_j < data->nb_rooms - 1) // we search for links from start
	{
		ft_printf("i = %d\n", i);
		ft_printf("j = %d\n", j);
		ft_printf("data->tab[i][j] = %d\n", data->tab[i][j]);
		ft_printf("data->rooms[j].visited = %d\n", data->rooms[j].visited);
		if (data->tab[i][j] && data->rooms[j].visited && !already_in_path(data, j)) // there's a link
		{
			// data->tab[j][i] = 0;
			ft_printf("i = %d\n", i);
			ft_printf("j = %d\n", j);
			ft_printf("data->path_i = %d\n", data->path_i);
			ft_printf("data->path_j = %d\n", data->path_j);
			if (i == 0)
			{
				data->path[data->path_i][0] = 0;
				if (data->path_j == 0)
					data->path_j++;
			}
			data->path[data->path_i][data->path_j] = j;
			data->path_j++;
			// ft_printf("i = %d\n", i);
			// ft_printf("j = %d\n", j);
			if (data->tab[i][data->nb_rooms - 1] || data->tab[j][data->nb_rooms - 1]) // we are in the last room
			{
				ft_printf("END FOUND\n");
				ft_printf("i = %d\n", i);
				ft_printf("j = %d\n", j);
				// ft_printf("data->p ind = %d\n", data->p_ind);
				data->rooms[data->p_ind].visited = 0; // PROBLEM HERE WITH R2/R5
				data->rooms[j].visited = 0; // PROBLEM HERE WITH R2/R5
				data->p_ind = i;
				// ft_printf("links left = %d\n", data->rooms[j].visited);
				// ft_printf("links R1 = %d\n", data->rooms[1].visited);
				// if (!data->rooms[1].visited)
					// destroy_links(data, j);
				data->path[data->path_i][data->path_j] = data->nb_rooms - 1;
				data->path_i++;
				data->path_j = 0;
				solver(data, 0);
			}
			
			solver(data, j);
		}
	}
	return (1);
}
