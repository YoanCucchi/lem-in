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

void	find_starting_links(t_data *data, int *connections)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// first fonction to check connections with start and create paths
	while (!data->rooms[j].visited && j < data->nb_rooms)
	{
		if (data->tab[0][j])
		{
			connections[i] = j;
			data->rooms[j].visited = 1;
			data->path[data->path_i++][data->path_j] = j;
			i++;
		}
		j++;
	}
	data->path_j++;
}

void	reset_connections(t_data *data, int *connections)
{
	int	i;

	i = 0;
	while (i++ < data->nb_rooms)
		connections[i] = 0;
}

static int	*add_new_connection(int *connections, int index)
{
	int	i;

	i = 0;
	ft_printf("index = %d\n", index);
	ft_printf("in NEW FUNCTIONd\n");
	while (connections[i])
		i++;
	i++;
	while (i-- > 0 && i != index) // 123   ==> .123
		connections[i] = connections[i - 1];
	connections[index] = connections[index];
	print_connections(connections);
	return (connections);
}

static int	*remove_connection(int *connections, int index)
{
	int	size; // A FIXER

	size = 10;
	ft_printf("index = %d\n", index);
	ft_printf("remove path\n");
	ft_printf("connections[i] = %d\n", connections[index]);
	while (index < size) // 123   ==> .13
	{
		connections[index] = connections[index + 1];
		index++;
	}
	ft_printf("connections after remove : \n");
	print_connections(connections);
	return (connections);
}

static void	delete_path_data(t_data *data, int index)
{
	int	size = 10; // a fixer. index = 2 soit = index 3

	ft_printf("inside");
	while (index + 1 < size)
	{
		ft_printf("in loop : index = %d\n", index);
		ft_memcpy(data->path[index], data->path[index+1], size * sizeof(int));
		index++;
	}
}

static void	move_path_data(t_data *data)
{
	int	size = 10; // a fixer.
	int	i = size - 1;
	while (i > 0)
	{
		ft_memcpy(data->path[i], data->path[i-1], size * sizeof(int));
		i--;
	}
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

int	*find_connections(t_data *data, int *connections)
{
	int	i;
	int	j;
	int	k;
	int	*save;

	save = (int *)malloc(sizeof(int) * data->nb_rooms);
	i = 0;
	k = 0;
	data->path_i = 0;
	while (connections[i])
	{
		// if (connections[i] == data->nb_rooms - 1)
		// 	ft_printf("winner at %d\n", i);
		ft_printf("dealing with connections [%d] = ", i);
		ft_printf("%d\n", connections[i]);
		j = 0;
		if (nb_links(data, connections[i]) > 1)
		{
			ft_printf("MULTIPLE ROOMS LINK\n");
			// move all path data to next path
			connections = add_new_connection(connections, i);
			move_path_data(data);
		}
		else if (nb_links(data, connections[i]) == 0)
		{
			ft_printf("no connections for this path FINISH HIM\n");
			// need to delete this shitty path
			connections = remove_connection(connections, i);
			delete_path_data(data, i);
			// find connections again ?  ou just path_i++ et i++ ? ou rien mais
			// retourne connections sans celle path empty.
		}
		while(j < data->nb_rooms)
		{
			if (data->tab[connections[i]][j] && !data->rooms[j].visited)
			{
				ft_printf("j = %d\n", j);
				if (j != data->nb_rooms - 1) // exclus la final room
					data->rooms[j].visited = 1;
				data->path[data->path_i][data->path_j] = j;
				data->path_i++;
				save[k] = j;
				k++;
				ft_printf("we break out\n");
				break ;
			}
			j++;
		}
		i++;
	}
	reset_connections(data, connections);
	i = 0;
	while (i < data->nb_rooms)
	{
		if (save[i])
			connections[i] = save[i];
		i++;
	}
	data->path_j++;
	free(save);

	ft_printf("connections before starting new cycle : \n\n");
	print_connections(connections);
	ft_printf("path at this points = \n\n");
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
	ft_printf("data->path[3][0] = %d\n", data->path[3][0]);
	ft_printf("data->path[3][1] = %d\n", data->path[3][1]);
	ft_printf("data->path[3][2] = %d\n", data->path[3][2]);
	ft_printf("data->path[3][3] = %d\n", data->path[3][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[4][0] = %d\n", data->path[4][0]);
	ft_printf("data->path[4][1] = %d\n", data->path[4][1]);
	ft_printf("data->path[4][2] = %d\n", data->path[4][2]);
	ft_printf("data->path[4][3] = %d\n", data->path[4][3]);
	ft_printf("--------------------------------------------------\n");
	ft_printf("data->path[5][0] = %d\n", data->path[5][0]);
	ft_printf("data->path[5][1] = %d\n", data->path[5][1]);
	ft_printf("data->path[5][2] = %d\n", data->path[5][2]);
	ft_printf("data->path[5][3] = %d\n", data->path[5][3]);
	ft_printf("--------------------------------------------------\n");
	return (connections);
}