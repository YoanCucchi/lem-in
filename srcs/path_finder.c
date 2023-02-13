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

static void	cpy_path(t_data *data)
{
	int	j;

	j = 0;
	ft_printf("début cpy_path\n");
	while (j < data->nb_rooms)
	{
		if (data->path_i > 0)
			data->path[data->path_i][j] = data->path[data->path_i - 1][j];
		j++;
	}
	ft_printf("fin cpy_path\n");
}

static void	print_path(t_data *data, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("============================================================\n");
	while (i <= index) // change value to debug
	{
		j = 0;
		while (j < 10) // change value to debug
		{
			ft_printf("data->path[%d]", i);
			ft_printf("[%d]", j);
			ft_printf(" = %d\n", data->path[i][j]);
			j++;
		}
		ft_printf("--------------------------------------------------------\n");
		i++;
	}
	ft_printf("============================================================\n");
}

static void	add_to_queue(t_queue *q, int j)
{
	t_queue *new;

	new = (t_queue *)malloc(sizeof(t_queue));
	new->index = j;
	while(q->next != NULL)
		q = q->next;
	new->next = NULL;
	q->next = new;
	ft_printf("end add to queue\n");
}

static void init_index(t_data *data)
{
	int	j;

	j = 0;
	ft_printf("début init_index\n");
	while (j < data->nb_rooms)
	{
		data->path[data->path_i][j] = 0;
		j++;
	}
	ft_printf("fin init_index\n");
}

static int	find_start_connections(t_data *data, t_queue *q, int index)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	ft_printf("data->path_j = %d\n", data->path_j);
	ft_printf("in starting links\n");
	while (j < data->nb_rooms)
	{
		if (data->tab[index][j])
			found++;
		j++;
	}
	ft_printf("found = %d\n", found);
	j = 0;
	while (j < data->nb_rooms)
	{
		ft_printf("j = %d\n", j);
		ft_printf("inside while loop\n");
		if (data->tab[index][j])
		{
			ft_printf("inside if \n");
			data->path[data->path_i] = (int *)ft_memalloc(sizeof(int) * data->nb_rooms);
			init_index(data);
			cpy_path(data);
			// ft_printf("room : %s\n", data->rooms[q->index]);
			ft_printf("connection with : %d\n", j);
			add_to_queue(q, j);
			data->q_size++;
			ft_printf("data->path_i = %d\n", data->path_i);
			ft_printf("data->path_j = %d\n", data->path_j);
			ft_printf("j = %d\n", j);
			data->path[data->path_i][data->path_j] = j;
			ft_printf("testing = %d\n", data->path[data->path_i][data->path_j]);
			print_path(data, data->path_i);
			data->path_i++;
			i++;
			ft_printf("end\n");
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

	data->path = (int **)ft_memalloc(sizeof(int *));
	data->q_size = 0;
	q = (t_queue *)malloc(sizeof(t_queue));
	q->index = 0;
	q->next = NULL;
	tmp = q;
	while (q && q->index != data->nb_rooms - 1)
	{
		ft_printf("q->index = %d\n", q->index);
		find_start_connections(data, q, q->index);
		q = q->next;
		data->path_i = 0;
		data->path_j++;
	}
	q->index = 0;
	q = tmp;
	ft_printf("cleaning\n");
	while (q)
	{
		ft_printf("q_index = %d\n", q->index);
		tmp = q;
		q = q->next;
		free(tmp);
	}
	free(q);
}
