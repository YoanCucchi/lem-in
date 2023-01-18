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

int	no_possible_solution(t_data *data, int *connections)
{
	int	i;

	i = 0;
	while (i < data->nb_rooms - 1)
	{
		if (connections[i] != 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_connections(int *connections)
{
	int	i;

	i = 0;
	while (connections[i])
	{
		ft_printf("connections[%d] = ", i);
		ft_printf("%d\n", connections[i++]);
	}
}

int	find_starting_links(t_data *data, int *connections)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	data->path_j = 1;
	data->path_i = 0;
	ft_printf("in starting links\n");
	// first fonction to check connections with start and create paths
	while (j < data->nb_rooms)
	{
		ft_printf("inside while loop\n");
		if (data->tab[0][j] && !data->rooms[j].visited)
		{
			found++;
			connections[i] = j;
			data->rooms[j].visited = 1;
			data->path[data->path_i++][data->path_j] = j;
			i++;
		}
		j++;
	}
	data->path_j++;
	print_connections(connections);
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
	if (!found)
		return (0);
	return (1);
}

void	reset_connections(t_data *data, int *connections)
{
	int	i;

	i = 0;
	ft_printf("reset connections \n");
	while (i < data->nb_rooms)
		connections[i++] = 0;
}

static void	move_path_data(t_data *data, int index, int delete)
{
	int	size;
	int	i;

	size = data->nb_rooms; // a fixer.
	i = size - 1;
	ft_printf("move path data, index = %d\n", index);
	ft_printf("delete = %d\n", delete);
	if (delete) // remove a path
	{
		while (index < i)
		{
			ft_printf("in loop : index = %d\n", index);
			ft_memcpy(data->path[index], data->path[index + 1], size * sizeof(int));
			index++;
		}
	}
	else // move to the right
	{
		while (i > index)
		{
			ft_memcpy(data->path[i], data->path[i - 1], size * sizeof(int));
			i--;
		}
	}
}

static int	*add_new_connection(t_data *data, int *connections, int index)
{
	int	i;

	i = 0;
	while (connections[i])
		i++;
	i++;
	while (i-- > 0 && i != index) // 123   ==> .123
		connections[i] = connections[i - 1];
	connections[index] = connections[index];
	print_connections(connections);
	move_path_data(data, i, 0);
	return (connections);
}

static int	*remove_connection(t_data *data, int *connections, int index)
{
	int	size;
	int	i;

	i = index;
	size = data->nb_rooms;
	while (index < size) // 123   ==> .13
	{
		connections[index] = connections[index + 1];
		index++;
	}
	move_path_data(data, i, 1);
	return (connections);
}

static int	nb_links(t_data *data, int room)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->nb_rooms)
	{
		if (data->tab[room][i] && !data->rooms[i].visited)
			count++;
		i++;
	}
	return (count);
}
static int	*cpy_new_connections(t_data *data, int *connections, int *save)
{
	int	i;

	i = -1;
	while (++i < data->nb_rooms)
	{
		connections[i] = save[i];
	}
	data->path_j++;
	return (connections);
}

int	*find_connections(t_data *data, int *connections)
{
	int	i;
	int	j;
	int	k;
	int	*save;

	ft_printf("début de find connections\n");
	save = (int *)malloc(sizeof(int) * data->nb_rooms);
	i = -1;
	k = -1;
	data->path_i = 0;
	while (connections[++i])
	{
		ft_printf("i = %d\n", i);
		j = -1;
		if (nb_links(data, connections[i]) > 1)
			connections = add_new_connection(data, connections, i);
		else if (nb_links(data, connections[i]) == 0)
			connections = remove_connection(data, connections, i);
		while (++j < data->nb_rooms)
		{
			if (data->tab[connections[i]][j] && !data->rooms[j].visited)
			{
				ft_printf("%d a un ", connections[i]);
				ft_printf("lien avec %d\n", j);
				data->rooms[j].visited = 1;
				data->path[data->path_i][data->path_j] = j;
				if (j == data->nb_rooms - 1)
				{
					ft_printf("we need to end");
					free(save);
					store_final_path(data, i);
					reset_visited(data);
					return (0);
				}
				data->path_i++;
				save[++k] = j;
				break ;
			}
		}
	}
	reset_connections(data, connections);
	connections = cpy_new_connections(data, connections, save);
	free(save);
	ft_printf("end of find connections\n");
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[0][0] = %d\n", data->path[0][0]);
	ft_printf("data->path[0][1] = %d\n", data->path[0][1]);
	ft_printf("data->path[0][2] = %d\n", data->path[0][2]);
	ft_printf("data->path[0][3] = %d\n", data->path[0][3]);
	ft_printf("data->path[0][4] = %d\n", data->path[0][4]);
	ft_printf("data->path[0][5] = %d\n", data->path[0][5]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[1][0] = %d\n", data->path[1][0]);
	ft_printf("data->path[1][1] = %d\n", data->path[1][1]);
	ft_printf("data->path[1][2] = %d\n", data->path[1][2]);
	ft_printf("data->path[1][3] = %d\n", data->path[1][3]);
	ft_printf("data->path[1][4] = %d\n", data->path[1][4]);
	ft_printf("data->path[1][5] = %d\n", data->path[1][5]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[2][0] = %d\n", data->path[2][0]);
	ft_printf("data->path[2][1] = %d\n", data->path[2][1]);
	ft_printf("data->path[2][2] = %d\n", data->path[2][2]);
	ft_printf("data->path[2][3] = %d\n", data->path[2][3]);
	ft_printf("data->path[2][4] = %d\n", data->path[2][4]);
	ft_printf("data->path[2][5] = %d\n", data->path[2][5]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[3][0] = %d\n", data->path[3][0]);
	ft_printf("data->path[3][1] = %d\n", data->path[3][1]);
	ft_printf("data->path[3][2] = %d\n", data->path[3][2]);
	ft_printf("data->path[3][3] = %d\n", data->path[3][3]);
	ft_printf("data->path[3][4] = %d\n", data->path[3][4]);
	ft_printf("data->path[3][5] = %d\n", data->path[3][5]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[4][0] = %d\n", data->path[4][0]);
	ft_printf("data->path[4][1] = %d\n", data->path[4][1]);
	ft_printf("data->path[4][2] = %d\n", data->path[4][2]);
	ft_printf("data->path[4][3] = %d\n", data->path[4][3]);
	ft_printf("data->path[4][4] = %d\n", data->path[4][4]);
	ft_printf("data->path[4][5] = %d\n", data->path[4][5]);
	ft_printf("--------------------------------------------------\n");
	if (no_possible_solution(data, connections) == 0)
		return (0);
	return (connections);
}