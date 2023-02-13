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

#include "../includes/lem_in.h" // change

static void	add_to_queue(t_queue *q, int j)
{
	t_queue *new;

	new = (t_queue *)malloc(sizeof(t_queue));
	new->index = j;
	while(q->next != NULL)
		q = q->next;
	new->next = NULL;
	q->next = new;
}

static int	find_start_connections(t_data *data, t_queue *q, int index)
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
		if (data->tab[index][j])
		{
			found++;
			ft_printf("room : %s\n", data->rooms[q->index]);
			ft_printf("connection with : %d\n", j);
			add_to_queue(q, j);
			data->q_size++;
			data->path[data->path_i++][data->path_j] = j;
			i++;
		}
		j++;
	}
	if (!found)
		return (0);
	return (1);
}

void	path_finder(t_data *data)
{
	t_queue	*q;
	t_queue *tmp;

	// idea working pretty much fine but i need to implement properly the path
	// to be able to check if a room is already inside it, in wich case i do
	// not want to visit the room again 
	data->q_size = 0;
	q = (t_queue *)malloc(sizeof(t_queue));
	q->index = 0;
	q->next = NULL;
	while (q && q->index != data->nb_rooms - 1)
	{
		ft_printf("q->index = %d\n", q->index);
		find_start_connections(data, q, q->index);
		q = q->next;
	}
	q->index = 0;
	ft_printf("data->q_size = %d\n", data->q_size);
	ft_printf("q->index = %d\n", q->index);
	ft_printf("q->next->index = %d\n", q->next->index);
	ft_printf("q->next->next->index = %d\n", q->next->next->index);
	ft_printf("q->next->next->next->index = %d\n", q->next->next->next->index);
	while (q)
	{
		tmp = q;
		q = q->next;
		free(tmp);
	}
	free(q);
}
