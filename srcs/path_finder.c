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

static int	already_in_path(t_data *data, int index)
{
	int	j;

	j = 0;
	while(j < data->nb_rooms)
	{
		if (data->path[data->path_i][j] == index)
			return (1);
		j++;
	}
	return (0);
}

static void intercalate_data_path(t_data *data, int index, int new_value) 
{
	int	tmp1;
	int	tmp2;
	int	tmp_j;

	ft_printf("data->path_i = %d\n", data->path_i);
	ft_printf("data->path_j = %d\n", data->path_j);
	ft_printf("data->path_counter = %d\n", data->path_counter);
	ft_printf("new value = %d\n", new_value);
	tmp_j = data->path_j - 1;
	tmp1 = data->path[index][tmp_j];
	data->path[index][tmp_j] = new_value;
	index ++;
	while (index < data->path_counter)
	{
		tmp_j = data->path_j - 1;
		ft_printf("index = %d\n", index);
		while (tmp_j < data->nb_rooms)
		{
			ft_printf("tmp_j = %d\n", tmp_j);
			tmp2 = data->path[index][tmp_j];
			ft_printf("tmp2 = %d\n", tmp2);
			data->path[index][tmp_j] = tmp1;
			ft_printf("data->path[index + 1][tmp_j] = %d\n", data->path[index + 1][tmp_j]);
			tmp1 = data->path[index + 1][tmp_j];
			ft_printf("tmp1 = %d\n", tmp1);
			data->path[index + 1][tmp_j] = tmp2;
			tmp_j++;
		}
		index++;
	}
}
static int	*new_int_arr(t_data *data)
{
	int	*new;
	int	i;

	i = 0;
	new = (int *)ft_memalloc(sizeof(int) * data->nb_rooms);
	ft_printf("data->nb_rooms = %d\n", data->nb_rooms);
	while (i < data->nb_rooms)
	{
		new[i] = 0;
		i++;
	}
	return (new);
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

static void	cpy_path(t_data *data)
{
	int	i;
	int	tmp;
	int	index;

	i = 0;
	index = 0;
	tmp = data->path_counter;
	ft_printf("début cpy_path\n");
	ft_printf("data->path_counter = %d\n", data->path_counter);
	data->path[data->path_counter] = new_int_arr(data);
	ft_printf("data->path_i = %d\n", data->path_i);
	ft_printf("data->path_counter = %d\n", data->path_counter);
	while (i < data->nb_rooms)
	{
		data->path[data->path_counter][i] = data->path[data->path_i][i];
		ft_printf("data->path[data->path_counter][i] = %d\n", data->path[data->path_counter][i]);
		i++;
	}
	// need to swap but fucking how 
	ft_printf("avant loop\n");
	ft_printf("data->path_i = %d\n", data->path_i);
	index = data->path_i + 1;
	print_path(data, 3);
	intercalate_data_path(data, index, data->path[data->path_i][data->path_j - 1]);
	print_path(data, 3);
	while (1)
		i++;
	data->path_counter = tmp;
	data->path_counter++;
	ft_printf("fin cpy_path\n");
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
	ft_printf("data->path_counter = %d\n", data->path_counter);
	ft_printf("found = %d\n", found);
	while (found > data->path_counter)
	{
		data->path[data->path_counter] = new_int_arr(data);
		data->path_counter++;
	}
	j = 0;
	ft_printf("data->path[0][1] = %d\n", data->path[0][1]);
	ft_printf("data->path[1][1] = %d\n", data->path[1][1]);
	ft_printf("data->path[2][1] = %d\n", data->path[2][1]);
	while (j < data->nb_rooms)
	{
		ft_printf("j = %d\n", j);
		ft_printf("inside while loop\n");
		if (data->tab[index][j])
		{
			ft_printf("inside if \n");
			ft_printf("connection with : %d\n", j);
			add_to_queue(q, j);
			data->q_size++;
			ft_printf("data->path_i = %d\n", data->path_i);
			ft_printf("data->path_j = %d\n", data->path_j);
			ft_printf("j = %d\n", j);
			data->path[data->path_i][data->path_j] = j;
			print_path(data, 2);
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

static int	find_connections(t_data *data, t_queue *q, int index)
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
	ft_printf("data->path_counter = %d\n", data->path_counter);
	while (found > 1)
	{
		ft_printf("found > 1\n");
		cpy_path(data);
		found--;
	}
	j = 0;
	i = 0;
	while (i < data->path_counter)
	{
		ft_printf("%d\n", data->path[i][1]);
		i++;
	}
	j = 0;
	i = 0;
	while (j < data->nb_rooms)
	{
		ft_printf("j = %d\n", j);
		ft_printf("inside while loop\n");
		if (data->tab[index][j] && !already_in_path(data, j))
		{
			ft_printf("inside if \n");
			ft_printf("connection with : %d\n", j);
			add_to_queue(q, j);
			data->q_size++;
			ft_printf("data->path_i = %d\n", data->path_i);
			ft_printf("data->path_j = %d\n", data->path_j);
			ft_printf("j = %d\n", j);
			data->path[data->path_i][data->path_j] = j;
			print_path(data, data->path_counter - 1);
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

	data->path = (int **)ft_memalloc(sizeof(int *) * (data->nb_rooms * 5)); // find proper value 
	data->q_size = 0;
	q = (t_queue *)malloc(sizeof(t_queue));
	q->index = 0;
	q->next = NULL;
	tmp = q;
	find_start_connections(data, q, q->index);
	data->path_i = 0;
	data->path_j++;
	q = q->next;
	while (q && q->index != data->nb_rooms - 1)
	{
		ft_printf("path_counter = %d\n", data->path_counter);
		ft_printf("q->index = %d\n", q->index);
		find_connections(data, q, q->index);
		q = q->next;
		if (data->path_counter == data->path_i)
		{
			data->path_i = 0;
			data->path_j++;
		}
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
