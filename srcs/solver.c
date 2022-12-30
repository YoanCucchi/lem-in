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

static void set_visited(t_data *data, int round)
{
	int i = 0;

	while (i < data->nb_rooms)
	{
		int x = 0;
		while (x < data->path_counter)
		{
			int j = 0;
			while (j < round)
			{
				if (data->final_path[x][j] == i)
				{
					data->rooms[i].visited = 1;
					break;
				}
				j++;
			}
			x++;
		}
		i++;
	}
}

static void reset_visited(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_rooms)
	{
		data->rooms[i].visited = 0;
		i++;
	}
}

static void	save_path(t_data *data, int j, int round)
{
	int	i;

	ft_printf("round = %d\n", round);
	i = 0;
	while (i < round + 1)
	{
		data->final_path[data->path_counter][i] = data->path[j][i];
		i++;
	}
	data->path_counter++;
	reset_visited(data);
	set_visited(data, round);
}

void	nb_links(t_data *data) //give all links end included
{
	int	i;
	int	j;
	int	links;

	i = -1;
	j = -1;
	links = 0;
	while (++i < data->nb_rooms - 1)
	{
		data->rooms[i].links = 0;
		j = -1;
		links = 0;
		while (++j < data->nb_rooms)
		{
			if (data->tab[i][j])
				links++;
		}
		ft_printf("data->tab[%d]", i);
		ft_printf(" = %d\n", links);
		data->rooms[i].links = links;
	}
}

static void	path_first(t_data *data, int round, int path_nb)
{
	int	i;

	i = 0;
	while (i < data->nb_rooms)
	{
		ft_printf("in");
		if (data->tab[0][i] && !data->rooms[i].visited)
		{
			data->path[path_nb][round] = i;
			data->rooms[i].visited = 1;
			ft_printf("test = %d\n", i);
			path_nb++;
		}
		i++;
	}
}

int	solver(t_data *data, int i)
{
	int	path_nb;
	int	round;
	int	j;
	int	k;

	path_nb = 0;
	round = 1;
	if (i)
		nb_links(data);
	ft_printf("data->visited.links = %d\n", data->rooms[0].links);
	// je connais le nombre de lien de chaque salle
	// si start à + d'un lien valide go
	if (data->rooms[0].links > 0)
		path_first(data, round, path_nb);
	ft_printf("path_nb = %d\n", path_nb);
	round++;
	ft_printf("round = %d\n", round);
	// j'ai X paths qui correspondent au nombre de link de start
	// de la je veux trouver tous les liens que ces X paths ont.
	j = 0;
	while (j < data->nb_rooms)
	{
		k = 0;
		if (data->path[j][round - 1]) // si le path n'est pas = 0
		{
			while (k < data->nb_rooms) // nombre de lien
			{
				if (data->tab[data->path[j][round - 1]][k] && !data->rooms[k].visited)
				{
					ft_printf("j = %d\n", j);
					ft_printf("lien avec %d\n", k);
					data->path[j][round] = k;
					data->rooms[k].visited = 1;
					break;
				}
				k++;
			}
		}
		j++;
	}
	round++;
	j = 0;
	while (j < data->nb_rooms)
	{
		k = 0;
		if (data->path[j][round - 1]) // si le path n'est pas = 0
		{
			if (data->tab[data->path[j][round - 1]][data->nb_rooms -1] || \
			data->tab[data->nb_rooms -1][data->path[j][round - 1]])
			{
				data->path[j][round] = data->nb_rooms - 1;
				data->rooms[data->path[j][round - 1]].visited = 1;
				save_path(data, j, round); // SAVETHEPATH
				break;
			}
			while (k < data->nb_rooms) // nombre de lien
			{
				// il faut que je rajoute un check pour voir si il y a un lien
				// avec la room end, je dois stop et save path
				if (data->tab[data->path[j][round - 1]][k] && !data->rooms[k].visited)
				{
					ft_printf("j = %d\n", j);
					ft_printf("lien avec %d\n", k);
					data->path[j][round] = k;
					data->rooms[k].visited = 1;
					if (k == data->nb_rooms - 1)
						save_path(data, j, round); // SAVETHEPATH
					break;
				}
				k++;
			}
		}
		j++;
	}
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[0][0] = %d\n", data->path[0][0]);
	ft_printf("data->path[0][1] = %d\n", data->path[0][1]);
	ft_printf("data->path[0][2] = %d\n", data->path[0][2]);
	ft_printf("data->path[0][3] = %d\n", data->path[0][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[1][0] = %d\n", data->path[1][0]);
	ft_printf("data->path[1][1] = %d\n", data->path[1][1]);
	ft_printf("data->path[1][2] = %d\n", data->path[1][2]);
	ft_printf("data->path[1][3] = %d\n", data->path[1][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[2][0] = %d\n", data->path[2][0]);
	ft_printf("data->path[2][1] = %d\n", data->path[2][1]);
	ft_printf("data->path[2][2] = %d\n", data->path[2][2]);
	ft_printf("data->path[2][3] = %d\n", data->path[2][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[0][0] = %d\n", data->final_path[0][0]);
	ft_printf("data->final_path[0][1] = %d\n", data->final_path[0][1]);
	ft_printf("data->final_path[0][2] = %d\n", data->final_path[0][2]);
	ft_printf("data->final_path[0][3] = %d\n", data->final_path[0][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[1][0] = %d\n", data->final_path[1][0]);
	ft_printf("data->final_path[1][1] = %d\n", data->final_path[1][1]);
	ft_printf("data->final_path[1][2] = %d\n", data->final_path[1][2]);
	ft_printf("data->final_path[1][3] = %d\n", data->final_path[1][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->final_path[2][0] = %d\n", data->final_path[2][0]);
	ft_printf("data->final_path[2][1] = %d\n", data->final_path[2][1]);
	ft_printf("data->final_path[2][2] = %d\n", data->final_path[2][2]);
	ft_printf("data->final_path[2][3] = %d\n", data->final_path[2][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->rooms[0].visited = %d\n", data->rooms[0].visited);
	ft_printf("data->rooms[1].visited = %d\n", data->rooms[1].visited);
	ft_printf("data->rooms[2].visited = %d\n", data->rooms[2].visited);
	ft_printf("data->rooms[3].visited = %d\n", data->rooms[3].visited);
	ft_printf("data->rooms[4].visited = %d\n", data->rooms[4].visited);
	ft_printf("data->rooms[5].visited = %d\n", data->rooms[5].visited);
	ft_printf("data->rooms[6].visited = %d\n", data->rooms[6].visited);
	ft_printf("data->rooms[7].visited = %d\n", data->rooms[7].visited);
	ft_printf("data->rooms[8].visited = %d\n", data->rooms[8].visited);
	return (1);
}
