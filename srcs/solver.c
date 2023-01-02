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

static void reset_path(t_data *data, int round)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_rooms)
	{
		j = 0;
		while (j <= round)
		{
			data->path[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	make_new_path(t_data *data, int j, int k, int round)
{
	// je dois faire une copie du path en cours et y ajouter le lien suivant (k)
	// j = index path a copier
	// k = lien a copier dans le nouveau path créé
	int	i;

	i = 0;
	ft_printf("round = %d\n", round);
	while (i < round)
	{
		data->path[data->tmp_path_counter][i] = data->path[j][i];
		i++;
	}
	data->path[data->tmp_path_counter][i] = k;
	if (k == data->nb_rooms - 1)
	{
		ft_printf("INSIDE\n");
		data->path[j][i] = k;
	}
}

static int	all_visited(t_data *data, int i) // return 0 false
{
	int	j;

	j = -1;
	while (++j < data->nb_rooms - 1)
	{
		if (data->tab[i][j] && !data->rooms[j].visited)
			return (FALSE);
	}
	return (TRUE);
}

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
	data->rooms[0].links--;
	reset_visited(data);
	set_visited(data, round);
	reset_path(data, round);
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

static void path_no_link_end(t_data *data, int round)
{
	int	j;
	int	k;

	j = 0;
	while (j < data->nb_rooms)
	{
		k = 0;
		if (k == 0) // si le path n'est pas = 0
		{
			ft_printf("exist??? or not ???\n");
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
}

static void	path_link_end(t_data *data, int round)
{
	int	j;
	int	k;

	j = 0;
	while (j < data->nb_rooms)
	{
		k = 0;
		if (data->path[j][round - 1]) // si le path n'est pas = 0
		{
			if ((data->tab[data->path[j][round - 1]][data->nb_rooms -1] || \
			data->tab[data->nb_rooms -1][data->path[j][round - 1]]))
			{
				// je dois check si il y'a d'autre lien que end je dois dupliquer path
				data->path[j][round] = data->nb_rooms - 1;
				data->rooms[data->path[j][round - 1]].visited = 1;
				save_path(data, j, round); // SAVETHEPATH
				break;
			}
			while (k < data->nb_rooms) // nombre de lien
			{
				// il faut que je rajoute un check pour voir si il y a un lien
				// avec la room end, je dois stop et save path
				if (data->tab[data->path[j][round - 1]][k] && !data->rooms[k].visited && all_visited(data, data->path[j][round - 1]))
				{
					ft_printf("j = %d\n", j);
					ft_printf("lien avec 2222 %d\n", k);
					data->path[j][round] = k;
					data->rooms[k].visited = 1;
					if (k == data->nb_rooms - 1)
						save_path(data, j, round); // SAVETHEPATH
					break;
				}
				else if (data->tab[data->path[j][round - 1]][k] && !data->rooms[k].visited && !all_visited(data, data->path[j][round - 1]))
				{
					ft_printf("ON A PAS TOUT VISITE\n\n\n\n\n\n\n\n\n");
					ft_printf("k = %d\n", k);
					ft_printf("tmp_path_counter = %d\n", data->tmp_path_counter);
					make_new_path(data, j, k, round);
					if (k == data->nb_rooms - 1)
						save_path(data, j, round); // SAVETHEPATH
					break;
				}
				k++;
			}
		}
		j++;
	}
}
int	solver(t_data *data, int i)
{
	// int	path_nb;
	int	round;
	int	j;
	// int	k;

	// path_nb = 0;
	round = 1;
	if (i)
		nb_links(data);
	data->tmp_path_counter = data->rooms[0].links;
	// je connais le nombre de lien de chaque salle
	// si start à + d'un lien valide go
	while (data->rooms[0].links > 0)
	{
		round = 1;
		j = 0;
		while ((!data->tab[data->path[j][round - 1]][data->nb_rooms -1] || \
			!data->tab[data->nb_rooms -1][data->path[j][round - 1]])) // tant que je suis pas sur une room connectée a end
		{
			path_no_link_end(data, round);
			round++;
			j = 0;
		}
		path_link_end(data, round);
	}
	ft_printf("round = %d\n", round);
	ft_printf("data->rooms[0].links = %d\n", data->rooms[0].links);
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
