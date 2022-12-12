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

// static void	clean_path(t_data *data)
// {
// 	int	reset;

// 	reset = -1;
// 	while (++reset < data->nb_rooms - 1)
// 	{
// 		ft_printf("\n\n\n\n\n\n-----------------------------------------\n");
// 		ft_printf("data->path_i = %d\n",data->path_i);
// 		ft_printf("reset = %d", reset);
// 		data->path[data->path_i][reset] = 0;
// 	}
// 		data->rooms[data->path[data->path_i][1]].visited = 0;
// }

static int	update_visited(t_data *data)
{
	int	index;
	int	print;

	print = 0;
	ft_printf("data->path = ");
	while (data->path[0][++print])
		ft_printf("%d - ", data->path[data->path_i - 1][print]);
	ft_printf("\n");
	index = data->nb_rooms - 1;
	ft_printf("index = %d\n", index);
	ft_printf("data->path_i = %d\n", data->path_i);
	ft_printf("data->rooms[R1].visited = %d\n", data->rooms[1].visited);
	ft_printf("data->rooms[R2].visited = %d\n", data->rooms[2].visited);
	ft_printf("data->rooms[R3].visited = %d\n", data->rooms[3].visited);
	ft_printf("data->rooms[R4].visited = %d\n", data->rooms[4].visited);
	ft_printf("data->rooms[R5].visited = %d\n", data->rooms[5].visited);
	ft_printf("data->rooms[R6].visited = %d\n", data->rooms[6].visited);
	ft_printf("data->rooms[R7].visited = %d\n", data->rooms[7].visited);
	while (data->path[data->path_i - 1][--data->step])
	{
		// l'idée c'est de visited-- la room visité et de continuer dans les index --
		// jusqu'a ce qu'en faisant visited-- la room.visited tombe à 0.
		// la on veut visited-- l'index - 1 et reprendre la recherche de path
		ft_printf("inside loop\n");
		ft_printf("index = %d\n", index);
		ft_printf("data->step = %d\n", data->step);
		ft_printf("data->path[data->path_i - 1][data->step - 1] = %d\n", data->path[data->path_i - 1][data->step - 1]);
		ft_printf("visited = %d\n", data->rooms[data->path[data->path_i - 1][data->step - 1]].visited);
		if (data->rooms[data->path[data->path_i - 1][data->step - 1]].visited - 1 > 0 &&\
			data->path[data->path_i - 1][data->step - 1] != 0) // 0 = start
		{
			ft_printf("before data->rooms[data->path[data->path_i - 1][data->step - 1]].visited = %d\n", data->rooms[data->path[data->path_i - 1][data->step - 1]].visited);
			data->rooms[data->path[data->path_i - 1][data->step - 1]].visited--;
			ft_printf("after data->rooms[data->path[data->path_i - 1][data->step - 1]].visited = %d\n", data->rooms[data->path[data->path_i - 1][data->step - 1]].visited);
		}
		else if (data->rooms[data->path[data->path_i - 1][data->step - 1]].visited - 1 == 0)
		{
			data->rooms[data->path[data->path_i - 1][data->step - 1]].visited--;
			if (data->step - 2 > 0)
			data->rooms[data->path[data->path_i - 1][data->step - 2]].visited--;
			data->step = 0;
			return 1;
		}
	}
	data->step = 0;
	return (0);
}

static int	already_in_path(t_data *data, int j)
{
	int	test;

	// i = 4 j = 1
	// ft_printf("------------------------------------------------------------\n");
	// ft_printf("j already in path = %d\n", j);
	test = data->path_j;
	// ft_printf("test = %d\n", test);
	while (test--)
	{
		// ft_printf("data->path[data->path_i][test] = %d\n", data->path[data->path_i][test]);
		if (data->path[data->path_i][test] == j)
			return(1);
	}
	// ft_printf("------------------------------------------------------------\n");
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
		// ft_printf("data->tab[%d]", i);
		// ft_printf("has %d links\n", links);
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
	// problem car rooms[2].visited = 0  du coup il atteint un j trop grand et go avec 
	// i = 0 et rentre dans R3 
	// solution if j > nb room delete path ???
	int	j;
	
	j = -1;
	while (++j < data->nb_rooms - 1 && data->path_j < data->nb_rooms - 1) // we search for links from start
	{
		if (data->tab[i][j] && data->rooms[j].visited && !already_in_path(data, j)) // there's a link
		{
			if (i == 0)
			{
				data->path[data->path_i][0] = 0;
				if (data->path_j == 0)
					data->path_j++;
				data->step++;
			}
			data->path[data->path_i][data->path_j] = j;
			data->path_j++;
			data->step++;
			// in this if we need to find a way to exclude when there another
			// link possible with a room != end
			if (data->tab[i][data->nb_rooms - 1] || data->tab[j][data->nb_rooms - 1]) // we are in the last room
			{

				// ft_printf("------------------------------------------------------------\n");
				// ft_printf("END FOUND\n");
				data->path[data->path_i][data->path_j] = data->nb_rooms - 1;
				data->path_i++;
				data->path_j = 0;
				data->step++;
				if (update_visited(data))
					solver(data, 0);
				else
					return (1);
			}
			solver(data, j);
		}
	}
	ft_printf("j = %d", j);
	if (j > data->nb_rooms - 1)
		solver(data, 0);
	ft_printf("\n\nEND\n\n");
	// check if we have at least 1 path if so return 1 else return 0
	return (ft_printf("\n\nEND\n\n"), 1);
}
